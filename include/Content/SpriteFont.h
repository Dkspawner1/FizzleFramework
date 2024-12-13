#ifndef SPRITEFONT_H
#define SPRITEFONT_H

#include <string>
#include <Graphics/Color.h>
#include <glad/glad.h>

class SpriteFont {
public:
    explicit SpriteFont(const std::string &fontPath); // Constructor declaration

    void DrawString(const std::string &text, float x, float y, const Color &color) const;

private:
    GLuint m_textureID; // OpenGL texture ID for the font atlas
    int m_charWidth;    // Width of each character
    int m_charHeight;   // Height of each character
};

#endif //SPRITEFONT_H
