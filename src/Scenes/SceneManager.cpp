#include <Scenes/SceneManager.h>
#include <Scenes/GameScene.h>
#include <Scenes/MenuScene.h>
#include <Scenes/LoadingScene.h>

void SceneManager::InitializeSceneFactories() {
    m_sceneFactories["Loading"] = [this]() { return std::make_unique<LoadingScene>(m_game); };
    m_sceneFactories["Menu"] = [this]() { return std::make_unique<MenuScene>(m_game); };
    m_sceneFactories["Game"] = [this]() { return std::make_unique<GameScene>(m_game); };
}

void SceneManager::ChangeScene(const std::string& sceneType) {
    auto it = m_sceneFactories.find(sceneType);
    if (it != m_sceneFactories.end()) {
        if (m_currentScene) {
            m_currentScene->UnloadContent(); // Unload current scene content
        }

        m_currentScene = it->second(); // Create the new scene
        m_currentScene->Initialize(); // Initialize the new scene
        m_currentScene->LoadContent(); // Load content for the new scene
    } else {
        throw std::invalid_argument("Invalid scene type: " + sceneType);
    }
}
void SceneManager::ChangeToLoadingScene() {
    if (m_currentScene) {
        m_currentScene->UnloadContent(); // Unload current scene content if necessary
    }

    m_currentScene = std::make_unique<LoadingScene>(m_game); // Create and set the loading scene
    m_currentScene->Initialize();
}

void SceneManager::Update(GameTime& gameTime) {
    if (m_currentScene) {
        m_currentScene->Update(gameTime); // Update the current scene
    }
}

void SceneManager::Draw() {
    if (m_currentScene) {
        m_currentScene->Draw(); // Draw the current scene
    }
}
