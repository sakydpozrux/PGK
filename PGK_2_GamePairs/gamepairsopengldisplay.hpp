#ifndef GAMEPAIRSOPENGLDISPLAY_HPP
#define GAMEPAIRSOPENGLDISPLAY_HPP

#include "gamepairsdisplay.hpp"

class GamePairsOpenGLDisplay : public GamePairsDisplay
{
public:
    GamePairsOpenGLDisplay() {}
    virtual ~GamePairsOpenGLDisplay() {}

    void gameBegin();
    void showRound(const unsigned int round,
                   Player *currentPlayer,
                   const Board& board);
    void showBoard(const Board& board);
    Card& letUserChooseCard(std::vector<Card>& cards);
    void showCurrentPlayerSuccess(const Player *currentPlayer);
    void showCurrentPlayerFail(const Player *currentPlayer);
    void showScores(const std::list<Player>& players);
    void gameEnd();

private:
    void initializeGL();
};

#endif // GAMEPAIRSOPENGLDISPLAY_HPP
