#ifndef GAMEPAIRSDISPLAY_HPP
#define GAMEPAIRSDISPLAY_HPP

#include "player.hpp"
#include "board.hpp"

class GamePairs;
class Card;

class GamePairsDisplay
{
public:
    GamePairsDisplay() {};
    virtual ~GamePairsDisplay() {};

    virtual void gameBegin() = 0;
    virtual void showRound(const unsigned int round,
                           Player *currentPlayer,
                           const Board& board) = 0;
    virtual void showBoard(const Board& board) = 0;
    virtual Card& letUserChooseCard(std::vector<Card>& cards) = 0;
    virtual void showCurrentPlayerSuccess(const Player *currentPlayer) = 0;
    virtual void showCurrentPlayerFail(const Player *currentPlayer) = 0;
    virtual void showScores(const std::list<Player>& players) = 0;
    virtual void gameEnd() = 0;
};

#endif // GAMEPAIRSDISPLAY_HPP
