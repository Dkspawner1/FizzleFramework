#include <Graphics/Renderer.h>
#include <stdexcept>

Renderer::Renderer() {
    InitializeGlad();
}

void Renderer::InitializeGlad() {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SetClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    glClearColor(r, g, b, a);
}
