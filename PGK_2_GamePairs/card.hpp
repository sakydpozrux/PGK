#ifndef CARD_HPP
#define CARD_HPP

#include "color.hpp"

enum CardVisibility
{
    CARD_VISIBLE,
    CARD_HIDDEN,
    CARD_NOT_PRESENT
};

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

    CardVisibility visibility = CARD_HIDDEN;
    bool isVisible() const;
    bool isPresent() const;
    void setVisible(bool shouldBeVisible);
    void removeFromBoard();

    static unsigned int lastUniqueId;

private:
    static std::string notPresentString();
    std::string presentString() const;
};

#endif // CARD_HPP
