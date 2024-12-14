#ifndef SPRITEFONT_H
#define SPRITEFONT_H

#include <Content/Asset.h>
#include <Graphics/Color.h>
#include <glad/glad.h>
#include <string>

class SpriteFont final : public Asset {
public:
    SpriteFont(const std::string& name, const std::string& path);
    ~SpriteFont() override;

    void DrawString(const std::string& text, float x, float y, const Color& color) const;

private:
    GLuint m_textureID; // OpenGL texture ID for the font atlas
    int m_charWidth;    // Width of each character
    int m_charHeight;   // Height of each character
};

#endif //SPRITEFONT_H