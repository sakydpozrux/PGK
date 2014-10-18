#include "card.hpp"

unsigned int Card::lastUniqueId = 0;

Card::Card(const Card& card)
    : color(card.color.r, card.color.g, card.color.b),
      uniqueId(card.uniqueId),
      presentOnBoard(card.presentOnBoard) {}

Card::Card(const Color& color)
    : color(color), uniqueId(++lastUniqueId) {}

Card::Card(const FrequentColor colorName)
    : color(colorName), uniqueId(++lastUniqueId) {}

bool Card::hasSameColorAs(const Card& card)
{
    return color.isSameColorAs(card.color);
}

bool Card::isSameCard(const Card& card)
{
    return uniqueId == card.uniqueId;
}
