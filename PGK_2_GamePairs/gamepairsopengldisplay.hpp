#ifndef GAMEPAIRSOPENGLDISPLAY_HPP
#define GAMEPAIRSOPENGLDISPLAY_HPP

#include "gamepairsdisplay.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef int keyidentifier;
typedef std::pair<GLfloat, GLfloat> point;

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

private:
    void refreshView();

    void initializeGLFW();
    void openWindowAndCreateItsContext();
    void initializeGLEW();
    void initializeBuffers();
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

    static const std::string konVertexShaderCode;
    static const std::string konFragmentShaderCode;
    static const std::string simpleVertexShaderCode;
    static const std::string simpleFragmentShaderCode;

    static void keyCallback(GLFWwindow* w, keyidentifier key, int scancode, int action, int mods);
    static bool keyIsOneOfArrowKeys(keyidentifier key);

    unsigned int rectanglesToDraw = 0;

    std::vector<GLfloat> rectanglesVerticesPositions;
    std::vector<GLfloat> rectanglesVerticesColors;

    void constructRectanglesVectors();
    void pushColoredPoint(const point& p,
                          const Color& color);
    void drawCardIfPresent(int x, int y, const Card& card);
    void drawCard(int x, int y, const Color& color);

    void drawRectangle(const point& origin,
                       const point& size,
                       const Color& color);
    void drawSymbol(const point& origin,
                    const point& size,
                    const Color& color);

    unsigned int cursorX = 0;
    unsigned int cursorY = 0;

    void applyCursorPosition();
    void updateCursorPosition(keyidentifier key);
};

#endif // GAMEPAIRSOPENGLDISPLAY_HPP
