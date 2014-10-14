#ifndef GAMEPAIRS_HPP
#define GAMEPAIRS_HPP

#include "player.hpp"
#include "board.hpp"
#include <list>

class GamePairs
{
public:
  GamePairs(std::list<Player> players, std::list<Card> cards);

  void play();

  std::list<Player> players;
  Board board;

  void addPlayer(Player player);
  const unsigned int numberOfPlayers;

  unsigned int round = 1;

  Player *nextPlayer();

  std::list<Card>& cards();
};

#endif // GAMEPAIRS_HPP
