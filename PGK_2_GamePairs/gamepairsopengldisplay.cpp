#include "gamepairsopengldisplay.hpp"
#include "shaders.hpp"
#include "exception"

#include <GL/glew.h>

#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
using namespace glm;

// REFACTOR: Do something with these ugly const strings. Even QtCreator doesn't correctly parse it. :D
const std::string GamePairsOpenGLDisplay::simpleVertexShaderCode =
R"sourceCode(
#version 330 core

// Input vertex data, different for all executions of this shader.
in vec2 position;
in vec3 color;

out vec3 Color;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    Color = color;
}

)sourceCode";


// REFACTOR: Same here.
const std::string GamePairsOpenGLDisplay::simpleFragmentShaderCode =
R"sourceCode(
#version 330 core

in vec3 Color;
out vec4 color;

void main()
{
        // Output color = red
        color = vec4(Color, 1.0);
}

)sourceCode";

GamePairsOpenGLDisplay::GamePairsOpenGLDisplay(unsigned int aWidth, unsigned int aHeight)
    : GamePairsDisplay(), width(aWidth), height(aHeight) {}

void GamePairsOpenGLDisplay::gameBegin()
{
    initializeGL();
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


// TODO: Refactor method below. Extract it to smaller functions.
void GamePairsOpenGLDisplay::initializeGL()
{
    // Initialise GLFW
    if(!glfwInit()) {
        throw std::runtime_error(std::string("Failed to initialize GLFW\n"));
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "Game Pairs", NULL, NULL);
    if(!window) {
        glfwTerminate();
        throw std::runtime_error(std::string("Failed to open GLFW window.\n"));
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        //return -1; TODO: raise exception
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.1f, 0.1f, 0.2f, 0.0f);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = Shaders::loadShaderFromString(simpleVertexShaderCode, simpleFragmentShaderCode);


    static const GLfloat g_vertex_buffer_data[] = {
        0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    do{

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        // 1rst attribute buffer : vertices
        GLint posAttrib = glGetAttribLocation(programID, "position");
        glEnableVertexAttribArray(posAttrib);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            posAttrib,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            5*sizeof(float),                  // stride
            (void*)0            // array buffer offset
        );


        GLint colAttrib = glGetAttribLocation(programID, "color");
        glEnableVertexAttribArray(colAttrib);
        glVertexAttribPointer(
            colAttrib, // position of color attribute
            3, // rgb)
            GL_FLOAT,
            GL_FALSE, //normalized?
            5*sizeof(float),
            (void*)(2 * sizeof(float)) // offset
       );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(programID);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}
