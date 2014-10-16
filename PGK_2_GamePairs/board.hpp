#ifndef BOARD_HPP
#define BOARD_HPP

#include "card.hpp"
#include <list>

class Board
{
public:
  // Currently I assume that at the beginning of game cards size equals to 16
  // and each color occurs exactly two times (or not at all).
  Board(std::list<Card> cards, unsigned int horizontalSize = 4, unsigned int verticalSize = 4);

  const unsigned int horizontalSize;
  const unsigned int verticalSize;

  std::list<Card> cards;

  void shuffle();
  std::list<std::list<Card> > cardsInRows();
};

#endif // BOARD_HPP
