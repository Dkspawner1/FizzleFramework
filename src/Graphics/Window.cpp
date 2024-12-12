#include <Graphics/Window.h>
#include <stdexcept>

Window::Window(const std::string &title, int width, int height)
    : m_width(width), m_height(height), m_title(title)
{
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW3");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // Hide the window initially

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW3 window");
    }

    CenterWindow(m_window, width, height);
    glfwShowWindow(m_window);
    glfwMakeContextCurrent(m_window);
}

Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::Initialize() {
    // Create OpenGL context
    glfwMakeContextCurrent(m_window);

    // Now it's safe to initialize GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(m_window);
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::SetFullScreen(bool fullscreen) {
    if (fullscreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        glfwSetWindowMonitor(m_window, nullptr, 100, 100, m_width, m_height, 0);
        CenterWindow(m_window, m_width, m_height);
    }
}

void Window::CenterWindow(GLFWwindow* window, int width, int height) {
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    int xPos = (mode->width - width) / 2;
    int yPos = (mode->height - height) / 2;

    glfwSetWindowPos(window, xPos, yPos);
}