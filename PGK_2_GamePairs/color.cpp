#include "color.hpp"

Color::Color(double red, double green, double blue)
    : r(red), g(green), b(blue) {}

Color::Color(const Color& color)
    : Color(color.r, color.g, color.b) {}

Color::Color(const FrequentColor colorName)
    : Color(frequentColors().at(colorName)) {}

Color::Color(const Color& color, float darkness)
    : Color(color.r + darkness,
            color.g + darkness,
            color.b + darkness) {}

bool Color::isSameColorAs(const Color& color) const
{
    return r == color.r && g == color.g && b == color.b;
}

std::list<Color> Color::frequentColorsNames()
{
    std::list<Color> frequentColorsNames;

    for (auto it = frequentColors().begin(); it != frequentColors().end(); ++it)
        frequentColorsNames.push_back(it->first);

    return frequentColorsNames;
}

std::map<FrequentColor, Color> Color::frequentColors()
{
    static const std::map<FrequentColor, Color> colors =
    {
        { RED    , Color(0.90f, 0.00f, 0.00f) },
        { YELLOW , Color(0.90f, 0.90f, 0.00f) },
        { GREEN  , Color(0.00f, 0.90f, 0.00f) },
        { BLUE   , Color(0.00f, 0.00f, 0.90f) },
        { PURPLE , Color(0.61f, 0.19f, 0.90f) },
        { BLACK  , Color(0.00f, 0.00f, 0.00f) },
        { WHITE  , Color(0.90f, 0.90f, 0.90f) },
        { ORANGE , Color(0.89f, 0.47f, 0.20f) }
    };

    return colors;
}
