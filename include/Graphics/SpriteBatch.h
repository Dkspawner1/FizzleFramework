#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include <Graphics/Color.h>
#include <Core/Rectangle.h>
#include <Graphics/Renderer.h>

class SpriteBatch {
public:
    explicit SpriteBatch(Renderer *renderer);
    ~SpriteBatch();
    void Begin();
    void End();
    void Draw(const Rectangle &destRect, const Color &color);

private:
    Renderer *m_renderer;
    bool m_isDrawing;
};
#endif //SPRITEBATCH_H
