#include <Scenes/SceneManager.h>
#include <Scenes/GameScene.h>
#include <Scenes/MenuScene.h>
#include <Scenes/LoadingScene.h>
#include <stdexcept>

SceneManager::SceneManager(Game* game) : m_game(game) {
    InitializeSceneFactories();
}

void SceneManager::InitializeSceneFactories() {
    m_sceneFactories["Loading"] = [this]() { return std::make_unique<LoadingScene>(m_game); };
    m_sceneFactories["Menu"] = [this]() { return std::make_unique<MenuScene>(m_game); };
    m_sceneFactories["Game"] = [this]() { return std::make_unique<GameScene>(m_game); };
}

void SceneManager::ChangeScene(const std::string& sceneType) {
    if (const auto it = m_sceneFactories.find(sceneType); it != m_sceneFactories.end()) {
        if (m_currentScene) {
            m_currentScene->UnloadContent();
        }
        m_currentScene = it->second();
        m_currentScene->Initialize();
        m_currentScene->LoadContent();
    } else {
        throw std::invalid_argument("Invalid scene type: " + sceneType);
    }
}

void SceneManager::Update(GameTime& gameTime) const {
    if (m_currentScene) {
        m_currentScene->Update(gameTime);
    }
}

void SceneManager::Draw() const {
    if (m_currentScene) {
        m_currentScene->Draw();
    }
}
