#include "card.hpp"
#include <sstream>

unsigned int Card::lastUniqueId = 0;

Card::Card(const Card& card)
    : color(card.color.r, card.color.g, card.color.b),
      uniqueId(card.uniqueId),
      colorVisibleOnBoard(card.isVisible()) {}

Card::Card(const Color& color)
    : color(color), uniqueId(++lastUniqueId) {}

Card::Card(const FrequentColor colorName)
    : color(colorName), uniqueId(++lastUniqueId) {}

bool Card::hasSameColorAs(const Card& card) const
{
    return color.isSameColorAs(card.color);
}

bool Card::isSameCard(const Card& card) const
{
    return uniqueId == card.uniqueId;
}

std::string Card::toString() const
{
    return colorVisibleOnBoard ? presentString() : notPresentString();
}

bool Card::isVisible() const
{
    return colorVisibleOnBoard;
}

void Card::setVisible()
{
    colorVisibleOnBoard = false;
}

std::string Card::notPresentString()
{
    return "(NOTHING), ";
}

std::string Card::presentString() const
{
    std::stringstream stream;

    stream << "[" << uniqueId << "]";
    stream << "(" << color.r << "," << color.g << "," << color.b << ")";
    stream << ", ";

    return stream.str();
}
