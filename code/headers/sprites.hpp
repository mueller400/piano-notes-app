/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef SPRITES_HPP
#define SPRITES_HPP

#include "../../dependencies/glad/glad.h"
#include "textures.hpp"
#include "shaders.hpp"
#include "units.hpp"
#include <string>
#include <map>
#include "math.h"

struct sprite
{
    vec2<float> pos;
    vec2<float> size;
    float rotation;     // rotation in degree [0.0 - 360.0]
    color<float> col;
    unsigned int texture;
    unsigned int shader;

    void rotate (float rot) {
        rotation = rot * (3.14159265359 / 180.0);
    }
};

class sprite_manager
{
    private:
        texture_manager textures_;
        shader_manager shaders_;

        std::map<std::string, sprite> sprite_list_;
        unsigned int rectangle_;
        unsigned int vbo_;
        unsigned int ebo_;
        unsigned int default_shader_;
        unsigned int offset_x_location_;
        unsigned int offset_y_location_;
        vec2<unsigned int> screen_resolution_;
        
        void create_rectangle();

    public:
        sprite_manager();
        sprite_manager(vec2<unsigned int> screen, std::string texture_folder_path);
        void init(vec2<unsigned int> screen, std::string texture_folder_path);
        
        texture_manager* get_texture_manager() {
            texture_manager* ptr = &textures_;
            return ptr;
        };

        sprite create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                             color<float> col, unsigned int texture, unsigned int shader);
        sprite create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                             unsigned int texture, unsigned int shader);
        sprite create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                             color<float> col, unsigned int texture);
        sprite create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                             unsigned int texture);
        sprite create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                             color<float> col, std::string texture_name);
        sprite create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                             std::string texture_name);
        sprite create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                             color<float> col, std::string texture_name, unsigned int shader);
        sprite create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                             std::string texture_name, unsigned int shader);

        void set_shader(sprite &spr, std::string shader_name);
        unsigned int get_rectangle();
        void draw(sprite &spr);
};

#endif