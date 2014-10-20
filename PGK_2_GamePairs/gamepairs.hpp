#ifndef GAMEPAIRS_HPP
#define GAMEPAIRS_HPP

#include "player.hpp"
#include "board.hpp"
#include "gamepairsdisplay.hpp"
#include "gamepairsopengldisplay.hpp"
#include "gamepairstextdisplay.hpp"
#include <vector>


class GamePairs
{
public:
  // I assume that there is at least one player.
  GamePairs(std::list<Player> players,
            GamePairsDisplay *aDisplayDelegate = new GamePairsTextDisplay(),
            std::vector<Card> cards = frequentCards());

  ~GamePairs();

  void play();

  std::list<Player> players;
  Board board;

  unsigned int round = 0;

  Player *currentPlayer;
  void nextPlayer();

  std::vector<Card>& cards();
  static std::vector<Card> frequentCards();

  GamePairsDisplay *displayDelegate;

protected:
  void nextRound();
  bool tryTakeCards(Card& card1, Card& card2);

  bool cardsArePresent(const Card& card1, const Card& card2) const;
  bool validChoice(const Card& card1, const Card& card2) const;

private:
  GamePairs(const GamePairs& gamePairs) = delete;
  const GamePairs& operator=(const GamePairs& gamePairs) = delete;
};

#endif // GAMEPAIRS_HPP
