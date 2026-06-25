#include <debug/logger.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/Vertex.h>


namespace fizzle
{

    GraphicsDevice::~GraphicsDevice()
    {
        if (m_gpu)
        {
            LOG_WARNING("GraphicsDevice destroyed without calling Shutdown() first");
            SDL_DestroyGPUDevice(m_gpu);
            m_gpu = nullptr;
        }
    }

    bool GraphicsDevice::Initialize(SDL_Window* window)
    {
        m_gpu = SDL_CreateGPUDevice(
            SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL,
            true,
            nullptr
        );
        if (!m_gpu)
        {
            LOG_ERROR("SDL_CreateGPUDevice failed: {}", SDL_GetError());
            return false;
        }

        if (!SDL_ClaimWindowForGPUDevice(m_gpu, window))
        {
            LOG_ERROR("SDL_ClaimWindowForGPUDevice failed: {}", SDL_GetError());
            SDL_DestroyGPUDevice(m_gpu);
            m_gpu = nullptr;
            return false;
        }

        LOG_INFO("GPU device ready ({})", SDL_GetGPUDeviceDriver(m_gpu));
        return true;
    }

    void GraphicsDevice::Shutdown(SDL_Window* window)
    {
        if (!m_gpu)
            return;

        if (m_transfer_buffer)
        {
            SDL_ReleaseGPUTransferBuffer(m_gpu, m_transfer_buffer);
            m_transfer_buffer = nullptr;
        }
        if (vertex_buffer)
        {
            SDL_ReleaseGPUBuffer(m_gpu, vertex_buffer);
            vertex_buffer = nullptr;
            LOG_INFO("GPU buffers released");
        }

        if (window)
        {
            SDL_ReleaseWindowFromGPUDevice(m_gpu, window);
            LOG_INFO("Window unclaimed from GPU device");
        }

        SDL_DestroyGPUDevice(m_gpu);
        m_gpu = nullptr;
        LOG_INFO("GPU device destroyed");
    }

    bool GraphicsDevice::UploadGeometry()
    {
        if (!m_gpu)
        {
            LOG_ERROR("UploadGeometry called before Initialize");
            return false;
        }

        SDL_GPUBufferCreateInfo buffer_info{};
        buffer_info.size = sizeof(g_vertices);
        buffer_info.usage = SDL_GPU_BUFFERUSAGE_VERTEX;
        vertex_buffer = SDL_CreateGPUBuffer(m_gpu, &buffer_info);
        if (!vertex_buffer)
        {
            LOG_ERROR("SDL_CreateGPUBuffer failed: {}", SDL_GetError());
            return false;
        }

        SDL_GPUTransferBufferCreateInfo transfer_info{};
        transfer_info.size = sizeof(g_vertices);
        transfer_info.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
        m_transfer_buffer = SDL_CreateGPUTransferBuffer(m_gpu, &transfer_info);
        if (!m_transfer_buffer)
        {
            LOG_ERROR("SDL_CreateGPUTransferBuffer failed: {}", SDL_GetError());
            return false;
        }

        void* mapped = SDL_MapGPUTransferBuffer(m_gpu, m_transfer_buffer, false);
        SDL_memcpy(mapped, g_vertices, sizeof(g_vertices));
        SDL_UnmapGPUTransferBuffer(m_gpu, m_transfer_buffer);

        SDL_GPUCommandBuffer* cmd = SDL_AcquireGPUCommandBuffer(m_gpu);
        SDL_GPUCopyPass* copy_pass = SDL_BeginGPUCopyPass(cmd);

        SDL_GPUTransferBufferLocation location{};
        location.transfer_buffer = m_transfer_buffer;
        location.offset = 0;

        SDL_GPUBufferRegion region{};
        region.buffer = vertex_buffer;
        region.size = sizeof(g_vertices);
        region.offset = 0;

        SDL_UploadToGPUBuffer(copy_pass, &location, &region, true);
        SDL_EndGPUCopyPass(copy_pass);
        SDL_SubmitGPUCommandBuffer(cmd);

        SDL_ReleaseGPUTransferBuffer(m_gpu, m_transfer_buffer);
        m_transfer_buffer = nullptr;

        LOG_INFO("Geometry uploaded to GPU ({} bytes)", sizeof(g_vertices));
        return true;
    }

} // namespace Fizzle