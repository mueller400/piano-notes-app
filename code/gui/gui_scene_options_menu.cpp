/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/gui_scene_options_menu.hpp"

void gui_scene_options_menu::create() {
    int pos_x = 0;
    int pos_y = 60;

    gui_button *button_apply = new gui_button(screen_resolution_, 
                                        default_shader_, 
                                        text_renderer_,
                                        "Apply",
                                        {0.05f, 0.05f, 0.05f, 1.0f},
                                        vec2<int>(240, 830),
                                        vec2<int>(100, 40), 
                                        vec2<int>(20, 20), 
                                        {0.95f, 0.95f, 0.95f, 1.0f},
                                        vec2<int>{6, 6});
    button_apply->set_callback([this](){
        program_state_->button_event = 91;
        program_state_->show_options_menu = false;
    });

    gui_label *options_text_1 = new gui_label(screen_resolution_, 
                                              vec2<int>(160 + pos_x, 710 + pos_y), 
                                              vec2<int>(300, 100), 
                                              "Maximum Violin note:", 
                                              text_renderer_,
                                              TEXT_ALIGNMENT::LEFT);

    gui_label *options_text_2 = new gui_label(screen_resolution_, 
                                              vec2<int>(160 + pos_x, 650 + pos_y), 
                                              vec2<int>(300, 100), 
                                              "Minimum Violin note:", 
                                              text_renderer_,
                                              TEXT_ALIGNMENT::LEFT);

    gui_label *options_text_3 = new gui_label(screen_resolution_, 
                                              vec2<int>(160 + pos_x, 590 + pos_y), 
                                              vec2<int>(300, 100), 
                                              "Maximum Bass note:", 
                                              text_renderer_,
                                              TEXT_ALIGNMENT::LEFT);

    gui_label *options_text_4 = new gui_label(screen_resolution_, 
                                              vec2<int>(160 + pos_x, 530 + pos_y), 
                                              vec2<int>(300, 100), 
                                              "Minimum Bass note:", 
                                              text_renderer_,
                                              TEXT_ALIGNMENT::LEFT);

    std::string shape_name = "button_options_1";
    gui_button *violin_upper_border_up = new gui_button(screen_resolution_, 
                                        default_shader_, 
                                        text_renderer_,
                                        "\u2191",
                                        {0.05f, 0.05f, 0.05f, 1.0f},
                                        vec2<int>(400 + pos_x, 700 + pos_y),
                                        vec2<int>(40, 40), 
                                        vec2<int>(20, 20), 
                                        {0.658f, 0.376f, 0.376f, 1.0f},
                                        vec2<int>{6, 6});
    violin_upper_border_up->hover_color = {0.758f, 0.476f, 0.476f, 1.0f};                             
    violin_upper_border_up->set_callback([this]() {
        program_state_->button_event = 100;
    });

    gui_shapes_[shape_name] = create_element_shape(violin_upper_border_up->get_shape_data());

    gui_button *violin_upper_border_down = new gui_button(screen_resolution_, 
                                        default_shader_, 
                                        text_renderer_,
                                        "\u2193",
                                        {0.05f, 0.05f, 0.05f, 1.0f},
                                        vec2<int>(450 + pos_x, 700 + pos_y),
                                        vec2<int>(40, 40), 
                                        vec2<int>(20, 20), 
                                         {0.658f, 0.376f, 0.376f, 1.0f},
                                        vec2<int>{6, 6});
    violin_upper_border_down->hover_color = {0.758f, 0.476f, 0.476f, 1.0f}; 
    violin_upper_border_down->set_callback([this]() {
        program_state_->button_event = 101;
    });

    gui_button *violin_lower_border_up = new gui_button(screen_resolution_, 
                                        default_shader_, 
                                        text_renderer_,
                                        "\u2191",
                                        {0.05f, 0.05f, 0.05f, 1.0f},
                                        vec2<int>(400 + pos_x, 640 + pos_y),
                                        vec2<int>(40, 40), 
                                        vec2<int>(20, 20), 
                                        {0.376f, 0.658f, 0.439f, 1.0f},
                                        vec2<int>{6, 6});
    violin_lower_border_up->hover_color = {0.476f, 0.758f, 0.539f, 1.0f},
    violin_lower_border_up->set_callback([this]() {
        program_state_->button_event = 110;
    });

    gui_button *violin_lower_border_down = new gui_button(screen_resolution_, 
                                        default_shader_, 
                                        text_renderer_,
                                        "\u2193",
                                        {0.05f, 0.05f, 0.05f, 1.0f},
                                        vec2<int>(450 + pos_x, 640 + pos_y),
                                        vec2<int>(40, 40), 
                                        vec2<int>(20, 20), 
                                        {0.376f, 0.658f, 0.439f, 1.0f},
                                        vec2<int>{6, 6});
    violin_lower_border_down->hover_color = {0.476f, 0.758f, 0.539f, 1.0f},
    violin_lower_border_down->set_callback([this]() {
        program_state_->button_event = 111;
    });

    gui_button *bass_upper_border_up = new gui_button(screen_resolution_, 
                                        default_shader_, 
                                        text_renderer_,
                                        "\u2191",
                                        {0.05f, 0.05f, 0.05f, 1.0f},
                                        vec2<int>(400 + pos_x, 580 + pos_y),
                                        vec2<int>(40, 40), 
                                        vec2<int>(20, 20), 
                                         {0.658f, 0.376f, 0.376f, 1.0f},
                                        vec2<int>{6, 6});
    bass_upper_border_up->hover_color = {0.758f, 0.476f, 0.476f, 1.0f};
    bass_upper_border_up->set_callback([this]() {
        program_state_->button_event = 120;
    });

    gui_button *bass_upper_border_down = new gui_button(screen_resolution_, 
                                        default_shader_, 
                                        text_renderer_,
                                        "\u2193",
                                        {0.05f, 0.05f, 0.05f, 1.0f},
                                        vec2<int>(450 + pos_x, 580 + pos_y),
                                        vec2<int>(40, 40), 
                                        vec2<int>(20, 20), 
                                         {0.658f, 0.376f, 0.376f, 1.0f},
                                        vec2<int>{6, 6});
    bass_upper_border_down->hover_color = {0.758f, 0.476f, 0.476f, 1.0f};
    bass_upper_border_down->set_callback([this]() {
        program_state_->button_event = 121;
    });

    gui_button *bass_lower_border_up = new gui_button(screen_resolution_, 
                                        default_shader_, 
                                        text_renderer_,
                                        "\u2191",
                                        {0.05f, 0.05f, 0.05f, 1.0f},
                                        vec2<int>(400 + pos_x, 520 + pos_y),
                                        vec2<int>(40, 40), 
                                        vec2<int>(20, 20), 
                                        {0.376f, 0.658f, 0.439f, 1.0f},
                                        vec2<int>{6, 6});
    bass_lower_border_up->hover_color = {0.476f, 0.758f, 0.539f, 1.0f},
    bass_lower_border_up->set_callback([this]() {
        program_state_->button_event = 130;
    });

    gui_button *bass_lower_border_down = new gui_button(screen_resolution_, 
                                        default_shader_, 
                                        text_renderer_,
                                        "\u2193",
                                        {0.05f, 0.05f, 0.05f, 1.0f},
                                        vec2<int>(450 + pos_x, 520 + pos_y),
                                        vec2<int>(40, 40), 
                                        vec2<int>(20, 20), 
                                        {0.376f, 0.658f, 0.439f, 1.0f},
                                        vec2<int>{6, 6});
    bass_lower_border_down->hover_color = {0.476f, 0.758f, 0.539f, 1.0f},
    bass_lower_border_down->set_callback([this]() {
        program_state_->button_event = 131;
    });

    vec2<int> symbol_size = {80, 80};

    show_violin_notes = create_options_box(
                                        vec2<int>(150 + pos_x, 400 + pos_y), 
                                        symbol_size, 
                                        "clef.png",
                                        "Use Violin Clef");
    show_violin_notes->set_callback([this]() {
        if (program_state_->show_violin_notes) {
            program_state_->show_violin_notes = false;
            show_violin_notes->is_checked = false;
        } else {
            program_state_->show_violin_notes = true;
            show_violin_notes->is_checked = true;
        }
    });
    if (program_state_->show_violin_notes) {
        show_violin_notes->is_checked = true;
    }

    show_bass_notes = create_options_box(
                                        vec2<int>(150 + pos_x, 300 + pos_y), 
                                        symbol_size, 
                                        "bass_clef_symbol.png",
                                        "Use Bass Clef");
    show_bass_notes->set_callback([this]() {
        if (program_state_->show_bass_notes) {
            program_state_->show_bass_notes = false;
            show_bass_notes->is_checked = false;
        } else {
            program_state_->show_bass_notes = true;
            show_bass_notes->is_checked = true;
        }
    });
    if (program_state_->show_bass_notes) {
        show_bass_notes->is_checked = true;
    }

    check_box *show_natural_sign = create_options_box(
                                        vec2<int>(450 + pos_x, 400 + pos_y), 
                                        symbol_size, 
                                        "natural.png",
                                        "Use Natural");
    show_natural_sign->set_callback([this, show_natural_sign](){
        if (program_state_->accidentals[5]) {
            program_state_->accidentals[5] = false;
            show_natural_sign->is_checked = false;
        } else {
            program_state_->accidentals[5] = true;
            show_natural_sign->is_checked = true;
        }
    });
    list_accidentals_check_boxes[5] = show_natural_sign;

    check_box *show_double_flat_sign = create_options_box(
                                        vec2<int>(250 + pos_x, 300 + pos_y), 
                                        symbol_size, 
                                        "double_flat.png",
                                        "Use Double Flat");
    show_double_flat_sign->set_callback([this, show_double_flat_sign](){
        if (program_state_->accidentals[4]) {
            program_state_->accidentals[4] = false;
            show_double_flat_sign->is_checked = false;
        } else {
            program_state_->accidentals[4] = true;
            show_double_flat_sign->is_checked = true;
        }
    });
    list_accidentals_check_boxes[4] = show_double_flat_sign;

    check_box *show_no_accidental_sign = create_options_box(
                                        vec2<int>(450 + pos_x, 300 + pos_y), 
                                        symbol_size, 
                                        "no_accidental.png",
                                        "Use No Accidental");
    show_no_accidental_sign->set_callback([this, show_no_accidental_sign](){
        if (program_state_->accidentals[0]) {
            program_state_->accidentals[0] = false;
            show_no_accidental_sign->is_checked = false;
        } else {
            program_state_->accidentals[0] = true;
            show_no_accidental_sign->is_checked = true;
        }
    });
    list_accidentals_check_boxes[0] = show_no_accidental_sign;

    check_box *show_double_sharp_sign = create_options_box(
                                        vec2<int>(350 + pos_x, 300 + pos_y), 
                                        symbol_size, 
                                        "double_sharp.png",
                                        "Use Double Sharp");
    show_double_sharp_sign->set_callback([this, show_double_sharp_sign](){
        if (program_state_->accidentals[2]) {
            program_state_->accidentals[2] = false;
            show_double_sharp_sign->is_checked = false;
        } else {
            program_state_->accidentals[2] = true;
            show_double_sharp_sign->is_checked = true;
        }
    });
    list_accidentals_check_boxes[2] = show_double_sharp_sign;

    check_box *show_flat_sign = create_options_box(
                                        vec2<int>(250 + pos_x, 400 + pos_y), 
                                        symbol_size, 
                                        "flat.png",
                                        "Use Flat");
    show_flat_sign->set_callback([this, show_flat_sign](){
        if (program_state_->accidentals[3]) {
            program_state_->accidentals[3] = false;
            show_flat_sign->is_checked = false;
        } else {
            program_state_->accidentals[3] = true;
            show_flat_sign->is_checked = true;
        }
    });
    list_accidentals_check_boxes[3] = show_flat_sign;

    check_box *show_sharp_sign = create_options_box(
                                        vec2<int>(350 + pos_x, 400 + pos_y), 
                                        symbol_size, 
                                        "sharp.png",
                                        "Use Sharp");

    show_sharp_sign->set_callback([this, show_sharp_sign](){
        if (program_state_->accidentals[1]) {
            program_state_->accidentals[1] = false;
            show_sharp_sign->is_checked = false;
        } else {
            program_state_->accidentals[1] = true;
            show_sharp_sign->is_checked = true;
        }
    });
    list_accidentals_check_boxes[1] = show_sharp_sign;

    violin_upper_border_up->shape = gui_shapes_[shape_name];
    violin_upper_border_down->shape = gui_shapes_[shape_name];
    violin_lower_border_up->shape = gui_shapes_[shape_name];
    violin_lower_border_down->shape = gui_shapes_[shape_name];
    bass_upper_border_up->shape = gui_shapes_[shape_name];
    bass_upper_border_down->shape = gui_shapes_[shape_name];
    bass_lower_border_up->shape = gui_shapes_[shape_name];
    bass_lower_border_down->shape = gui_shapes_[shape_name];

    shape_name = "default_button_shape_1";
    gui_shapes_[shape_name] = create_element_shape(button_apply->get_shape_data());
    button_apply->shape = gui_shapes_[shape_name];

    gui_elements.push_back(options_text_1);
    gui_elements.push_back(options_text_2);
    gui_elements.push_back(options_text_3);
    gui_elements.push_back(options_text_4);
    gui_elements.push_back(violin_upper_border_up);
    gui_elements.push_back(violin_upper_border_down);
    gui_elements.push_back(violin_lower_border_up);
    gui_elements.push_back(violin_lower_border_down);
    gui_elements.push_back(bass_upper_border_up);
    gui_elements.push_back(bass_upper_border_down);
    gui_elements.push_back(bass_lower_border_up);
    gui_elements.push_back(bass_lower_border_down);
    gui_elements.push_back(show_violin_notes);
    gui_elements.push_back(show_bass_notes);
    gui_elements.push_back(show_natural_sign);
    gui_elements.push_back(show_double_flat_sign);
    gui_elements.push_back(show_double_sharp_sign);
    gui_elements.push_back(show_flat_sign);
    gui_elements.push_back(show_no_accidental_sign);
    gui_elements.push_back(show_sharp_sign);
    gui_elements.push_back(button_apply);

    create_circle_of_fifths();

    update();
}

