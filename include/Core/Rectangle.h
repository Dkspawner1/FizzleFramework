#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
    // Constructor to initialize the rectangle's position and size
    Rectangle(int x, int y, int width, int height)
        : m_x(x), m_y(y), m_width(width), m_height(height) {
    }
    Rectangle() : m_x(0), m_y(0), m_width(0), m_height(0) {}

    // Destructor
    ~Rectangle() {
    }

    // Setters
    void SetRectangle(int x, int y, int width, int height) {
        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;
    }

    // Getters
    int GetX() const { return m_x; }
    int GetY() const { return m_y; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

    // Operator overloads
    bool operator==(const Rectangle &other) const {
        return (m_x == other.m_x && m_y == other.m_y && m_width == other.m_width && m_height == other.m_height);
    }

    bool operator!=(const Rectangle &other) const {
        return !(*this == other);
    }

    bool intersects(const Rectangle &other) const {
        return (m_x < other.m_x + other.m_width &&
                m_x + m_width > other.m_x &&
                m_y < other.m_y + other.m_height &&
                m_y + m_height > other.m_y);
    }

private:
    int m_x; // X position
    int m_y; // Y position
    int m_width; // Width of the rectangle
    int m_height; // Height of the rectangle
};

#endif // RECTANGLE_H
