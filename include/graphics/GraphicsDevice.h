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

		[[nodiscard]] bool UploadGeometry();
		void RenderGeometry(SDL_GPURenderPass* render_pass) const;

		SDL_GPUBuffer* vertex_buffer = nullptr;

	private:
		SDL_GPUDevice* m_gpu = nullptr;
		SDL_GPUTransferBuffer* m_transfer_buffer = nullptr;
		SDL_GPUGraphicsPipeline* m_graphics_pipeline = nullptr;


		SDL_GPUShader* m_vertex_shader = nullptr;
		SDL_GPUShader* m_fragment_shader = nullptr;
	};
} // namespace Fizzle
