#include "board.hpp"
#include <algorithm>
#include <vector>

Board::Board(std::list<Card> cards, unsigned int horizontalSize, unsigned int verticalSize)
    : horizontalSize(horizontalSize), verticalSize(verticalSize), cards(cards)
{
    shuffle();
}

void Board::shuffle()
{
    std::vector<Card> vectorCards(std::make_move_iterator(std::begin(cards)),
                                  std::make_move_iterator(std::end(cards)));

    std::random_shuffle(vectorCards.begin(), vectorCards.end());

    cards = std::list<Card>(vectorCards.begin(), vectorCards.end());
}

std::list<std::list<Card> > Board::cardsInRows()
{
    std::list<std::list<Card> > rows;
    std::list<Card> currentRow;

    unsigned int i = 1;
    for (const Card& card : cards)
    {
        currentRow.push_back(card);

        if (i % horizontalSize == 0 && i == cards.size())
        {
            rows.push_back(currentRow);
            currentRow.clear();
            if (rows.size() >= verticalSize) return rows;
        }
        ++i;
    }

    return rows;
}
