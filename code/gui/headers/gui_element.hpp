/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef GUI_ELEMENT_HPP
#define GUI_ELEMENT_HPP

#include "../../../dependencies/glad/glad.h"
#include <iostream>
#include "../../headers/units.hpp"
#include <functional>

struct shape_data
{
public:
    float *vertices_data;
    unsigned int *indices_data;
    unsigned int number_vertices;
    unsigned int number_indices;
};

struct shape_buffers
{
public:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int number_indices;

    shape_buffers();
    shape_buffers(unsigned int a, unsigned int b, unsigned int e, unsigned int i);
    void free();
};

class gui_element
{
public:
    vec2<float> pos_gl;
    vec2<float> pos_px;
    int top;
    int bottom;
    int left;
    int right;
    vec2<float> size_gl;
    vec2<float> size_px;
    vec2<float> scale = vec2<float>(1.0, 1.0);
    color<float> normal_color = {0.9f, 0.9f, 0.9f, 1.0f};
    color<float> hover_color = {1.0f, 1.0f, 1.0f, 1.0f};
    bool has_second_hitbox = false;
    bool mouse_is_on_hitbox = false;
    vec2<double> second_hitbox_pos;
    vec2<double> second_hitbox_size;
    bool is_selectable = false;
    bool is_visible = true;
    bool is_hovered = false;
    bool has_on_enter_event = false;
    bool has_on_leave_event = false;
    bool has_mouse_click_event = false;
    shape_buffers shape;

    virtual ~gui_element();
    virtual shape_data get_shape_data();
    virtual void draw() = 0;

    void check_mouse_position(double mouse_x, double mouse_y);
    void mouse_click_event(char mouse_button);
    void set_callback(std::function<void ()> cb);
    void set_on_enter_event(std::function<void ()> cb);
    void set_on_leave_event(std::function<void ()> cb);


protected:
    std::function<void ()> callback_;    
    std::function<void ()> on_enter_event_;
    std::function<void ()> on_leave_event_;

};

#endif