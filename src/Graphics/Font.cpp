// Font.cpp
#include <iostream>
#include <Graphics/Font.h>
#include <stdexcept>

Font::Font(const std::string& name, const std::string& path, int fontSize) : Asset(name), m_isLoaded(false) {
    if (FT_Init_FreeType(&m_ft)) {
        throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
    }

    if (FT_New_Face(m_ft, path.c_str(), 0, &m_face)) {
        throw std::runtime_error("ERROR::FREETYPE: Failed to load font");
    }

    FT_Set_Pixel_Sizes(m_face, 0, fontSize);
    LoadCharacters();
    m_isLoaded = true;
}

Font::~Font() {
    for (auto& [_, character] : m_characters) {
        delete character.texture;
    }
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ft);
}

void Font::LoadCharacters() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER)) {
            std::cerr << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        auto* texture = new Texture(std::string(1, c),
                                  m_face->glyph->bitmap.buffer,
                                  m_face->glyph->bitmap.width,
                                  m_face->glyph->bitmap.rows);

        Character character = {
            texture,
            {static_cast<int>(m_face->glyph->bitmap.width),
             static_cast<int>(m_face->glyph->bitmap.rows)},
            {m_face->glyph->bitmap_left,
             m_face->glyph->bitmap_top},
            static_cast<unsigned int>(m_face->glyph->advance.x)
        };

        m_characters.insert(std::pair<char, Character>(c, character));
    }
}
