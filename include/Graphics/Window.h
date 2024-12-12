// Window.h
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(const std::string &title, int width, int height);
    ~Window();

    void Initialize();
    [[nodiscard]] bool ShouldClose() const;
    void SwapBuffers();
    void PollEvents();
    void SetFullScreen(bool fullscreen);

    [[nodiscard]] GLFWwindow* GetGLFWWindow() const { return m_window; }
    [[nodiscard]] int GetWidth() const { return m_width; }
    [[nodiscard]] int GetHeight() const { return m_height; }

private:
    GLFWwindow *m_window;
    void CenterWindow(GLFWwindow *window, int width, int height);
    int m_width;
    int m_height;
    std::string m_title;
};
#endif // WINDOW_H