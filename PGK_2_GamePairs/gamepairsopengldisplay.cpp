#include "gamepairsopengldisplay.hpp"
#include "shaders.hpp"
#include "exception"
#include <iostream> //TODO: Remove this include when possible

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

const float DISTANCE_BETWEEN_CARDS = 0.04f;
const float CARD_WIDTH  = 0.350f;
const float CARD_HEIGHT = 0.450f;

GamePairsOpenGLDisplay *GamePairsOpenGLDisplay::lastDisplayForCallback = nullptr;

// REFACTOR: Do something with these ugly const strings. Even QtCreator doesn't correctly parse it. :D
// BEGIN
const std::string GamePairsOpenGLDisplay::simpleVertexShaderCode =
R"sourceCode(
#version 330 core

in vec2 position;
in vec3 color;

out vec3 Color;
void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    Color = color;
}
)sourceCode";
// END


// REFACTOR: Same here.
// BEGIN
const std::string GamePairsOpenGLDisplay::simpleFragmentShaderCode =
R"sourceCode(
#version 330 core

in vec3 Color;
out vec4 color;
void main()
{
    color = vec4(Color, 1.0);
}
)sourceCode";
// END

GamePairsOpenGLDisplay::GamePairsOpenGLDisplay(unsigned int aWidth, unsigned int aHeight)
    : GamePairsDisplay(), width(aWidth), height(aHeight) {}

void GamePairsOpenGLDisplay::gameBegin()
{
    initialize();
    state = STATE_BEGIN;

    refreshView();
}

void GamePairsOpenGLDisplay::setKeyCallback()
{
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void GamePairsOpenGLDisplay::setBackgroundColor()
{
    glClearColor(0.1f, 0.1f, 0.2f, 0.0f);
}

void GamePairsOpenGLDisplay::setProgramIdWithCompilingShaders()
{
    programID = Shaders::loadShaderFromString(simpleVertexShaderCode, simpleFragmentShaderCode);
}

void GamePairsOpenGLDisplay::initialize()
{
    initializeGLFW();
    openWindowAndCreateItsContext();
    initializeGLEW();

    setKeyCallback();
    setBackgroundColor();

    constructRectanglesVectors();

    setProgramIdWithCompilingShaders();
    initializeBuffers();
}

void GamePairsOpenGLDisplay::showRound(const unsigned int round)
{
    state = STATE_SHOW_BOARD;
    std::cout << "ROUND: " << round << std::endl;
}

void GamePairsOpenGLDisplay::showBoard()
{
    constructRectanglesVectors();
    refreshView();
}

Card& GamePairsOpenGLDisplay::letUserChooseCard(std::vector<Card>& cards)
{
    state = (state == STATE_TAKE_CARD_FIRST) ? STATE_TAKE_CARD_SECOND
                                             : STATE_TAKE_CARD_FIRST;

    if (state == STATE_TAKE_CARD_SECOND)
    {
        Card& selectedCard = cards[cursorY * board->horizontalSize + cursorX];
        selectedCard.setVisible(true);
    }

    do {
        constructRectanglesVectors();
        refreshView();
        glfwPollEvents();
    } while (!justChoseCard && !shouldWindowExit());

    justChoseCard = false;

    if (state == STATE_TAKE_CARD_SECOND)
        state = STATE_TWO_CARDS_CHOSEN;

    Card& selectedCard = cards[cursorY * board->horizontalSize + cursorX];

    return selectedCard;
}

void GamePairsOpenGLDisplay::showCurrentPlayerSuccess()
{
    std::cout << "SUCCESS" << std::endl;
}

void GamePairsOpenGLDisplay::showCurrentPlayerFail()
{
    std::cout << "FAIL" << std::endl;
}

void GamePairsOpenGLDisplay::showScore()
{
    std::cout << "SCORE: " << player->score << std::endl;
}

void GamePairsOpenGLDisplay::gameEnd()
{
    constructRectanglesVectors();
    do {
        refreshView();
        glfwPollEvents();
    } while(!shouldWindowExit());

    cleanupGL();
}

void GamePairsOpenGLDisplay::initializeGLFW()
{
    if(!glfwInit())
        throw std::runtime_error(std::string("Failed to initialize GLFW\n"));

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GamePairsOpenGLDisplay::openWindowAndCreateItsContext()
{
    window = glfwCreateWindow(width, height, "Game Pairs", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        throw std::runtime_error(std::string("Failed to open GLFW window.\n"));
    }
    glfwMakeContextCurrent(window);
}

void GamePairsOpenGLDisplay::initializeGLEW()
{
    glewExperimental = true;

    if (glewInit() != GLEW_OK)
        throw std::runtime_error(std::string("Failed to initialize GLEW\n"));
}

void GamePairsOpenGLDisplay::initializeBuffers()
{
    VertexArrayID = new GLuint();
    glGenVertexArrays(1, VertexArrayID);
    glBindVertexArray(*VertexArrayID);

    vertexbuffer = new GLuint();
    glGenBuffers(1, vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 rectanglesVerticesPositions.size() * sizeof(GLfloat),
                 rectanglesVerticesPositions.data(),
                 GL_STATIC_DRAW);

    colorbuffer = new GLuint();
    glGenBuffers(1, colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, *colorbuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 rectanglesVerticesColors.size() * sizeof(GLfloat),
                 rectanglesVerticesColors.data(),
                 GL_STATIC_DRAW);
}

void GamePairsOpenGLDisplay::refreshView()
{
    initializeBuffers();
    lastDisplayForCallback = this;

    glUseProgram(programID);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
    glVertexAttribPointer(
                0,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void*)0
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, *colorbuffer);
    glVertexAttribPointer(
                1,
                3,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void*)0
   );

    glDrawArrays(GL_TRIANGLES,
                 0,
                 rectanglesVerticesPositions.size() * sizeof(GLfloat));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glfwSwapBuffers(window);
}

