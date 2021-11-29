/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef GUI_HPP
#define GUI_HPP 

#include "../../headers/shaders.hpp"
#include "../../headers/sprites.hpp"
#include <string>
#include "gui_element.hpp"
#include "gui_button.hpp"
#include "gui_label.hpp"
#include "text_renderer.hpp"
#include <vector>
#include <map>
#include "gui_scene_1.hpp"
#include "gui_scene_options_menu.hpp"


class gui_manager
{
public: 

    gui_manager(unsigned int screen_size_x, unsigned int screen_size_y, std::string shader_folder,
                program_state* program_state);
    ~gui_manager();
    void create_scenes();
    void render_gui();
    void update_mouse_position(double x, double y);
    void mouse_click_event(char mouse_button);
    void change_gui_scene();
    void change_text(std::string new_text);
    void update_options_menu();

private:
    vec2<unsigned int> screen_resolution_;
    float screen_ratio_ = 16.0f / 9.0f;
    shader_manager* shaders_;
    text_renderer* text_renderer_;
    sprite_manager* sprite_manager_;
    unsigned int default_shader_;
    std::map<std::string, shape_buffers> gui_shapes_;
    std::map<std::string, gui_scene*> scenes_;
    gui_scene* current_scene_;
    program_state* program_state_;
    sprite background_;

    std::string display_text_;
    void setup_default_shader();
};

#endif
