#ifndef COLOR_HPP
#define COLOR_HPP

#include <list>
#include <map>

enum FrequentColor
{
    RED, YELLOW, GREEN, BLUE, PURPLE, BLACK, WHITE, ORANGE
};

class Color
{
public:
    double r, g, b;

    Color(double red, double green, double blue);
    Color(const Color& color);
    Color(const FrequentColor colorName);

    bool isSameColorAs(const Color& color);

    static std::list<Color> frequentColorsNames();
    static std::map<FrequentColor, Color> frequentColors();
};

#endif // COLOR_HPP