check_box* gui_scene_options_menu::create_options_box(vec2<int> pos, vec2<int> size,
                           std::string texture_name, std::string info_text){

    check_box *new_check_box = new check_box(screen_resolution_, sprite_manager_,
                                             pos, 
                                             size, 
                                             texture_name,
                                             texture_name);
    new_check_box->switch_textures = true;
    new_check_box->normal_color = {0.85f, 0.85f, 0.85f, 0.5f};
    new_check_box->hover_color = {0.95f, 0.95f, 0.95f, 1.0f};
    new_check_box->overlay_normal_color = {0.95f, 0.95f, 0.95f, 1.0};
    new_check_box->overlay_hover_color = {1.0, 1.0, 1.0, 1.0};

    gui_label *label = new gui_label(screen_resolution_, 
                                              vec2<int>(160, 320), 
                                              vec2<int>(300, 100), 
                                              info_text,
                                              text_renderer_,
                                              TEXT_ALIGNMENT::LEFT);
    label->is_visible = false;

    new_check_box->set_on_enter_event([label](){
        label->is_visible = true;
    });    

    new_check_box->set_on_leave_event([label](){
        label->is_visible = false;
    });

    gui_elements.push_back(label);
    return new_check_box;
}

void gui_scene_options_menu::create_circle_of_fifths() {

    vec2<int> pos = {1530, 565};
    float radius = 1.1 * 200.0; // px
    float angle = 45.0; // degree
    int width = 120;
    vec2<int> size = {width, (int)(width * 208 / 294)};
    
    check_box* c_major = create_chromatic_pitch_symbol(0, radius * 1.1, 0.0,
                                        pos,
                                        size,
                                        "c_major.png",
                                        "C major\n/\nA minor");

    check_box* g_major = create_chromatic_pitch_symbol(1, radius * 1.1, 35.0,
                                        pos,
                                        size,
                                        "g_major.png",
                                        "G major\n/\nE minor");

    check_box* d_major = create_chromatic_pitch_symbol(2, radius, 60.0,
                                        pos,
                                        size,
                                        "d_major.png",
                                        "D major\n/\nB minor");

    check_box* a_major = create_chromatic_pitch_symbol(3, radius, 85.0,
                                        pos,
                                        size,
                                        "a_major.png",
                                        "A major\n/\nF-sharp minor");

    check_box* e_major = create_chromatic_pitch_symbol(4, radius, 110.0,
                                        pos,
                                        size,
                                        "e_major.png",
                                        "E major\n/\nC-sharp minor");

    check_box* b_major = create_chromatic_pitch_symbol(5, radius, 140.0,
                                        pos,
                                        size,
                                        "b_major.png",
                                        "B major\n/\nG-sharp minor");

    check_box* c_flat_major = create_chromatic_pitch_symbol(6, radius * 1.52, 140.0,
                                        pos,
                                        size,
                                        "c_flat_major.png",
                                        "C-flat major");

    check_box* f_sharp_major = create_chromatic_pitch_symbol(7, radius * 1.21, 166.5,
                                        pos,
                                        size,
                                        "f_sharp_major.png",
                                        "F-sharp major\n/\nD-sharp minor");

    check_box* g_flat_major = create_chromatic_pitch_symbol(8, radius * 1.21, 193.5,
                                        pos,
                                        size,
                                        "g_flat_major.png",
                                        "G-flat major\n/\nE-flat minor");

    check_box* d_flat_major = create_chromatic_pitch_symbol(9,radius, 220.0,
                                        pos,
                                        size,
                                        "d_flat_major.png",
                                        "D-flat major\n/\nB-flat minor");

    check_box* c_sharp_major = create_chromatic_pitch_symbol(10, radius * 1.52, 220.0,
                                        pos,
                                        size,
                                        "c_sharp_major.png",
                                        "C-sharp major");

    check_box* a_flat_major = create_chromatic_pitch_symbol(11, radius, 250.0,
                                        pos,
                                        size,
                                        "a_flat_major.png",
                                        "A-flat major\n/\nF minor"); 

    check_box* e_flat_major = create_chromatic_pitch_symbol(12, radius, 275.0,
                                        pos,
                                        size,
                                        "e_flat_major.png",
                                        "E-flat major\n/\nC minor");

    check_box* b_flat_major = create_chromatic_pitch_symbol(13, radius, 300.0,
                                        pos,
                                        size,
                                        "b_flat_major.png",
                                        "B-flat major\n/\nG minor");

    check_box* f_major = create_chromatic_pitch_symbol(14, radius * 1.1, 325.0,
                                        pos,
                                        size,
                                        "f_major.png",
                                        "F major\n/\nD minor");                                                 
    gui_elements.push_back(c_major);
    gui_elements.push_back(g_major);
    gui_elements.push_back(d_major);
    gui_elements.push_back(a_major);
    gui_elements.push_back(e_major);
    gui_elements.push_back(b_major);
    gui_elements.push_back(f_sharp_major);
    gui_elements.push_back(g_flat_major);
    gui_elements.push_back(d_flat_major);
    gui_elements.push_back(a_flat_major);
    gui_elements.push_back(e_flat_major);
    gui_elements.push_back(b_flat_major);
    gui_elements.push_back(f_major);
    gui_elements.push_back(c_flat_major);
    gui_elements.push_back(c_sharp_major);

}

