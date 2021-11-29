/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef GUI_LABEL_HPP
#define GUI_LABEL_HPP

#include "gui_element.hpp"
#include "text_renderer.hpp"

class gui_label : public gui_element
{
private:
    text_renderer *text_renderer_;
    vec2<unsigned int> screen_resolution_;
    text_block label_text_;

public:
    int vertical_text_offset = 0;
    vec2<int> text_content_boundary = {0, 0};

    gui_label() {is_visible = false;}; // placeholder constructor
    gui_label(vec2<unsigned int> screen, 
              vec2<int> position_px, vec2<int> size_px, 
              std::string text, text_renderer *tr, 
              TEXT_ALIGNMENT text_alignment = TEXT_ALIGNMENT::CENTER);
    void draw();

};

#endif