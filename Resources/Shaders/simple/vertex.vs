#version 330

in vec3 in_Position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 ex_Color;

void main(void)
{
    gl_Position = projectionMatrix * viewMatrix * vec4(in_Position, 1.0);
    ex_Color = vec3(1.0, 0.0, 0.0);
}