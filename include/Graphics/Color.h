#ifndef COLOR_H
#define COLOR_H
#include <stdint.h>

class Color {
public:
    constexpr Color(const uint8_t red, const uint8_t green, const uint8_t blue,
                    const uint8_t alpha = 255) : m_r(red), m_g(green),
                                                 m_b(blue), m_a(alpha) {
    };

    static constexpr Color FromPredefined(const Color &predefined) {
        return predefined;
    }

    [[nodiscard]] uint8_t GetR() const { return m_r; }
    [[nodiscard]] uint8_t GetG() const { return m_g; }
    [[nodiscard]] uint8_t GetB() const { return m_b; }
    [[nodiscard]] uint8_t GetA() const { return m_a; }

    // Predefined Colors (declarations)
    static const Color Black;
    static const Color CornflowerBlue;
    static const Color DarkGray;
    static const Color DeepPink;
    static const Color Gray;
    static const Color Red;
    static const Color Transparent;
    static const Color White;

private:
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;
    uint8_t m_a;
};

// Definitions of static members
constexpr Color Color::Black{0, 0, 0};
constexpr Color Color::CornflowerBlue{100, 149, 237};
constexpr Color Color::DarkGray{169, 169, 169};
constexpr Color Color::DeepPink{255, 20, 147};
constexpr Color Color::Gray{128, 128, 128};
constexpr Color Color::Red{255, 0, 0};
constexpr Color Color::Transparent{0, 0, 0, 0};
constexpr Color Color::White{255, 255, 255};

#endif //COLOR_H
