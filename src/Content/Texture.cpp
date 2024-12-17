#include <Content/Texture.h>
#include <stdexcept>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string &name, const std::string &path) : Asset(name), m_width(0), m_height(0) {
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // Set the texture's parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &m_width, &m_height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        throw std::runtime_error("Failed to load texture: " + path);
    }

    const GLenum format = (nrChannels == 1) ? GL_RED : (nrChannels == 3) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}


Texture::Texture(const std::string &name, unsigned char *buffer, int width, int height)
    : Asset(name), m_width(width), m_height(height) {
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // Set texture parameters specifically for font rendering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload texture data
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Important for font textures
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_textureID);
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}
