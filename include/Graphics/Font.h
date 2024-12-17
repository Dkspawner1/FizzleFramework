#ifndef FONT_H
#define FONT_H

#include <Content/Asset.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <unordered_map>
#include <Graphics/Color.h>

#include "Content/Texture.h"

struct Character {
    Texture* texture;
    int Size[2];
    int Bearing[2];
    unsigned int Advance;
};
class Font : public Asset {
public:
    Font(const std::string& name, const std::string& path, int fontSize);
    ~Font() override;

    bool IsLoaded() const { return m_isLoaded; }
    const std::unordered_map<char, Character>& GetCharacters() const { return m_characters; }

private:
    FT_Library m_ft;
    FT_Face m_face;
    std::unordered_map<char, Character> m_characters;
    bool m_isLoaded;

    void LoadCharacters();
};

#endif //FONT_H
