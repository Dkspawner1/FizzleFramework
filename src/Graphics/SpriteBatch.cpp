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

void SpriteBatch::Draw(const Texture &texture, const Rectangle &destRect, const Color &color) {
    if (!m_isDrawing) {
        throw std::runtime_error("SpriteBatch::Draw called while not drawing");
    }

    m_renderer->DrawTexture(texture, destRect, color);
}

void SpriteBatch::Draw(const Rectangle &destRect, const Color &color) {
    if (!m_isDrawing) {
        throw std::runtime_error("SpriteBatch::Draw called without Begin");
    }
    m_renderer->DrawRectangle(destRect, color);
}
