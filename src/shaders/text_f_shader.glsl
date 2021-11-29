#version 330 core

in vec2 tex_coords;

uniform sampler2D tex;
uniform vec4 color;

out vec4 fragment_color;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, tex_coords).r);
    fragment_color = vec4(color) * sampled;
}