/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef GUI_BUTTON_HPP
#define GUI_BUTTON_HPP

#include "gui_element.hpp"
#include "gui_label.hpp"
#include "../../headers/sprites.hpp"

class gui_button : public gui_element
{
private:
    vec2<float> border_size_gl;
    vec2<float> border_size_px;
    unsigned int shader_;
    
    

public:
    gui_label button_label;
    bool show_label = true;

    gui_button(vec2<unsigned int> screen,
               unsigned int shader,
               text_renderer* text_renderer,
               std::string button_text,
               color<float> button_text_color,
               vec2<int> position_px, 
               vec2<int> size_px,
               vec2<int> padding_px,
               color<float> button_color,
               vec2<int> border_width_px = vec2<int>{6, 6});
    void draw();
    shape_data get_shape_data();
};

class texture_button : public gui_element
{
private:
    sprite_manager* sprite_manager_;
    sprite sprite_;
    unsigned int vao_;
    unsigned int shader_;

public:
    texture_button(vec2<unsigned int> screen, sprite_manager* sprite_manager, vec2<int> position_px,
                   vec2<int> size_pixel, std::string texture_name);
    void draw();
};

class check_box : public gui_element
{
private:
    sprite_manager* sprite_manager_;
    sprite sprite_;
    unsigned int overlay_texture_;
    unsigned int vao_;
    unsigned int shader_;

public:
    bool is_checked = false;
    bool switch_textures = false;
    color<float> overlay_normal_color = {0.9f, 0.9f, 0.9f, 1.0f};
    color<float> overlay_hover_color = {1.0f, 1.0f, 1.0f, 1.0f};

    check_box(vec2<unsigned int> screen, sprite_manager* sprite_manager, vec2<int> position_px,
                   vec2<int> size_pixel, std::string texture_name_1, 
                   std::string texture_name_2);
    void draw();
};

#endif