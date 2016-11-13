#version 130

uniform sampler2D tex;
uniform float intensity;

in vec2 tex_coord;

out vec4 color;

void main()
{
    color = texture(tex, tex_coord);
    color *= intensity;
}
