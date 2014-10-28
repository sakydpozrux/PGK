#ifndef SHADERSSOURCECODES_HPP
#define SHADERSSOURCECODES_HPP

const std::string GamePairsOpenGLDisplay::simpleVertexShaderCode =
R"C0DE(
#version 330 core

in vec2 position;
in vec3 color;

out vec3 Color;
void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    Color = color;
}
)C0DE";


const std::string GamePairsOpenGLDisplay::simpleFragmentShaderCode =
R"C0DE(
#version 330 core

in vec3 Color;
out vec4 color;
void main()
{
    color = vec4(Color, 1.0);
}
)C0DE";


#endif // SHADERSSOURCECODES_HPP
