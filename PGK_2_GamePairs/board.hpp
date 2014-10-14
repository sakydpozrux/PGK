#ifndef BOARD_HPP
#define BOARD_HPP

#include "card.hpp"
#include <list>

class Board
{
public:
  Board(std::list<Card> cards, unsigned int horizontalSize = 4, unsigned int verticalSize = 4);

  const unsigned int horizontalSize;
  const unsigned int verticalSize;

  std::list<Card> cards;

  void shuffle();
  std::list<std::list<Card> > cardsInRows();
};

#endif // BOARD_HPP
