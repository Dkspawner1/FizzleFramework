#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <Scenes/Scene.h>
class SceneManager {
public:
    explicit SceneManager(Game* game);
    void ChangeScene(const std::string& sceneType);
    void Update(GameTime& gameTime) const;
    void Draw() const;


private:
    Game* m_game;
    std::unique_ptr<Scene> m_currentScene;
    std::unordered_map<std::string, std::function<std::unique_ptr<Scene>()>> m_sceneFactories;

    void InitializeSceneFactories();
};

#endif // SCENEMANAGER_H
