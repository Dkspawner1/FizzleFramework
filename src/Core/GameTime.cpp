#include <Core/GameTime.h>

GameTime::GameTime() : m_startTime(std::chrono::steady_clock::now()), m_lastUpdateTime(m_startTime),
                       m_elapsedTime(0.0f), m_totalTime(0.0f), m_deltaTime(0.0f) {
}

void GameTime::Update() {
    const auto currentTime = std::chrono::steady_clock::now();
    m_deltaTime = std::chrono::duration<float>(currentTime - m_lastUpdateTime).count();
    m_totalTime = std::chrono::duration<float>(currentTime - m_startTime).count();
    m_elapsedTime += m_deltaTime;
    m_lastUpdateTime = currentTime;
}

float GameTime::GetElapsedTime() const { return m_elapsedTime; }
float GameTime::GetTotalTime() const { return m_totalTime; }
float GameTime::GetDeltaTime() const { return m_deltaTime; }
