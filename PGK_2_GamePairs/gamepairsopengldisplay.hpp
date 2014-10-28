#ifndef GAMEPAIRSOPENGLDISPLAY_HPP
#define GAMEPAIRSOPENGLDISPLAY_HPP

#include "gamepairsdisplay.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef int keyidentifier;
typedef std::pair<GLfloat, GLfloat> point;

enum GameState
{
    STATE_NOT_SPECIFIED,
    STATE_BEGIN,
    STATE_SHOW_BOARD,
    STATE_TAKE_CARD_FIRST,
    STATE_TAKE_CARD_SECOND,
    STATE_TWO_CARDS_CHOSEN,
    STATE_END
};

class GamePairsOpenGLDisplay : public GamePairsDisplay
{
public:
    GamePairsOpenGLDisplay(unsigned int aWidth = 800, unsigned int aHeight = 600);
    virtual ~GamePairsOpenGLDisplay() {}

    void gameBegin();
    void showRound(const unsigned int round);
    void showBoard();
    Card& letUserChooseCard(std::vector<Card>& cards);
    void showCurrentPlayerSuccess();
    void showCurrentPlayerFail();
    void showScore();
    void gameEnd();

    static GamePairsOpenGLDisplay *lastDisplayForCallback;

    void close();

private:
    GameState state = STATE_NOT_SPECIFIED;
    unsigned int failsCounter = 0;

    void initializeGLFW();
    void openWindowAndCreateItsContext();
    void initializeGLEW();

    void initializeBuffers();
    void refreshView();
    void cleanBuffers();

    void setKeyCallback();
    void setBackgroundColor();
    void setProgramIdWithCompilingShaders();

    unsigned int width;
    unsigned int height;

    GLuint programID;
    GLFWwindow *window;

    GLuint *VertexArrayID;
    GLuint *vertexbuffer;
    GLuint *colorbuffer;

    void initialize();
    void cleanupGL();
    bool shouldWindowExit();

    static const std::string simpleVertexShaderCode;
    static const std::string simpleFragmentShaderCode;

    static void keyCallback(GLFWwindow* w, keyidentifier key, int scancode, int action, int mods);
    static bool keyIsOneOfArrowKeys(keyidentifier key);

    std::vector<GLfloat> rectanglesVerticesPositions;
    std::vector<GLfloat> rectanglesVerticesColors;

    void constructRectanglesVectors();
    void constructCards();
    void constructFailBoxes();

    void pushColoredPoint(const point& p,
                          const Color& color);
    bool isCurrentCursorPosition(unsigned int x, unsigned int y);
    void drawCardIfPresent(unsigned int x,
                           unsigned int y,
                           const Card& card);
    void drawCard(unsigned int x,
                  unsigned int y,
                  const Color& color);

    void drawFailBox(unsigned int i);
    float failBoxOriginY(unsigned int i);

    void drawRectangle(const point& origin,
                       const point& size,
                       const Color& color);
    void drawSymbol(const point& origin,
                    const point& size,
                    const Color& color);

    unsigned int cursorX = 0;
    unsigned int cursorY = 0;

    void applyCursorPosition();
    bool justChoseCard = false;
    void updateCursorPosition(keyidentifier key);
};

#endif // GAMEPAIRSOPENGLDISPLAY_HPP
