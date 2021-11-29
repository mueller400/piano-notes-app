/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/gui.hpp"

gui_manager::gui_manager(unsigned int screen_size_x, unsigned int screen_size_y, 
                         std::string shader_folder, program_state* program_state) {
    screen_resolution_ = vec2<unsigned int>{screen_size_x, screen_size_y};
    shaders_ = new shader_manager(shader_folder);
    setup_default_shader();
    text_renderer_ = new text_renderer(shaders_);
    sprite_manager_ = new sprite_manager(screen_resolution_, "src/pictures");
    text_renderer_->init(screen_resolution_);
    display_text_ = "hello";
    program_state_ = program_state;
    background_ = sprite_manager_->create_sprite(screen_size_x / 2, screen_size_y / 2, screen_size_x, screen_size_y,
                                                 color<float>(0.0, 0.0, 0.0, 0.3), "white.png");
}

gui_manager::~gui_manager() {

}

void gui_manager::setup_default_shader() {
    std::string shader_name = "gui_default_shader";
    shaders_->create_shader_from_file(shader_name, "button_v_shader.glsl", "button_f_shader.glsl");
    default_shader_ = (*shaders_)[shader_name];
}

void gui_manager::update_mouse_position(double x, double y)
{
    std::vector<gui_element*>::iterator it;

    if (program_state_->show_options_menu) {
        for (it = scenes_["scene_options_menu"]->gui_elements.begin(); it != scenes_["scene_options_menu"]->gui_elements.end(); ++it)
        {
            if ((*it)->is_selectable)
            {
                (*it)->check_mouse_position(x, -y);
            }
        }
    }
    else {
        for (it = current_scene_->gui_elements.begin(); it != current_scene_->gui_elements.end(); ++it)
        {
            if ((*it)->is_selectable)
            {
                (*it)->check_mouse_position(x, -y);
            }
        }
    }

}

void gui_manager::render_gui()
{
    std::vector<gui_element*>::iterator it;

    for (it = current_scene_->gui_elements.begin(); it != current_scene_->gui_elements.end(); ++it)
    {
        if ((*it)->is_visible) {
            (*it)->draw();
        }
    }
    if (program_state_->show_options_menu) {
        sprite_manager_->draw(background_);
        for (it = scenes_["scene_options_menu"]->gui_elements.begin(); it != scenes_["scene_options_menu"]->gui_elements.end(); ++it)
        {
            if ((*it)->is_visible) {
                (*it)->draw();
            }
        }
    }
}

void gui_manager::change_gui_scene()
{

}

void gui_manager::change_text(std::string new_text)
{
    display_text_ = new_text;
    std::cout << display_text_ << std::endl;
}

void gui_manager::create_scenes(){
    
    scenes_["scene_1"] = new gui_scene_1(screen_resolution_, screen_ratio_,
                                         shaders_, text_renderer_, default_shader_,
                                         sprite_manager_, program_state_);
    scenes_["scene_1"]->create();

    scenes_["scene_options_menu"] = new gui_scene_options_menu(screen_resolution_, screen_ratio_,
                                         shaders_, text_renderer_, default_shader_,
                                         sprite_manager_, program_state_);
    scenes_["scene_options_menu"]->create();


    current_scene_ = scenes_["scene_1"];
}

void gui_manager::mouse_click_event(char mouse_button) {

    std::vector<gui_element*>::iterator it;

    if (program_state_->show_options_menu) {
        for (it = scenes_["scene_options_menu"]->gui_elements.begin(); it != scenes_["scene_options_menu"]->gui_elements.end(); ++it)
        {
            if ((*it)->is_hovered)
            {
                (*it)->mouse_click_event(mouse_button);
            }
        }
    }
    else {
        for (it = current_scene_->gui_elements.begin(); it != current_scene_->gui_elements.end(); ++it)
        {
            if ((*it)->is_hovered)
            {
                (*it)->mouse_click_event(mouse_button);
            }
        }
    }
}

void gui_manager::update_options_menu() {
    scenes_["scene_options_menu"]->update();
}