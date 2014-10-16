#include "card.hpp"

Card::Card(const Card& card)
    : color(card.color.r, card.color.g, card.color.b) {}

Card::Card(const Color& color)
    : color(color) {}

Card::Card(const FrequentColor colorName)
    : color(colorName) {}

bool Card::hasSameColorAs(const Card& card)
{
    return color.isSameColorAs(card.color);
}
