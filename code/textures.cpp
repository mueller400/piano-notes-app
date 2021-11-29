/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/textures.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/stb_image.h"

texture_manager::texture_manager()
{
    texture_folder_path_ = "src/pictures";
    missing_texture_ = 0;
}

texture_manager::texture_manager(std::string folder)
{
    texture_folder_path_ = folder;
    missing_texture_ = 0;
}

void texture_manager::load_texture(std::string name, std::string file_name)
{
    // check if texture is not already loaded
    std::map<std::string, unsigned int>::iterator it;
    it = textures.find(name);

    if (it == textures.end())
    {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        int width, height, channels;
        unsigned char *data = stbi_load((texture_folder_path_ + "/" + file_name).c_str(), &width, &height, &channels, 0);

        if (data)
        {
            if (channels == 3) // RGB
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            else if (channels == 4) //RGBA
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            glGenerateMipmap(GL_TEXTURE_2D);
            textures[name] = texture;
        }
        else
        {
            std::cout << "Error: Failed to load texture: " << texture_folder_path_ + "/" + file_name << std::endl;
            textures[name] = missing_texture_;
        }
        stbi_image_free(data);
    }
}

unsigned int texture_manager::get_texture(std::string texture_name)
{
    if (textures.find(texture_name) == textures.end())
    {
        std::cout << "Error: No texture with name >" << texture_name << "< could be found." << std::endl;
        return missing_texture_;
    }
    else
    {
        return textures[texture_name];
    }
}

bool texture_manager::texture_exists(std::string &texture_name)
{
    if (textures.find(texture_name) == textures.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}