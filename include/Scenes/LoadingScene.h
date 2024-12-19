#ifndef LOADINGSCENE_H
#define LOADINGSCENE_H

#include <freetype.h>
#include <Scenes/Scene.h>
#include <Game/Game1.h>
#include <sstream>
#include <iomanip>
#include "Graphics/Font.h"

class LoadingScene final : public Scene {
public:
    explicit LoadingScene(Game *game)
       : Scene(game)
       , m_font(nullptr)
       , m_progress(0.0f)
       , m_finished(false) {
        if (!game) {
            throw std::runtime_error("Invalid game pointer");
        }
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

    void DrawLoadingBar() const;
};

#endif // LOADINGSCENE_H
