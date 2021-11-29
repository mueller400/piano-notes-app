#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in float shade;

uniform vec2 offset = vec2(0.0f, 0.0f);
uniform vec2 scale = vec2(1.0f, 1.0f);

out float vertex_shade;

void main()
{
    gl_Position = vec4((pos.x * scale.x) + offset.x, (pos.y * scale.y) + offset.y, 0.0f, 1.0f);
    vertex_shade = shade;
}
