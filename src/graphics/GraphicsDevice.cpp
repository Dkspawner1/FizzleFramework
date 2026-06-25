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
			SDL_GPU_SHADERFORMAT_SPIRV,
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


		size_t vertex_code_size;
		const auto vertex_code = SDL_LoadFile("C:/Users/Dorll/source/repos/FizzleFramework/assets/shaders/compiled/spirv/quad.vert.spv", &vertex_code_size);

		SDL_GPUShaderCreateInfo vertex_shader_data{};
		vertex_shader_data.code = static_cast<Uint8*>(vertex_code);
		vertex_shader_data.code_size = vertex_code_size;
		vertex_shader_data.entrypoint = "main";
		vertex_shader_data.format = SDL_GPU_SHADERFORMAT_SPIRV;
		vertex_shader_data.stage = SDL_GPU_SHADERSTAGE_VERTEX;
		vertex_shader_data.num_samplers = 0;
		vertex_shader_data.num_storage_buffers = 0;
		vertex_shader_data.num_storage_textures = 0;
		vertex_shader_data.num_uniform_buffers = 0;

		m_vertex_shader = SDL_CreateGPUShader(m_gpu, &vertex_shader_data);
		SDL_free(vertex_code);

		size_t fragment_code_size;
		const auto fragment_code = SDL_LoadFile("C:/Users/Dorll/source/repos/FizzleFramework/assets/shaders/compiled/spirv/quad.frag.spv", &fragment_code_size);
		SDL_GPUShaderCreateInfo fragment_shader_data{};
		fragment_shader_data.code = static_cast<Uint8*>(fragment_code);
		fragment_shader_data.code_size = fragment_code_size;
		fragment_shader_data.entrypoint = "main";
		fragment_shader_data.format = SDL_GPU_SHADERFORMAT_SPIRV;
		fragment_shader_data.stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
		fragment_shader_data.num_samplers = 0;
		fragment_shader_data.num_storage_buffers = 0;
		fragment_shader_data.num_storage_textures = 0;
		fragment_shader_data.num_uniform_buffers = 0;

		m_fragment_shader = SDL_CreateGPUShader(m_gpu, &fragment_shader_data);
		SDL_free(fragment_code);


		SDL_GPUGraphicsPipelineCreateInfo pipeline_info{};
		pipeline_info.vertex_shader = m_vertex_shader;
		pipeline_info.fragment_shader = m_fragment_shader;
		pipeline_info.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;

		SDL_GPUVertexBufferDescription vertex_buffer_descriptions[1];
		vertex_buffer_descriptions[0].slot = 0;
		vertex_buffer_descriptions[0].input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
		vertex_buffer_descriptions[0].instance_step_rate = 0;
		vertex_buffer_descriptions[0].pitch = sizeof(Vertex);


		pipeline_info.vertex_input_state.num_vertex_buffers = 1;
		pipeline_info.vertex_input_state.vertex_buffer_descriptions = vertex_buffer_descriptions;


		//SDL_GPUVertexAttribute vertex_attributes[2];
		SDL_GPUVertexAttribute vertex_attributes[1];

		// a_position
		vertex_attributes[0].buffer_slot = 0;
		vertex_attributes[0].location = 0;
		vertex_attributes[0].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
		vertex_attributes[0].offset = 0;

		//// a_color
		//vertex_attributes[1].buffer_slot = 0;
		//vertex_attributes[1].location = 1;
		//vertex_attributes[1].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4;
		//vertex_attributes[1].offset = sizeof(float) * 3;

		//pipeline_info.vertex_input_state.num_vertex_attributes = 2;
		pipeline_info.vertex_input_state.num_vertex_attributes = 1;

		pipeline_info.vertex_input_state.vertex_attributes = vertex_attributes;

		SDL_GPUColorTargetDescription color_target_descriptions[1];
		color_target_descriptions[0] = {};
		color_target_descriptions[0].blend_state.enable_blend = true;
		color_target_descriptions[0].blend_state.color_blend_op = SDL_GPU_BLENDOP_ADD;
		color_target_descriptions[0].blend_state.alpha_blend_op = SDL_GPU_BLENDOP_ADD;
		color_target_descriptions[0].blend_state.src_color_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
		color_target_descriptions[0].blend_state.dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
		color_target_descriptions[0].blend_state.src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
		color_target_descriptions[0].blend_state.dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
		color_target_descriptions[0].format = SDL_GetGPUSwapchainTextureFormat(m_gpu, window);

		pipeline_info.target_info.num_color_targets = 1;
		pipeline_info.target_info.color_target_descriptions = color_target_descriptions;

		m_graphics_pipeline = SDL_CreateGPUGraphicsPipeline(m_gpu, &pipeline_info);

		SDL_ReleaseGPUShader(m_gpu, m_vertex_shader);
		SDL_ReleaseGPUShader(m_gpu, m_fragment_shader);

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

		if (m_graphics_pipeline)
		{
			SDL_ReleaseGPUGraphicsPipeline(m_gpu, m_graphics_pipeline);
			m_graphics_pipeline = nullptr;
			LOG_INFO("Graphics Pipeline Destroyed");
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

		SDL_GPUCommandBuffer* command_buffer = SDL_AcquireGPUCommandBuffer(m_gpu);
		SDL_GPUCopyPass* copy_pass = SDL_BeginGPUCopyPass(command_buffer);

		SDL_GPUTransferBufferLocation location{};
		location.transfer_buffer = m_transfer_buffer;
		location.offset = 0;

		SDL_GPUBufferRegion region{};
		region.buffer = vertex_buffer;
		region.size = sizeof(g_vertices);
		region.offset = 0;

		SDL_UploadToGPUBuffer(copy_pass, &location, &region, true);
		SDL_EndGPUCopyPass(copy_pass);
		SDL_SubmitGPUCommandBuffer(command_buffer);

		SDL_ReleaseGPUTransferBuffer(m_gpu, m_transfer_buffer);
		m_transfer_buffer = nullptr;

		LOG_INFO("Geometry uploaded to GPU ({} bytes)", sizeof(g_vertices));
		return true;
	}


	void GraphicsDevice::RenderGeometry(SDL_GPURenderPass* render_pass) const
	{
		if (!m_graphics_pipeline || !vertex_buffer)
		{
			LOG_ERROR("RenderGeometry called before pipeline/buffer are ready");
			return;
		}

		SDL_BindGPUGraphicsPipeline(render_pass, m_graphics_pipeline);

		SDL_GPUBufferBinding vertex_binding{};
		vertex_binding.buffer = vertex_buffer;
		vertex_binding.offset = 0;
		SDL_BindGPUVertexBuffers(render_pass, 0, &vertex_binding, 1);

		// 6 vertices = 2 triangles = 1 quad, 1 instance
		SDL_DrawGPUPrimitives(render_pass, 6, 1, 0, 0);
	}

} // namespace Fizzle