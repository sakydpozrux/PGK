#ifndef CARD_HPP
#define CARD_HPP

#include "color.hpp"

class Card
{
public:
    Card(const Card& card);
    Card(const Color& color);
    Card(const FrequentColor colorName);

    bool hasSameColorAs(const Card& card);

    Color color;
};

#endif // CARD_HPP
