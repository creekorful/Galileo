#version 330

in  vec3 ex_Color;
out vec4 out_FragColor;

void main(void)
{
    out_FragColor = vec4(ex_Color, 1.0);
}