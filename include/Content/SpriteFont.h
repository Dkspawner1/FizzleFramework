#ifndef SPRITEFONT_H
#define SPRITEFONT_H

#include <Content/Asset.h>
#include <Graphics/Color.h>
#include <glad/glad.h>
#include <string>
#include <unordered_map>

#include <Content/Texture.h>

struct CharInfo {
    int x;
    int y;
    int width;
    int height;
    int xoffset;
    int yoffset;
    int xadvance;
};

class SpriteFont final : public Asset {
public:
    SpriteFont(const std::string &name, const std::string &path);

    ~SpriteFont() override;

    const CharInfo *GetCharInfo(const char c) const {
        const auto it = m_charInfo.find(c);
        return (it != m_charInfo.end()) ? &it->second : nullptr;
    }

private:
    static std::string GetDirectoryPath(const std::string &filePath);

    void LoadFontFile(const std::string &path);

    void LoadTexture(const std::string &texturePath);

    int m_textureWidth;
    int m_textureHeight;
    GLuint m_textureID;
    int m_lineHeight;
    std::unordered_map<char, CharInfo> m_charInfo;
};

#endif //SPRITEFONT_H
