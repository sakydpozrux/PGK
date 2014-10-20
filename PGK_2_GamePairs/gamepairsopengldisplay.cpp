#include "gamepairsopengldisplay.hpp"

void GamePairsOpenGLDisplay::gameBegin()
{
}

void GamePairsOpenGLDisplay::showRound(const unsigned int round,
                                       Player *currentPlayer,
                                       const Board& board)
{
}

void GamePairsOpenGLDisplay::showBoard(const Board& board)
{
}

Card& GamePairsOpenGLDisplay::letUserChooseCard(std::vector<Card>& cards)
{
    //return &(new Card(RED));
}

void GamePairsOpenGLDisplay::showCurrentPlayerSuccess(const Player *currentPlayer)
{
}

void GamePairsOpenGLDisplay::showCurrentPlayerFail(const Player *currentPlayer)
{
}

void GamePairsOpenGLDisplay::showScores(const std::list<Player>& players)
{
}

void GamePairsOpenGLDisplay::gameEnd()
{
}
