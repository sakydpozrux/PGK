#ifndef GAMEPAIRSDISPLAY_HPP
#define GAMEPAIRSDISPLAY_HPP

#include "player.hpp"
#include "board.hpp"

class GamePairs;

class GamePairsDisplay
{
public:
    GamePairsDisplay() {}
    virtual ~GamePairsDisplay() {}

    virtual void gameBegin() = 0;
    virtual void showRound(const unsigned int round) = 0;
    virtual void showBoard() = 0;
    virtual Card& letUserChooseCard(std::vector<Card>& cards) = 0;
    virtual void showCurrentPlayerSuccess() = 0;
    virtual void showCurrentPlayerFail() = 0;
    virtual void showScore() = 0;
    virtual void gameEnd() = 0;

    Player *player;
    void setPlayer(Player* aPlayer);

    Board *board;
    void setBoard(Board* aBoard);
};

#endif // GAMEPAIRSDISPLAY_HPP
