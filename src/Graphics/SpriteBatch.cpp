#include <stdexcept>
#include <Graphics/SpriteBatch.h>


SpriteBatch::SpriteBatch(Renderer *renderer): m_renderer(renderer), m_isDrawing(false) {
}

SpriteBatch::~SpriteBatch() = default;

void SpriteBatch::Begin() {
    if (m_isDrawing) {
        throw std::runtime_error("SpriteBatch::Begin called while already drawing");
    }
    m_isDrawing = true;
}

void SpriteBatch::End() {
    if (!m_isDrawing) {
        throw std::runtime_error("SpriteBatch::End called without matching Begin");
    }
    m_isDrawing = false;
}

void SpriteBatch::Draw(const Texture &texture, const Rectangle &destRect, const Color &color) const {
    if (!m_isDrawing) {
        throw std::runtime_error("SpriteBatch::Draw called while not drawing");
    }

    m_renderer->DrawTexture(texture, destRect, color);
}

void SpriteBatch::Draw(const Rectangle &destRect, const Color &color) const {
    if (!m_isDrawing) {
        throw std::runtime_error("SpriteBatch::Draw called without Begin");
    }
    m_renderer->DrawRectangle(destRect, color);
}

void SpriteBatch::DrawString(const Font& font, const std::string& text,
                           float x, float y, float scale, const Color& color) const {
    if (!m_isDrawing) {
        throw std::runtime_error("SpriteBatch::DrawString called without Begin()");
    }

    const auto& characters = font.GetCharacters();
    float baselineY = y; // Store the baseline y-position

    for (char c : text) {
        const Character& ch = characters.at(c);

        // Calculate position with proper baseline alignment
        float xpos = x + ch.Bearing[0] * scale;
        float ypos = baselineY - ch.Bearing[1] * scale; // Subtract bearing from baseline

        float w = ch.Size[0] * scale;
        float h = ch.Size[1] * scale;

        Rectangle srcRect(0, 0, ch.Size[0], ch.Size[1]);
        Rectangle destRect(xpos, ypos, w, h);

        m_renderer->DrawFontTexture(*ch.texture, srcRect, destRect, color);

        x += (ch.Advance >> 6) * scale;
    }
}