#ifndef GAMETIME_H
#define GAMETIME_H
#include <chrono>

class GameTime {
public:
    GameTime();

    void Update();

    float GetElapsedTime() const;

    float GetTotalTime() const;

    float GetDeltaTime() const;

private:
    std::chrono::steady_clock::time_point m_startTime;
    std::chrono::steady_clock::time_point m_lastUpdateTime;
    float m_elapsedTime;
    float m_totalTime;
    float m_deltaTime;
};

#endif //GAMETIME_H
