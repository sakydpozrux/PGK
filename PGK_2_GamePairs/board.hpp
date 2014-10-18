#ifndef BOARD_HPP
#define BOARD_HPP

#include "card.hpp"
#include <vector>

class Board
{
public:
  // Currently I assume that at the beginning of game cards size equals to 16
  // and each color occurs exactly two times (or not at all).
  Board(std::vector<Card> cards, unsigned int horizontalSize = 4, unsigned int verticalSize = 4);

  const unsigned int horizontalSize;
  const unsigned int verticalSize;

  std::vector<Card> cards;
  unsigned int presentCardsCounter;

  bool enoughCardsForNextRound();
  void decrementPresentCardsCounter();

  void shuffle();
  std::vector<std::vector<Card> > cardsInRows();
};

#endif // BOARD_HPP
