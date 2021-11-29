#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 tex;

uniform vec2 offset = vec2(0.0f, 0.0f);
uniform vec2 scale = vec2(1.0f, 1.0f);

out vec2 tex_coords;

void main()
{
    gl_Position = vec4((pos.x * scale.x) + offset.x, (pos.y * scale.y) + offset.y, 0.0f, 1.0f);
    tex_coords = tex;
}