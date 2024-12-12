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
    glGenBuffers(1,&m_texCoordVbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Set up vertex attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);


    // Vertex Shader
    const char *vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    layout (location = 1) in vec2 aTexCoord; // Add this line for texture coordinates

    out vec2 TexCoords; // Output to fragment shader

    void main() {
        gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
        TexCoords = aTexCoord; // Pass texture coordinates to fragment shader
    }
)";
    const char *fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
in vec2 TexCoords; // Texture coordinates from vertex shader
uniform sampler2D texture1; // Texture sampler
uniform vec4 color; // Color uniform

void main() {
    vec4 texColor = texture(texture1, TexCoords); // Sample the texture
    FragColor = texColor * color; // Multiply texture color by the uniform color
}
)";

    // Fragment Shader

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::CheckShaderCompilation(GLuint shader, const char *shaderType) const {
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

void Renderer::SetClearColor(const Color &color) const {
    glClearColor(color.GetR() / 255.0f, color.GetG() / 255.0f, color.GetB() / 255.0f, color.GetA() / 255.0f);
}


void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Present() {
    m_window->SwapBuffers();
}

void Renderer::DrawTexture(const Texture &texture, const Rectangle &destRect, const Color &color) const {
    float normalizedX, normalizedY, normalizedWidth, normalizedHeight;

    // Get window dimensions
    int windowWidth = m_window->GetWidth();
    int windowHeight = m_window->GetHeight();

    // Convert rectangle coordinates to normalized device coordinates
    ConvertToNormalizedDeviceCoordinates(destRect, windowWidth, windowHeight,
                                         normalizedX, normalizedY,
                                         normalizedWidth, normalizedHeight);

    const std::array<float, 8> vertices = {
        normalizedX, normalizedY,
        normalizedX + normalizedWidth, normalizedY,
        normalizedX + normalizedWidth, normalizedY - normalizedHeight,
        normalizedX, normalizedY - normalizedHeight
    };

    const std::array<float, 8> texCoords = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    // Bind vertex buffer and upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    // Set up vertex attributes for position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Bind and upload texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordVbo);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);

    // Bind the texture and set uniforms
    texture.Bind();

    glUseProgram(m_shaderProgram);

    // Set color uniform (ensure values are between [0.0f - 1.0f])
    glUniform4f(glGetUniformLocation(m_shaderProgram, "color"),
                color.GetR() / 255.0f,
                color.GetG() / 255.0f,
                color.GetB() / 255.0f,
                color.GetA() / 255.0f);

    glBindVertexArray(m_vao);

    // Draw with texture
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Renderer::DrawRectangle(const Rectangle &destRect, const Color &color) const {
    float normalizedX, normalizedY, normalizedWidth, normalizedHeight;

    // Get the window dimensions
    int windowWidth = m_window->GetWidth();
    int windowHeight = m_window->GetHeight();
    // Convert rectangle coordinates to normalized device coordinates
    ConvertToNormalizedDeviceCoordinates(destRect, windowWidth, windowHeight, normalizedX, normalizedY, normalizedWidth,
                                         normalizedHeight);
    const std::array<float, 8> vertices = {
        normalizedX, normalizedY,
        normalizedX + normalizedWidth, normalizedY,
        normalizedX + normalizedWidth, normalizedY - normalizedHeight,
        normalizedX, normalizedY - normalizedHeight
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glUseProgram(m_shaderProgram);

    // Set color uniform
    glUniform4f(glGetUniformLocation(m_shaderProgram, "color"), color.GetR(), color.GetG(), color.GetB(), color.GetA());

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Renderer::ConvertToNormalizedDeviceCoordinates(const Rectangle &rect, int windowWidth, int windowHeight,
                                                    float &outX, float &outY, float &outWidth, float &outHeight) const {
    // Convert X
    outX = (rect.GetX() / (windowWidth / 2.0f)) - 1.0f;
    // Convert Y (inverted)
    outY = 1.0f - (rect.GetY() / (windowHeight / 2.0f));

    // Convert width and height from pixel space to NDC
    outWidth = rect.GetWidth() / (windowWidth / 2.0f);
    outHeight = rect.GetHeight() / (windowHeight / 2.0f);
}
