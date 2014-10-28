#include "board.hpp"
#include <algorithm>
#include <vector>

Board::Board(std::vector<Card> cards, unsigned int horizontalSize, unsigned int verticalSize)
    : horizontalSize(horizontalSize),
      verticalSize(verticalSize),
      cards(cards),
      presentCardsCounter(cards.size())
{
    shuffle();
}

bool Board::enoughCardsForNextRound()
{
    return presentCardsCounter >= 2;
}

void Board::decreaseVisibleCardsCounter()
{
    presentCardsCounter -= 2;
}

void Board::shuffle()
{
    srand(unsigned(time(NULL)));
    std::random_shuffle(cards.begin(), cards.end());
}

std::vector<std::vector<Card> > Board::cardsInRows() const
{
    std::vector<std::vector<Card> > rows;
    std::vector<Card> currentRow;

    unsigned int i = 0;
    for (const Card& card : cards)
        pushCardToRows(card, i, rows, currentRow);

    return rows;
}

void Board::pushCardToRows(const Card& card, unsigned int& i,
                           std::vector<std::vector<Card> >& rows,
                           std::vector<Card>& currentRow) const
{
    currentRow.push_back(card);

    if (++i == horizontalSize)
    {
        i = 0;
        rows.push_back(currentRow);
        currentRow.clear();
    }
}
