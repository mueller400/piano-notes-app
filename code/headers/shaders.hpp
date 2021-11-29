/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#define default_vertex_shader_code "#version 330 core\nlayout (location = 0) in vec2 pos; layout (location = 1) in vec2 tex; uniform vec2 offset = vec2(0.0f, 0.0f); uniform vec2 scale = vec2(1.0f, 1.0f); out vec2 tex_coords; void main() {gl_Position = vec4((pos.x * scale.x) + offset.x, (pos.y * scale.y) + offset.y, 0.0f, 1.0f);tex_coords = tex;}"
#define default_fragment_shader_code "#version 330 core\nin vec2 tex_coords;uniform sampler2D tex;uniform vec4 color;out vec4 fragment_color;void main(){fragment_color = vec4(color) * texture(tex, tex_coords);}"
#ifndef SHADERS_HPP
#define SHADERS_HPP

#include "../../dependencies/glad/glad.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>

class shader_manager
{
public:
    shader_manager(std::string shader_folder);
    shader_manager();
    unsigned int operator[](std::string &shader_name)
    {
        return shaders_[shader_name];
    }
    unsigned int operator[](std::string &&shader_name)
    {
        return shaders_[shader_name];
    }
    void create_default_shader();
    unsigned int get_default_shader();
    void create_shader_from_file(std::string name, std::string vertex_shader_source_file,
                       std::string fragment_shader_source_file);
    void create_shader_from_code(std::string name, const char *vertex_shader_code, 
                                const char *fragment_shader_code);

private:
    std::string shader_folder_;
    std::map<std::string, unsigned int> shaders_;

    unsigned int compile_shader(std::string shader_name, const char *vertex_shader_code,
                                const char *fragment_shader_code);
    bool check_compile_errors(std::string shader_name, unsigned int shader);
    std::string get_shader_code_from_file(std::string shader_source_file);
};

#endif