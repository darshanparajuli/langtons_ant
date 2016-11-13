#version 130

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

in vec3 pos;
in vec2 tex_coord_in;

out vec2 tex_coord;

void main()
{
    gl_Position = projection * view * transform * vec4(pos, 1.0f);
    tex_coord = tex_coord_in;
}
