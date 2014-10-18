#include "board.hpp"
#include <algorithm>
#include <vector>

Board::Board(std::vector<Card> cards, unsigned int horizontalSize, unsigned int verticalSize)
    : horizontalSize(horizontalSize),
      verticalSize(verticalSize),
      cards(cards),
      presentCardsCounter(cards.size())
{
    // TODO: uncomment board shuffling if visual card choosing is implemented
    shuffle();
}

bool Board::enoughCardsForNextRound()
{
    return presentCardsCounter >= 2;
}

void Board::decrementPresentCardsCounter()
{
    --presentCardsCounter;
}

void Board::shuffle()
{
    std::random_shuffle(cards.begin(), cards.end());
}

std::vector<std::vector<Card> > Board::cardsInRows()
{
    std::vector<std::vector<Card> > rows;
    std::vector<Card> currentRow;

    unsigned int i = 1;
    for (const Card& card : cards)
    {
        currentRow.push_back(card);

        if (i % horizontalSize == 0)
        {
            rows.push_back(currentRow);
            currentRow.clear();
            if (rows.size() >= verticalSize) return rows;
        }
        ++i;
    }

    return rows;
}