check_box* gui_scene_options_menu::create_chromatic_pitch_symbol(unsigned int pitch, float radius, float angle,
                                                          vec2<int> pos, vec2<int> size,
                                                          std::string texture_name, std::string info_text) {
    check_box* new_check_box = new check_box(screen_resolution_, sprite_manager_,
                                        add_vec2(pos, radial_position(radius, angle)),
                                        size,
                                        texture_name,
                                        texture_name);
    new_check_box->normal_color = {0.85f, 0.85f, 0.85f, 0.5f};
    new_check_box->hover_color = {0.95f, 0.95f, 0.95f, 1.0f};
    new_check_box->overlay_normal_color = {0.95f, 0.95f, 0.95f, 1.0};
    new_check_box->overlay_hover_color = {1.0f, 1.0f, 1.0f, 1.0f};
    new_check_box->switch_textures = true;
    if (program_state_->chromatic_pitches[pitch].is_used) {
        new_check_box->is_checked = true;
    }
    new_check_box->set_callback([this, new_check_box, pitch]() {
        if (new_check_box->is_checked) {
                program_state_->chromatic_pitches[pitch].is_used = false;
                new_check_box->is_checked = false;
        } else {
            new_check_box->is_checked = true;
            program_state_->chromatic_pitches[pitch].is_used = true;
        }
    });

    gui_label *label = new gui_label(screen_resolution_, 
                                              add_vec2(pos, vec2<int>(-100, 60)),
                                              vec2<int>(300, 100),
                                              info_text,
                                              text_renderer_,
                                              TEXT_ALIGNMENT::CENTER);
    label->is_visible = false;

    new_check_box->set_on_enter_event([label](){
        label->is_visible = true;
    });    

    new_check_box->set_on_leave_event([label](){
        label->is_visible = false;
    });

    gui_elements.push_back(label);

    list_chromatic_pitch_check_boxes[pitch] = new_check_box;
    return new_check_box;
}

vec2<int> gui_scene_options_menu::radial_position(float radius, float angle) {
    vec2<int> pos = {0, 0};
    pos.x = (int)(sin(angle * (3.14159265359 / 180)) * radius);
    pos.y = (int)(cos(angle * (3.14159265359 / 180)) * radius);
    return pos;
}

void gui_scene_options_menu::update() {

    for (int i = 0; i < 6; i++) {
        if (program_state_->accidentals[i]) {
            list_accidentals_check_boxes[i]->is_checked = true;
        }
        else {
            list_accidentals_check_boxes[i]->is_checked = false;
        }
    }

    for (int i = 0; i < 15; i++) {
        if (program_state_->chromatic_pitches[i].is_used) {
            list_chromatic_pitch_check_boxes[i]->is_checked = true;
        }
        else {
            list_chromatic_pitch_check_boxes[i]->is_checked = false;
        }
    }

    if (program_state_->show_violin_notes) {
        show_violin_notes->is_checked = true;
    } else {
        show_violin_notes->is_checked = false;
    }

    if (program_state_->show_bass_notes) {
        show_bass_notes->is_checked = true;
    } else {
        show_bass_notes->is_checked = false;
    }
}