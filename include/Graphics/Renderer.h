#ifndef RENDERER_H
#define RENDERER_H

#include <Core/Rectangle.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Graphics/Color.h>
#include <Graphics/Window.h>

class Renderer {
public:
    explicit Renderer(Window *window);

    ~Renderer();

    void Initialize();

    void Clear() const;

    void Present();

    void SetClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void DrawRectangle(const Rectangle &destRect, const Color &color) const;

private:
    void InitializeGlad();

    void CheckShaderCompilation(GLuint shader, const char *shaderType);

    void CheckProgramLinking(GLuint program);

    Window *m_window;
    GLuint m_vao, m_vbo;
    GLuint m_shaderProgram;
};

#endif //RENDERER_H
