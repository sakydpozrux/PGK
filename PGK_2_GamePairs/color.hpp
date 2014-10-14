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
    Color(const FrequentColor color);

    static std::list<Color> frequentColorsNames();
    static std::map<FrequentColor, Color> frequentColors();
};

#endif // COLOR_HPP
