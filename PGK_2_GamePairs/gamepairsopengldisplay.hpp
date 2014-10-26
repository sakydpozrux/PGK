#ifndef GAMEPAIRSOPENGLDISPLAY_HPP
#define GAMEPAIRSOPENGLDISPLAY_HPP

#include "gamepairsdisplay.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef int keyidentifier;

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

    void initializeGLFW();
    void openWindowAndCreateItsContext();
    void initializeGLEW();
    void doSomethingFunny();
    void setKeyCallback();
    void setBackgroundColor();
    void setProgramIdWithCompilingShaders();

private:
    unsigned int width;
    unsigned int height;

    GLuint programID;
    GLFWwindow *window;

    GLuint *VertexArrayID;
    GLuint *vertexbuffer;

    void initialize();
    void cleanupGL();

    static const std::string konVertexShaderCode;
    static const std::string konFragmentShaderCode;
    static const std::string simpleVertexShaderCode;
    static const std::string simpleFragmentShaderCode;

    static void keyCallback(GLFWwindow* w, keyidentifier key, int scancode, int action, int mods);
    static bool keyIsOneOfArrowKeys(keyidentifier key);
};

#endif // GAMEPAIRSOPENGLDISPLAY_HPP
