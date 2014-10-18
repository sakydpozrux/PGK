#ifndef CARD_HPP
#define CARD_HPP

#include "color.hpp"

class Card
{
public:
    Card(const Card& card);
    Card(const Color& color);
    Card(const FrequentColor colorName);

    bool hasSameColorAs(const Card& card) const;
    bool isSameCard(const Card& card) const;

    std::string toString() const;

    Color color;
    unsigned int uniqueId;
    bool presentOnBoard = true;

    static unsigned int lastUniqueId;

private:
    static std::string notPresentString();
    std::string presentString() const;
};

#endif // CARD_HPP
