#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <Core/Rectangle.h>

enum class MouseState {
    LEFT_BUTTON,
    RIGHT_BUTTON,
    MIDDLE_BUTTON,
    SCROLL_UP,
    SCROLL_DOWN,
    MOUSE4,
    MOUSE5
};

class InputManager {
public:
    explicit InputManager(GLFWwindow *window);
    ~InputManager();

    bool IsKeyDown(int keyCode) const;

    bool IsKeyUp(int keyCode) const;

    bool IsMouseButtonDown(int button) const;

    bool IsMouseButtonUp(int button) const;

    Rectangle GetMousePosition() const {return Rectangle(m_mouseX,m_mouseY,1,1);}
    void SetMousePosition(double x, double y);

private:
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

    static void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset);

    static void CursorPositionCallback(GLFWwindow *window, double xPos, double yPos);

    GLFWwindow *m_window; // Change to pointer
    std::unordered_map<int, bool> m_keyStates;
    std::unordered_map<int, bool> m_mouseButtonStates;
    double m_mouseX;
    double m_mouseY;
    Rectangle m_mouseRect;
};

#endif // INPUTMANAGER_H
