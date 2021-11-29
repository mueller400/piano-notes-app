/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/gui_scene_1.hpp"

void gui_scene_1::create() {

    // buttons
    std::string shape_name = "default_button_shape";

    // button quit
    gui_button *button = new gui_button(screen_resolution_, 
                                        default_shader_, 
                                        text_renderer_,
                                        "Quit",
                                        {0.05f, 0.05f, 0.05f, 1.0f},
                                        vec2<int>(20, 830),
                                        vec2<int>(100, 40), 
                                        vec2<int>(20, 20), 
                                        {0.95f, 0.95f, 0.95f, 1.0f},
                                        vec2<int>{6, 6});
    button->set_callback([this](){
        program_state_->close_application = true;
    });

    gui_shapes_[shape_name] = create_element_shape(button->get_shape_data());
    button->shape = gui_shapes_[shape_name];
    gui_elements.push_back(button);

    // options button
    gui_button *button2 = new gui_button(screen_resolution_, 
                              default_shader_,
                              text_renderer_,
                              "Options",
                              {0.05f, 0.05f, 0.05f, 1.0f},
                              vec2<int>(130, 830), 
                              vec2<int>(100, 40), 
                              vec2<int>(20, 20), 
                              {0.95f, 0.95f, 0.95f, 1.0f},
                              vec2<int>{6, 6});
    button2->set_callback([this](){
        program_state_->button_event = 90;
    });
    button2->shape = gui_shapes_[shape_name];
    gui_elements.push_back(button2);

    // create piano keys
    int offset = 36;
    int pos_x = 20;
    int pos_y = 40;
    bool is_black_key[12] = {true, false, false, true, false, true, false,
                             false, true, false, true, false};
    char key_types[7] = {3, 1, 2, 3, 1, 2, 2};
    unsigned int white_key_counter = 0;
    
    // key_A_2
    gui_elements.push_back(create_white_key(1, pos_x + offset * 0, pos_y, sprite_manager_, 1));

    for (int i = 0; i < 86; i++) {
        if (is_black_key[i % 12]) {
            gui_elements.push_back(create_black_key(pos_x + offset * (white_key_counter),
                                   pos_y, 
                                   sprite_manager_, 
                                   i + 2));
        } 
        else {
            gui_elements.push_back(create_white_key(key_types[white_key_counter % 7], 
                                   pos_x + offset * (white_key_counter + 1), 
                                   pos_y, sprite_manager_, 
                                   i + 2));
            white_key_counter++;
        }
    }

    // key_c_5
    texture_button* key_c_5 = new texture_button(screen_resolution_, sprite_manager_, vec2<int>(pos_x + offset * 51, 
                                                 pos_y), vec2<int>(35, 252), "key_white_4.png");
    key_c_5->hover_color = {1.0f, 0.7f, 0.3f, 1.0f};
    key_c_5->set_callback([this](){
        program_state_->button_event = 88;
    });
    gui_elements.push_back(key_c_5);
}

void gui_scene_1::update() {
}

texture_button* gui_scene_1::create_white_key(char type, int pos_x, int pos_y, sprite_manager* spr_m,
                                              int button_number){
    std::string texture_name = "";
    vec2<double>second_hitbox_pos;
    vec2<double>second_hitbox_size;
    switch (type)
    {
    case 1:
        texture_name = "key_white_1.png";
        second_hitbox_pos = coord_pixel_to_gl(vec2<double>((double)pos_x + 0.0, (double)pos_y + 90.0), screen_resolution_);
        second_hitbox_size = vec2<double>(2.0f / (double)screen_resolution_.x * 
                             (double)23, 2.0f / (double)screen_resolution_.y * (double)162);
        break;
    case 2:
        texture_name = "key_white_2.png";
        second_hitbox_pos = coord_pixel_to_gl(vec2<double>((double)pos_x + 11.2, (double)pos_y + 90.0), screen_resolution_);
        second_hitbox_size = vec2<double>(2.0f / (double)screen_resolution_.x * 
                             (double)11, 2.0f / (double)screen_resolution_.y * (double)162);
        break;
    case 3:
        texture_name = "key_white_3.png";
        second_hitbox_pos = coord_pixel_to_gl(vec2<double>((double)pos_x + 11.9, (double)pos_y + 90.0), screen_resolution_);
        second_hitbox_size = vec2<double>(2.0f / (double)screen_resolution_.x * 
                             (double)23, 2.0f / (double)screen_resolution_.y * (double)162);
        break;
    default:
        break;
    }
    texture_button* button = new texture_button(screen_resolution_, sprite_manager_, vec2<int>(pos_x, pos_y),
                                                     vec2<int>(35, 252), texture_name);

    button->size_gl = vec2<float>(2.0f / (double)screen_resolution_.x * 
                             (double)35, 2.0f / (double)screen_resolution_.y * (double)90);
    button->has_second_hitbox = true;
    button->second_hitbox_pos = second_hitbox_pos;
    button->second_hitbox_size = second_hitbox_size;

    button->hover_color = {1.0f, 0.7f, 0.3f, 1.0f};
    button->set_callback([this, button_number](){
        program_state_->button_event = button_number;
    });
    return button;
}

texture_button* gui_scene_1::create_black_key(int pos_x, int pos_y, sprite_manager* spr_m, 
                                              int button_number){
    texture_button* button = new texture_button(screen_resolution_, sprite_manager_, vec2<int>(pos_x + 24, pos_y + 91),
                                                     vec2<int>(23, 161), "key_black.png");
    button->normal_color = {0.05f, 0.05f, 0.05f, 1.0f};
    button->hover_color = {0.8745f, 0.588f, 0.055f, 1.0f};
    button->set_callback([this, button_number](){
        program_state_->button_event = button_number;
    });
    return button;
}