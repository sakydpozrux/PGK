#ifndef GAMEPAIRSOPENGLDISPLAY_HPP
#define GAMEPAIRSOPENGLDISPLAY_HPP

#include "gamepairsdisplay.hpp"
#include <GL/glew.h>

class GamePairsOpenGLDisplay : public GamePairsDisplay
{
public:
    GamePairsOpenGLDisplay(unsigned int aWidth = 800, unsigned int aHeight = 600);
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
    unsigned int width;
    unsigned int height;

    GLuint programID = 0;

    void initializeGL();

    static const std::string simpleVertexShaderCode;
    static const std::string simpleFragmentShaderCode;
};

#endif // GAMEPAIRSOPENGLDISPLAY_HPP
