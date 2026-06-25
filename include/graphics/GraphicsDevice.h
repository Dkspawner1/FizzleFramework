#pragma once

#include <SDL3/SDL.h>

namespace fizzle
{

    class GraphicsDevice
    {
    public:
        GraphicsDevice() = default;
        ~GraphicsDevice();

        GraphicsDevice(const GraphicsDevice&) = delete;
        GraphicsDevice& operator=(const GraphicsDevice&) = delete;
        GraphicsDevice(GraphicsDevice&&) = delete;
        GraphicsDevice& operator=(GraphicsDevice&&) = delete;

        [[nodiscard]] bool Initialize(SDL_Window* window);
        void Shutdown(SDL_Window* window);

        [[nodiscard]] SDL_GPUDevice* GetDevice() const { return m_gpu; }
        [[nodiscard]] bool           IsValid()   const { return m_gpu != nullptr; }

        [[nodiscard]] bool UploadGeometry();

        SDL_GPUBuffer* vertex_buffer = nullptr;

    private:
        SDL_GPUDevice* m_gpu = nullptr;
        SDL_GPUTransferBuffer* m_transfer_buffer = nullptr;
    };

} // namespace Fizzle