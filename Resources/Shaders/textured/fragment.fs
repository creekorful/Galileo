#version 330

in  vec2 ex_TextureCoordinate;
out vec4 out_FragColor;

uniform sampler2D textureSampler;

void main(void)
{
    out_FragColor = texture(textureSampler, ex_TextureCoordinate);
}