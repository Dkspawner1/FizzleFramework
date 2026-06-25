#pragma once
#include <string>
#include <SDL3/SDL.h>

enum class ShaderType
{
	FRAGMENT,
	VERTEX
};

inline const char* to_string(const ShaderType e)
{
	switch (e)
	{
	default: return "unknown";
	case ShaderType::FRAGMENT: return "FRAGMENT";
	case ShaderType::VERTEX: return "VERTEX";
	}
}


struct FragmentShader{};
struct VertexShader{};


class Shader
{
public:
	explicit Shader(std::string path) : m_path(std::move(path))
	{

	}

	inline bool Load(const std::string& path)
	{
	}

private:
	SDL_GPUShader* m_shader;
	std::string m_path;

};
