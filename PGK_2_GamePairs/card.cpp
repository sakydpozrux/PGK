#include "card.hpp"
#include <sstream>

unsigned int Card::lastUniqueId = 0;

Card::Card(const Card& card)
    : color(card.color.r, card.color.g, card.color.b),
      uniqueId(card.uniqueId),
      visibility(card.visibility) {}

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
    return isPresent() ? presentString() : notPresentString();
}

bool Card::isVisible() const
{
    return visibility == CARD_VISIBLE;
}

bool Card::isPresent() const
{
    return visibility != CARD_NOT_PRESENT;
}

void Card::setVisible(bool shouldBeVisible)
{
    if (visibility != CARD_NOT_PRESENT)
        visibility = shouldBeVisible ? CARD_VISIBLE : CARD_HIDDEN;
}

void Card::removeFromBoard()
{
    visibility = CARD_NOT_PRESENT;
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
