#ifndef SPRITEFONT_H
#define SPRITEFONT_H

#include <Content/Asset.h>
#include <Graphics/Color.h>
#include <glad/glad.h>
#include <string>
#include <unordered_map>

#include "Texture.h"

struct CharInfo {
    int x, y, width, height, xoffset, yoffset, xadvance;
};

class SpriteFont final : public Asset {
public:
    SpriteFont(const std::string& name, const std::string& path);
    virtual ~SpriteFont() override;
    void DrawString(const std::string& text, float x, float y, const Color& color) const;
    const CharInfo* GetCharInfo(char c) const {
        auto it = m_charInfo.find(c);
        return (it != m_charInfo.end()) ? &it->second : nullptr;
    }

private:
    static std::string GetDirectoryPath(const std::string& filePath);
    void LoadFontFile(const std::string& path);
    void LoadTexture(const std::string& texturePath);

    GLuint m_textureID;
    int m_lineHeight;
    std::unordered_map<char, CharInfo> m_charInfo;
};

#endif //SPRITEFONT_H
