#ifndef LOADINGSCENE_H
#define LOADINGSCENE_H

#include <freetype.h>
#include <Scenes/Scene.h>
#include <Game/Game1.h>

#include "Graphics/Font.h"

class LoadingScene final : public Scene {
public:
    explicit LoadingScene(Game *game) : Scene(game) {
    }

    void Initialize() override;

    void LoadContent() override;

    void Update(GameTime &gameTime) override;

    void Draw() override;

    void UnloadContent() override;

    bool IsFinished() const { return m_finished; }

    void SetProgress(float progress); // Method to set the loading progress

private:
    Font *m_font;
    float m_progress; // Current loading progress (0.0 to 1.0)
    bool m_finished = false;
    std::string m_text;
    FT_Library m_ft;
    FT_Face m_face;
};

#endif // LOADINGSCENE_H
