#include <iostream>
#include <stb_image.h>
#include <Content/SpriteFont.h>

SpriteFont::SpriteFont(const std::string &fontPath) {
    // Load texture from file using stb_image or similar
    int width, height, nrChannels;
    unsigned char *data = stbi_load(fontPath.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Upload texture data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D); // Generate mipmaps if needed

        stbi_image_free(data); // Free image data after uploading to GPU

        // Set character width and height (assuming fixed-width font)
        m_charWidth = width / 94; // Define this based on your font atlas
        m_charHeight = height;     // Assuming single row of characters
    } else {
        std::cerr << "Failed to load font texture: " << fontPath << std::endl;
    }
}


void SpriteFont::DrawString(const std::string &text, float x, float y, const Color &color) const {
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // Set up vertex data (and buffer(s)) and configure vertex attributes
    // This is just a simple example; you would typically set this up once
    float vertices[4][4] = {
        {x, y, 0.0f, 0.0f}, // Bottom left
        {x + m_charWidth, y, 1.0f, 0.0f}, // Bottom right
        {x + m_charWidth, y + m_charHeight, 1.0f, 1.0f}, // Top right
        {x, y + m_charHeight, 0.0f, 1.0f} // Top left
    };


    // Create VAO and VBO here if not already created
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // Draw the text quad
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)1);

    glBindVertexArray(0); // Unbind VAO
}
