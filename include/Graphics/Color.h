#ifndef COLOR_H
#define COLOR_H
#include <glad/glad.h>

class Color {
    public:
    constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) : m_r(red), m_g(green), m_b(blue), m_a(alpha) {

    };

    uint8_t GetR() const { return m_r; }
    uint8_t GetG() const { return m_g; }
    uint8_t GetB() const { return m_b; }
    uint8_t GetA() const { return m_a; }

    // Predefined Colors (declarations)
    static const Color Black;
    static const Color CornflowerBlue;
    static const Color DeepPink;
    static const Color Red;
    static const Color White;

private:
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;
    uint8_t m_a;
};

// Definitions of static members
inline constexpr Color Color::Black{0, 0, 0, 255};
inline constexpr Color Color::CornflowerBlue{100, 149, 237, 255};
inline constexpr Color Color::DeepPink{255, 20, 147, 255};
inline constexpr Color Color::Red{255, 0, 0, 255};
inline constexpr Color Color::White{255, 255, 255, 255};

#endif //COLOR_H
