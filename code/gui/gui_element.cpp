/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/gui_element.hpp"

shape_buffers::shape_buffers()
{
}

shape_buffers::shape_buffers(unsigned int a, unsigned int b, unsigned int e, unsigned int i)
{
    vao = a;
    vbo = b;
    ebo = e;
    number_indices = i;
}

void shape_buffers::free()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

shape_data gui_element::get_shape_data()
{
    shape_data data;
    return data;
}

gui_element::~gui_element()
{
}

void gui_element::check_mouse_position(double mouse_x, double mouse_y)
{
    if (is_selectable) {
        if (mouse_x > pos_gl.x && mouse_x < pos_gl.x + size_gl.x) {
            if (mouse_y > pos_gl.y && mouse_y < pos_gl.y + size_gl.y) {
                mouse_is_on_hitbox = true;
            }
        }
    
        // a second hitbox is necessary for the white piano keys
        if (has_second_hitbox && !mouse_is_on_hitbox) {
            if (mouse_x > second_hitbox_pos.x && mouse_x < second_hitbox_pos.x + second_hitbox_size.x) {
                if (mouse_y > second_hitbox_pos.y && mouse_y < second_hitbox_pos.y + second_hitbox_size.y) {
                    mouse_is_on_hitbox = true;
                }
            }
        }
        if (mouse_is_on_hitbox) {
            mouse_is_on_hitbox = false;
            if (!is_hovered) {
                is_hovered = true;
                if (has_on_enter_event)
                {
                    on_enter_event_();
                }
            }
        } 
        else if (is_hovered) {
            is_hovered = false;
            if (has_on_leave_event) {
                on_leave_event_();
            }
        }
    }

}

void gui_element::set_callback(std::function<void ()> cb) {
    callback_ = cb;
}

void gui_element::set_on_enter_event(std::function<void ()> cb) {
    has_on_enter_event = true;
    on_enter_event_ = cb;
}

void gui_element::set_on_leave_event(std::function<void ()> cb) {
    has_on_leave_event = true;
    on_leave_event_ = cb;
}

void gui_element::mouse_click_event(char mouse_button) {
    
    if (mouse_button == 1) {
        callback_();
    }
}