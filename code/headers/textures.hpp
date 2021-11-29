/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include "../../dependencies/glad/glad.h"
#include <map>
#include <string>
#include <iostream>

class texture_manager
{
public:
    std::map<std::string, unsigned int> textures;
    unsigned int operator[](std::string &texture_name) {
        return textures[texture_name];
    }
    texture_manager();
    texture_manager(std::string texture_folder);
    void load_texture(std::string name, std::string file_name);
    unsigned int get_texture(std::string texture_name);
    bool texture_exists(std::string &texture_name);

private:
    std::string texture_folder_path_;
    unsigned int missing_texture_;
    void create_missing_texture();

};

#endif