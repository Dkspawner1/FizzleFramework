#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <functional>
#include <unordered_map>
#include <Scenes/Scene.h>

class Game1; // Forward declaration of Game1

class SceneManager {
public:
    explicit SceneManager(Game1* game) : m_game(game) { InitializeSceneFactories(); }

    void ChangeScene(const std::string& sceneType);

    void ChangeToLoadingScene();

    void Update(GameTime& gameTime);
    void Draw();

private:
    Game1* m_game;
    std::unique_ptr<Scene> m_currentScene;
    std::unordered_map<std::string, std::function<std::unique_ptr<Scene>()>> m_sceneFactories;

    void InitializeSceneFactories();
};

#endif // SCENEMANAGER_H
