#include <array>
#include <Graphics/Renderer.h>
#include <stdexcept>

Renderer::Renderer(Window *window) : m_window(window), m_vao(0), m_vbo(0), m_shaderProgram(0) {
    // Don't perform OpenGL operations here
}

Renderer::~Renderer() {
    if (m_vao != 0)
        glDeleteVertexArrays(1, &m_vao);
    if (m_vbo != 0)
        glDeleteBuffers(1, &m_vbo);
    if (m_shaderProgram != 0)
        glDeleteProgram(m_shaderProgram);
}

void Renderer::Initialize() {
    // Create and bind VAO and VBO
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Set up vertex attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    // Vertex Shader
    const char *vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        void main() {
            gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
        }
    )";

    // Fragment Shader
    const char *fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec4 color;
        void main() {
            FragColor = color;
        }
    )";

    // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    CheckShaderCompilation(vertexShader, "Vertex");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    CheckShaderCompilation(fragmentShader, "Fragment");

    // Create shader program
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    CheckProgramLinking(m_shaderProgram);

    // Clean up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Renderer::CheckShaderCompilation(GLuint shader, const char *shaderType) const{
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error(std::string(shaderType) + " shader compilation failed: " + infoLog);
    }
}

void Renderer::CheckProgramLinking(const GLuint program) const {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
    }
}

void Renderer::SetClearColor(const Color &color) const{
    glClearColor(color.GetR() / 255.0f, color.GetG() / 255.0f, color.GetB() / 255.0f, color.GetA() / 255.0f);
}
void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Present() {
    m_window->SwapBuffers();
}


void Renderer::DrawRectangle(const Rectangle &destRect, const Color &color) const {

    const std::array vertices = {
        static_cast<float>(destRect.GetX()), static_cast<float>(destRect.GetY()),
        static_cast<float>(destRect.GetX() + destRect.GetWidth()), static_cast<float>(destRect.GetY()),
        static_cast<float>(destRect.GetX() + destRect.GetWidth()), static_cast<float>(destRect.GetY() + destRect.GetHeight()),
        static_cast<float>(destRect.GetX()), static_cast<float>(destRect.GetY() + destRect.GetHeight())
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glUseProgram(m_shaderProgram);
    // Set color uniform
    glUniform4f(glGetUniformLocation(m_shaderProgram, "color"), color.GetR(), color.GetG(), color.GetB(), color.GetA());

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
