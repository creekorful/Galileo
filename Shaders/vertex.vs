#version 330

in vec3 in_Position;

out vec3 ex_Color;

void main(void)
{
    gl_Position = vec4(in_Position, 1.0);
    ex_Color = vec3(in_Position.x, 0, in_Position.y);
}