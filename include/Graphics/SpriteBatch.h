#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include <Graphics/Color.h>
#include <Core/Rectangle.h>
#include <Graphics/Renderer.h>
#include <Content/Texture.h>


class SpriteBatch {
public:
    explicit SpriteBatch(Renderer *renderer);

    ~SpriteBatch();

    void Begin();

    void End();

    // Draw a texture sized to a rectangle
    void Draw(const Texture &texture, const Rectangle &destRect, const Color &color) const;

    // Draws a colored rectangle
    void Draw(const Rectangle &destRect, const Color &color) const;

    // Draws text to the screen with a provided font: *.fnt& | .*tga
    // void DrawString(const SpriteFont &font, const std::string &text, float x, float y, const Color &color);

private:
    Renderer *m_renderer;
    bool m_isDrawing;
};
#endif //SPRITEBATCH_H
