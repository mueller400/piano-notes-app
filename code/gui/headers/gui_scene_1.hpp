/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef GUI_SCENE_1_HPP
#define GUI_SCENE_1_HPP

#include "gui_scene.hpp"

class gui_scene_1 : public gui_scene {
public:
    using gui_scene::gui_scene;
    void create();
    void update();
private:
    texture_button* create_white_key(char type, int pos_x, int pos_y, sprite_manager* spr_m,
                                     int button_number); //type: (1,2,3)
    texture_button* create_black_key(int pos_x, int pos_y, sprite_manager* spr_m,
                                     int button_number);
};

#endif