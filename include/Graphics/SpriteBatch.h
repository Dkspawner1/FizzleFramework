#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include "Color.h"
#include "Core/Rectangle.h"
#include "Renderer.h"

class SpriteBatch {
public:
    SpriteBatch(Renderer *renderer);

    ~SpriteBatch();

    void Begin();

    void End();

    void Draw(const Rectangle &destRect, const Color &color);

private:
    Renderer *m_renderer;
    bool m_isDrawing;
};
#endif //SPRITEBATCH_H
