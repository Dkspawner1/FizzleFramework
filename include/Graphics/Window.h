#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(const std::string &title, int width, int height);
    ~Window();

    bool ShouldClose() const;
    void SwapBuffers();
    void PollEvents();

private:
    GLFWwindow *m_window;
    void CenterWindow(GLFWwindow* window, int width, int height);
};
#endif // WINDOW_H