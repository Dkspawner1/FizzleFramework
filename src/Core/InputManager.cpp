#include <Core/InputManager.h>

InputManager::InputManager(GLFWwindow *window) : m_window(window), m_mouseX(0), m_mouseY(0) {
    // Set the user pointer to this instance for callback access
    glfwSetWindowUserPointer(window, this);
    // Set GLFW callbacks
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetCursorPosCallback(window, CursorPositionCallback);
}

InputManager::~InputManager() {
    // Reset callbacks to avoid dangling pointers
    glfwSetKeyCallback(m_window, nullptr);
    glfwSetMouseButtonCallback(m_window, nullptr);
    glfwSetScrollCallback(m_window, nullptr);
    glfwSetCursorPosCallback(m_window, nullptr);
}

// Return true if key is pressed
bool InputManager::IsKeyDown(int keyCode) const {
    const auto it = m_keyStates.find(keyCode);
    return it != m_keyStates.end() && it->second;
}

// Return true if key is not pressed
bool InputManager::IsKeyUp(int keyCode) const {
    const auto it = m_keyStates.find(keyCode);
    return it == m_keyStates.end() || !it->second;
}

// Return true if mouse button is pressed
bool InputManager::IsMouseButtonDown(int button) const {
    auto it = m_mouseButtonStates.find(button);
    return it != m_mouseButtonStates.end() && it->second;
}

// Return true if mouse button is not pressed
bool InputManager::IsMouseButtonUp(int button) const {
    auto it = m_mouseButtonStates.find(button);
    return it == m_mouseButtonStates.end() || !it->second;
}

void InputManager::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto *inputManager = static_cast<InputManager *>(glfwGetWindowUserPointer(window));

    // Update the key state based on action (press/release)
    switch (action) {
        case GLFW_PRESS:
            inputManager->m_keyStates[key] = true;
            break;
        case GLFW_RELEASE:
            inputManager->m_keyStates[key] = false;
            break;
    }
}

void InputManager::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    auto *inputManager = static_cast<InputManager *>(glfwGetWindowUserPointer(window));
    // Update the mouse button state based on action (press/release)
    switch (action) {
        case GLFW_PRESS:
            inputManager->m_mouseButtonStates[button] = true;
            break;
        case GLFW_RELEASE:
            inputManager->m_mouseButtonStates[button] = false;
            break;
    }
}

void InputManager::GetMousePosition(double &x, double &y) const {
    x = m_mouseX;
    y = m_mouseY;
}

void InputManager::SetMousePosition(const double x, const double y) {
    glfwSetCursorPos(m_window, x, y);
}


void InputManager::ScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    // TODO: impl
}

void InputManager::CursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
    auto *inputManager = static_cast<InputManager *>(glfwGetWindowUserPointer(window));
    inputManager->m_mouseX = xPos;
    inputManager->m_mouseY = yPos;
}
