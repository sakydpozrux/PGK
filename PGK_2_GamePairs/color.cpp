#include "color.hpp"

Color::Color(double red, double green, double blue)
    : r(red), g(green), b(blue) {}

Color::Color(const FrequentColor color)
{
    r = frequentColors().at(color).r;
    g = frequentColors().at(color).g;
    b = frequentColors().at(color).b;
}

std::list<Color> Color::frequentColorsNames()
{
    std::list<Color> frequentColorsNames;

    for (auto it = frequentColors().begin(); it != frequentColors().end(); ++it)
    {
        frequentColorsNames.push_back(it->first);
    }

    return frequentColorsNames;
}

std::map<FrequentColor, Color> Color::frequentColors()
{
    static const std::map<FrequentColor, Color> colors =
    {
        { RED    , Color(1.00f, 0.00f, 0.00f) },
        { YELLOW , Color(1.00f, 1.00f, 0.00f) },
        { GREEN  , Color(0.00f, 1.00f, 0.00f) },
        { BLUE   , Color(0.00f, 0.00f, 1.00f) },
        { PURPLE , Color(0.61f, 0.19f, 1.00f) },
        { BLACK  , Color(0.00f, 0.00f, 0.00f) },
        { WHITE  , Color(1.00f, 1.00f, 1.00f) },
        { ORANGE , Color(0.89f, 0.47f, 0.20f) }
    };

    return colors;
}
