#ifndef GRAPHICSDEVICEMANAGER_H
#define GRAPHICSDEVICEMANAGER_H
#include <memory>

#include <Graphics/Renderer.h>
#include <Graphics/Window.h>

class GraphicsDeviceManager {
public:
    GraphicsDeviceManager(const std::string&title = "Game", int width = 1600, int height = 900);

    ~GraphicsDeviceManager();

    void Initialize();
    void BeginDraw();
    void EndDraw();
    bool IsFullScreen() const;
    void ToggleFullScreen();

    Window* GetWindow() {return m_window.get();}
    Renderer* GetRenderer() {return m_renderer.get();}
private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    bool m_isFullScreen;
};

#endif //GRAPHICSDEVICEMANAGER_H
