#ifndef GAMEPAIRS_HPP
#define GAMEPAIRS_HPP

#include "player.hpp"
#include "board.hpp"
#include <vector>


class GamePairs
{
public:
  // I assume that there is at least one player.
  GamePairs(std::list<Player> players, std::vector<Card> cards = frequentCards());

  void play();

  std::list<Player> players;
  Board board;

  unsigned int round = 0;

  Player *currentPlayer;
  void nextPlayer();

  std::vector<Card>& cards();
  static std::vector<Card> frequentCards();

protected:
  virtual void gameBegin();
  void nextRound();
  virtual void showRound();
  virtual void showBoard();
  bool tryTakeCards(Card& card1, Card& card2);
  virtual Card& letUserChooseCard();
  virtual void showCurrentPlayerSuccess();
  virtual void showCurrentPlayerFail();
  virtual void showScores();
  virtual void gameEnd();

  void printableRowToStream(const std::vector<Card>& horizontalRow, std::stringstream& stream) const;
  bool cardsArePresent(const Card& card1, const Card& card2) const;
  bool validChoice(const Card& card1, const Card& card2) const;
};

#endif // GAMEPAIRS_HPP
