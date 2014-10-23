#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <string>
#include <GL/glew.h>

class Shaders
{
public:
    static GLuint loadShaderFromString(const std::string& vertexSourceCode, const std::string& fragmentSourceCode);

    static GLuint loadShadersFromFile(const std::string& vertex_file_path, const std::string& fragment_file_path);
    static GLuint loadShadersFromFile(const char * vertex_file_path,const char * fragment_file_path);

    // helpers
    void throwRuntimeError(const std::string& filePath);
    void f(GLuint VertexShaderID, GLint Result, const std::string& vertexSourceCode, int InfoLogLength);
    void g(GLuint FragmentShaderID, const std::string& fragmentSourceCode, GLint Result, int InfoLogLength);

private:
    static std::string contentsOfFile(const std::string& filePath);
    static void compileShader(GLuint shaderID, const std::string& sourceCode, GLint* result, int* infoLogLength);
};

#endif // SHADERS_HPP
