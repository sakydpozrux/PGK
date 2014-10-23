#include "shaders.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

void Shaders::compileShader(GLuint shaderID, const std::string& sourceCode, GLint* result, int* infoLogLength)
{
    char const * cstringSourceCode = sourceCode.c_str();
    glShaderSource(shaderID, 1, &cstringSourceCode , NULL);
    glCompileShader(shaderID);

    // Check Vertex Shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS,  result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, infoLogLength);
    if (*infoLogLength > 0 ){
        std::vector<char> shaderErrorMessage(*infoLogLength+1);
        glGetShaderInfoLog(shaderID, *infoLogLength, NULL, &shaderErrorMessage[0]);
        printf("%s\n", &shaderErrorMessage[0]);
    }
}

GLuint Shaders::loadShaderFromString(const std::string& vertexSourceCode, const std::string& fragmentSourceCode)
{
    // Create the shaders
    GLuint vertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    GLint result = GL_FALSE;
    int infoLogLength;

    compileShader(vertexShaderID,   vertexSourceCode,   &result,  &infoLogLength);
    compileShader(fragmentShaderID, fragmentSourceCode, &result,  &infoLogLength);

    // Link the program
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if ( infoLogLength > 0 ){
        std::vector<char> programErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
        printf("%s\n", &programErrorMessage[0]);
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}

GLuint Shaders::loadShadersFromFile(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
    try {
        return loadShaderFromString(contentsOfFile(vertexFilePath),
                                    contentsOfFile(fragmentFilePath));
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }

    return 0;
}

GLuint Shaders::loadShadersFromFile(const char *vertexFilePath, const char *fragmentFilePath)
{
    return loadShadersFromFile(std::string(vertexFilePath), std::string(fragmentFilePath));
}

std::string Shaders::contentsOfFile(const std::string& filePath)
{
    std::string fileContents;
    std::ifstream fileStream(filePath, std::ios::in);

    if (fileStream.is_open()) {
        std::string currentLine = "";
        while(getline(fileStream, currentLine))
            fileContents += "\n" + currentLine;
        fileStream.close();
    } else {
        std::stringstream errorStream;
        errorStream << "Impossible to open " << filePath
                  << ". Are you in the right directory ? Don't forget to read the FAQ !"
                  << std::endl;

        throw std::runtime_error(errorStream.str());
    }

    return fileContents;
}

