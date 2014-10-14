#ifndef CARD_HPP
#define CARD_HPP

#include "color.hpp"

class Card
{
public:
    Card(const Card& card);
    Card(const Color& color);

    Color color;
};

#endif // CARD_HPP
