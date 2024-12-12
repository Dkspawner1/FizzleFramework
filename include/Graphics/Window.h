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
    bool ShouldClose() const;
    void SwapBuffers();
    void PollEvents();
    void SetFullScreen(bool fullscreen);

    GLFWwindow* GetGLFWWindow() const { return m_window; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

private:
    GLFWwindow *m_window;
    void CenterWindow(GLFWwindow *window, int width, int height);
    int m_width;
    int m_height;
    std::string m_title;
};
#endif // WINDOW_H