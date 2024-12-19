#include <array>
#include <Graphics/Renderer.h>
#include <stdexcept>

Renderer::Renderer(Window *window) : m_window(window), m_vao(0), m_vbo(0), m_textureShaderProgram(0) {
    // Don't perform OpenGL operations here
}

Renderer::~Renderer() {
    if (m_vao != 0)
        glDeleteVertexArrays(1, &m_vao);
    if (m_vbo != 0)
        glDeleteBuffers(1, &m_vbo);
    if (m_textureShaderProgram != 0)
        glDeleteProgram(m_textureShaderProgram);
}

void Renderer::Initialize() {
    // Create and bind VAO and VBO
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_texCoordVbo);

    glBindVertexArray(m_vao);

    // Position attribute setup
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute setup
    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordVbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(1);

    // Regular texture shader setup
    const char *vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec2 aTexCoord;
        out vec2 TexCoords;

        void main() {
            gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
            TexCoords = aTexCoord;
        }
    )";

    const char *fragmentShaderSource = R"(
        #version 330 core
        in vec2 TexCoords;
        out vec4 FragColor;
        uniform sampler2D texture1;
        uniform vec4 color;

        void main() {
            vec4 texColor = texture(texture1, TexCoords);
            FragColor = texColor * color;
        }
    )";

    // Font shader setup
    const char *fontVertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec2 aTexCoord;
        out vec2 TexCoords;

        void main() {
            gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
            TexCoords = aTexCoord;
        }
    )";

    const char *fontFragmentShaderSource = R"(
    #version 330 core
    in vec2 TexCoords;
    out vec4 FragColor;

    uniform sampler2D text;
    uniform vec4 textColor;

    void main() {
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
        FragColor = textColor * sampled;
    }
)";

    // Compile regular texture shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    CheckShaderCompilation(vertexShader, "Texture Vertex");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    CheckShaderCompilation(fragmentShader, "Texture Fragment");

    // Create and link texture shader program
    m_textureShaderProgram = glCreateProgram();
    glAttachShader(m_textureShaderProgram, vertexShader);
    glAttachShader(m_textureShaderProgram, fragmentShader);
    glLinkProgram(m_textureShaderProgram);
    CheckProgramLinking(m_textureShaderProgram);

    // Clean up texture shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Compile font shaders
    GLuint fontVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fontVertexShader, 1, &fontVertexShaderSource, nullptr);
    glCompileShader(fontVertexShader);
    CheckShaderCompilation(fontVertexShader, "Font Vertex");

    GLuint fontFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fontFragmentShader, 1, &fontFragmentShaderSource, nullptr);
    glCompileShader(fontFragmentShader);
    CheckShaderCompilation(fontFragmentShader, "Font Fragment");

    // Create and link font shader program
    m_fontShaderProgram = glCreateProgram();
    glAttachShader(m_fontShaderProgram, fontVertexShader);
    glAttachShader(m_fontShaderProgram, fontFragmentShader);
    glLinkProgram(m_fontShaderProgram);
    CheckProgramLinking(m_fontShaderProgram);

    // Clean up font shaders
    glDeleteShader(fontVertexShader);
    glDeleteShader(fontFragmentShader);

    // Set default texture units
    glUseProgram(m_textureShaderProgram);
    glUniform1i(glGetUniformLocation(m_textureShaderProgram, "texture1"), 0);

    glUseProgram(m_fontShaderProgram);
    glUniform1i(glGetUniformLocation(m_fontShaderProgram, "text"), 0);

    // Enable blending for transparency
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
    Rectangle srcRect(0, 0, texture.GetWidth(), texture.GetHeight());
    DrawTexture(texture, srcRect, destRect, color);
}

void Renderer::DrawTexture(const Texture &texture, const Rectangle &srcRect, const Rectangle &destRect,
                           const Color &color) const {
    float normalizedX;
    float normalizedY;
    float normalizedWidth;
    float normalizedHeight;

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
        static_cast<float>(srcRect.GetX()) / texture.GetWidth(),
        static_cast<float>(srcRect.GetY()) / texture.GetHeight(),
        static_cast<float>(srcRect.GetX() + srcRect.GetWidth()) / texture.GetWidth(),
        static_cast<float>(srcRect.GetY()) / texture.GetHeight(),
        static_cast<float>(srcRect.GetX() + srcRect.GetWidth()) / texture.GetWidth(),
        static_cast<float>(srcRect.GetY() + srcRect.GetHeight()) / texture.GetHeight(),
        static_cast<float>(srcRect.GetX()) / texture.GetWidth(),
        static_cast<float>(srcRect.GetY() + srcRect.GetHeight()) / texture.GetHeight()
    };


    // Bind vertex buffer and upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    // Set up vertex attributes for position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    // Bind and upload texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordVbo);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(1);

    // Bind the texture and set uniforms
    texture.Bind();

    glUseProgram(m_textureShaderProgram);

    // Set color uniform (ensure values are between [0.0f - 1.0f])
    glUniform4f(glGetUniformLocation(m_textureShaderProgram, "color"),
                color.GetR() / 255.0f,
                color.GetG() / 255.0f,
                color.GetB() / 255.0f,
                color.GetA() / 255.0f);

    glBindVertexArray(m_vao);

    // Draw with texture
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Renderer::DrawRectangle(const Rectangle &destRect, const Color &color) const {
    float normalizedX;
    float normalizedY;
    float normalizedWidth;
    float normalizedHeight;

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

    glUseProgram(m_textureShaderProgram);

    // Set color uniform
    glUniform4f(glGetUniformLocation(m_textureShaderProgram, "color"), color.GetR(), color.GetG(), color.GetB(),
                color.GetA());

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

void Renderer::DrawFontTexture(const Texture& texture, const Rectangle& srcRect,
                             const Rectangle& destRect, const Color& color) const {
    float normalizedX, normalizedY, normalizedWidth, normalizedHeight;

    int windowWidth = m_window->GetWidth();
    int windowHeight = m_window->GetHeight();

    ConvertToNormalizedDeviceCoordinates(destRect, windowWidth, windowHeight,
                                       normalizedX, normalizedY,
                                       normalizedWidth, normalizedHeight);

    // Flip the Y coordinates to correct text orientation
    const std::array<float, 8> vertices = {
        normalizedX, normalizedY,                      // top-left
        normalizedX + normalizedWidth, normalizedY,    // top-right
        normalizedX + normalizedWidth, normalizedY - normalizedHeight,  // bottom-right
        normalizedX, normalizedY - normalizedHeight    // bottom-left
    };

    // Updated texture coordinates for correct orientation
    // Correct texture coordinates for proper glyph rendering
    const std::array<float, 8> texCoords = {
        0.0f, 0.0f,  // top-left
        1.0f, 0.0f,  // top-right
        1.0f, 1.0f,  // bottom-right
        0.0f, 1.0f   // bottom-left
    };


    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordVbo);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_DYNAMIC_DRAW);

    texture.Bind();
    glUseProgram(m_fontShaderProgram);

    glUniform4f(glGetUniformLocation(m_fontShaderProgram, "textColor"),
                color.GetR() / 255.0f,
                color.GetG() / 255.0f,
                color.GetB() / 255.0f,
                color.GetA() / 255.0f);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}