/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef GUI_SCENE_OPTIONS_MENU_HPP
#define GUI_SCENE_OPTIONS_MENU_HPP

#include "gui_scene.hpp"
#include <math.h>

class gui_scene_options_menu : public gui_scene {
public:
    using gui_scene::gui_scene;
    void create();
    void update();

private:
    check_box* list_chromatic_pitch_check_boxes[15];
    check_box* list_accidentals_check_boxes[6];
    check_box* show_violin_notes;
    check_box* show_bass_notes;

    check_box* create_options_box(vec2<int> pos, vec2<int> size,
                           std::string texture_name, std::string info_text);
    vec2<int> radial_position(float radius, float angle);
    void create_circle_of_fifths(); // Quintenzirkel
    check_box* create_chromatic_pitch_symbol(unsigned int pitch, float radius, float angle,
                                     vec2<int> pos, vec2<int> size,
                                std::string texture_name, std::string info_text);
};

#endif