void GamePairsOpenGLDisplay::cleanupGL()
{
    glDeleteBuffers(1, vertexbuffer);
    glDeleteVertexArrays(1, VertexArrayID);
    glDeleteProgram(programID);

    delete VertexArrayID;
    delete vertexbuffer;
    delete colorbuffer;

    glfwTerminate();
}

void GamePairsOpenGLDisplay::keyCallback(GLFWwindow*, keyidentifier key, int, int action, int)
{
    if (action == GLFW_RELEASE)
        return;

    if (key == GLFW_KEY_ESCAPE)
        lastDisplayForCallback->close();

    if (key == GLFW_KEY_SPACE)
        lastDisplayForCallback->applyCursorPosition();

    if (keyIsOneOfArrowKeys(key))
        lastDisplayForCallback->updateCursorPosition(key);

    lastDisplayForCallback->refreshView();
}

void GamePairsOpenGLDisplay::applyCursorPosition()
{
    Card& card = (board->cards)[cursorY * board->horizontalSize + cursorX];
    if (card.isPresent())
        justChoseCard = true;
}

void GamePairsOpenGLDisplay::updateCursorPosition(keyidentifier key)
{
    const unsigned int horizontalSize = board->horizontalSize;
    const unsigned int verticalSize   = board->verticalSize;

    switch (key) {
    case GLFW_KEY_UP:
        cursorY = (cursorY - 1) % verticalSize;
        break;
    case GLFW_KEY_DOWN:
        cursorY = (cursorY + 1) % verticalSize;
        break;
    case GLFW_KEY_LEFT:
        cursorX = (cursorX - 1) % horizontalSize;
        break;
    default: // GLFW_KEY_RIGHT
        cursorX = (cursorX + 1) % horizontalSize;
        break;
    }

    std::cout << "Cursor position: (" << cursorX << ", " << cursorY << ")" << std::endl;
}

bool GamePairsOpenGLDisplay::keyIsOneOfArrowKeys(keyidentifier key)
{
    return key == GLFW_KEY_UP
        || key == GLFW_KEY_DOWN
        || key == GLFW_KEY_LEFT
        || key == GLFW_KEY_RIGHT;
}

void GamePairsOpenGLDisplay::constructRectanglesVectors()
{
    rectanglesVerticesPositions.clear();
    rectanglesVerticesColors.clear();

    const std::vector<std::vector<Card> >& cards = board->cardsInRows();

    for (unsigned int y = 0; y < board->verticalSize; ++y)
        for (unsigned int x = 0; x < board->horizontalSize; ++x)
            drawCardIfPresent(x, y, cards[y][x]);
}

void GamePairsOpenGLDisplay::drawCardIfPresent(int x, int y, const Card& card)
{
    if (!card.isPresent())
        return;

    Color color = card.isVisible() ? card.color : Color::gray();

    if (x == cursorX && y == cursorY)
        color = Color(color, 0.3f);

    drawCard(x, y, color);
}

void GamePairsOpenGLDisplay::drawCard(int x, int y, const Color& color)
{
    point origin(-1.0f + (x+1) * DISTANCE_BETWEEN_CARDS + x * CARD_WIDTH,
                  1.0f - (y+1) * DISTANCE_BETWEEN_CARDS - y * CARD_HEIGHT);
    point size(CARD_WIDTH, CARD_HEIGHT);

    drawRectangle(origin, size, color);
    drawSymbol(origin, size, color);
}

void GamePairsOpenGLDisplay::pushColoredPoint(const point& p,
                                              const Color& color)
{
    rectanglesVerticesPositions.push_back(p.first);
    rectanglesVerticesPositions.push_back(p.second);

    rectanglesVerticesColors.push_back(static_cast<GLfloat>(color.r));
    rectanglesVerticesColors.push_back(static_cast<GLfloat>(color.g));
    rectanglesVerticesColors.push_back(static_cast<GLfloat>(color.b));
}

void GamePairsOpenGLDisplay::drawRectangle(const point& origin, const point& size, const Color& color)
{
    point upLeft = origin;
    point downLeft(origin.first, origin.second - size.second);
    point downRight(origin.first + size.first, downLeft.second);
    point upRight(downRight.first, origin.second);

    pushColoredPoint(upLeft,    color);
    pushColoredPoint(downLeft,  Color(color, -0.1f));
    pushColoredPoint(downRight, Color(color,  0.05f));
    pushColoredPoint(downRight, Color(color,  0.15f));
    pushColoredPoint(upRight,   Color(color,  0.3f));
    pushColoredPoint(upLeft,    color);
}

void GamePairsOpenGLDisplay::drawSymbol(const point& origin, const point& size, const Color& color)
{
    // TODO
}

bool GamePairsOpenGLDisplay::shouldWindowExit()
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
            || glfwWindowShouldClose(window) != 0;
}

void GamePairsOpenGLDisplay::close()
{
    exit(0);
}
