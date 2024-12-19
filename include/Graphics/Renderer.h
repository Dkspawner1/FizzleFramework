#ifndef RENDERER_H
#define RENDERER_H

#include <Core/Rectangle.h>
#include <glad/glad.h>
#include <Graphics/Color.h>
#include <Graphics/Window.h>
#include <Content/Texture.h>

class Renderer {
public:
    explicit Renderer(Window *window);
    ~Renderer();

    void Initialize();
    void Clear() const;
    void Present();
    void SetClearColor(const Color &color) const;
    void DrawRectangle(const Rectangle &destRect, const Color &color) const;
    void DrawTexture(const Texture &texture, const Rectangle &destRect, const Color &color) const;
    void DrawTexture(const Texture &texture, const Rectangle &srcRect, const Rectangle &destRect, const Color &color) const;
    void DrawFontTexture(const Texture& texture, const Rectangle& srcRect, const Rectangle& destRect, const Color& color) const;

private:
    void ConvertToNormalizedDeviceCoordinates(const Rectangle &rect, int windowWidth, int windowHeight,
                                          float &outX, float &outY, float &outWidth, float &outHeight) const;
    void CheckShaderCompilation(GLuint shader, const char *shaderType) const;
    void CheckProgramLinking(const GLuint program) const;

    Window *m_window;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_texCoordVbo;
    GLuint m_textureShaderProgram;
    GLuint m_fontShaderProgram;
    GLuint m_whiteTexture;
};
#endif
