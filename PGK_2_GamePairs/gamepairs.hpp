#ifndef GAMEPAIRS_HPP
#define GAMEPAIRS_HPP

#include "player.hpp"
#include "board.hpp"
#include <list>


class GamePairs
{
public:
  // I assume that there is at least one player.
  GamePairs(std::list<Player> players, std::list<Card> cards = frequentCards());

  void play();

  std::list<Player> players;
  Board board;

  unsigned int round = 0;

  Player *currentPlayer;
  void nextPlayer();

  std::list<Card>& cards();
  static std::list<Card> frequentCards();

protected:
  virtual void gameBegin();
  bool enoughCardsForNextRound();
  void nextRound();
  virtual void showRound();
  void tryTakeCards(Card& card1, Card& card2);
  virtual void showScores();
  virtual void gameEnd();
};

#endif // GAMEPAIRS_HPP
