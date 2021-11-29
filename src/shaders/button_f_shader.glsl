#version 330 core

in float vertex_shade;
uniform vec4 color;

out vec4 fragment_color;

void main()
{
    fragment_color = vec4(vertex_shade * color.x, vertex_shade * color.y, vertex_shade * color.z, color.w);
}