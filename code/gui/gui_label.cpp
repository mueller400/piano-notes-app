/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/gui_label.hpp"

gui_label::gui_label(vec2<unsigned int> screen, vec2<int> position_px, 
                     vec2<int> size_px, std::string text, text_renderer *tr,
                     TEXT_ALIGNMENT text_alignment) : screen_resolution_(screen), 
                                                      text_renderer_(tr) {

    pos_gl = coord_pixel_to_gl(position_px, screen);
    size_gl = length_pixel_to_gl(size_px, screen);
    normal_color = color<float>(1.0f, 1.0f, 1.0f, 1.0f);
    
    label_text_ = text_renderer_->create_text_block(text, vec2<float>((float)size_px.x,
                                                   (float)size_px.y), text_alignment);
    
    vertical_text_offset = gl_to_px(label_text_.offset_y, screen.y);
    vec2<float> tmp = length_gl_to_pixel(label_text_.boundary, screen);
    text_content_boundary = vec2<int>((int)tmp.x, (int)tmp.y);
}

void gui_label::draw()
{
    text_renderer_->render_text(label_text_, pos_gl, vec2<float>(1.0f, 1.0f), normal_color);
}