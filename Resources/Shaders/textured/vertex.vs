#version 330

in vec3 in_Position;
in vec2 in_TextureCoordinate;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec2 ex_TextureCoordinate;

void main(void)
{
    gl_Position = projectionMatrix * viewMatrix * vec4(in_Position, 1.0);
    ex_TextureCoordinate = in_TextureCoordinate;
}