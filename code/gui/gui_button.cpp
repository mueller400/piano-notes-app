/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/gui_button.hpp"

gui_button::gui_button(vec2<unsigned int> screen,
                       unsigned int shader,
                       text_renderer* text_renderer,
                       std::string button_text,
                       color<float> button_text_color,
                       vec2<int> position_px, 
                       vec2<int> size_pixel,
                       vec2<int> padding_px,
                       color<float> button_color,
                       vec2<int> border_width_px) : shader_(shader) {

    // create gui_label
    vec2<int> label_bounding_box = sub_vec2<int>(size_pixel, padding_px);
    button_label = gui_label(screen, position_px, label_bounding_box, button_text, text_renderer);
    button_label.normal_color = button_text_color;
    vec2<int> label_pos = vec2<int>(position_px.x + padding_px.x / 2, 
                                    position_px.y + size_pixel.y - button_label.vertical_text_offset - padding_px.y / 2);
    button_label.pos_gl = coord_pixel_to_gl(label_pos, screen);

    // create button
    pos_px = vec2<float>(position_px.x, position_px.y);
    pos_gl = coord_pixel_to_gl(position_px, screen);
    size_gl = length_pixel_to_gl(size_pixel, screen);
    size_px = vec2<float>(size_pixel.x, size_pixel.y);
    border_size_gl = length_pixel_to_gl(border_width_px, screen);
    border_size_px = vec2<float>(border_width_px.x, border_width_px.y);
    normal_color = button_color;
    is_selectable = true;
    callback_ = [](){};
}

shape_data gui_button::get_shape_data()
{
    shape_data data;
    data.number_vertices = 36;

    data.vertices_data = new float[data.number_vertices] {
        // position                                                     // shade
        // middle
        size_gl.x - border_size_gl.x,   size_gl.y - border_size_gl.y,   1.0f,   // top right      0
        size_gl.x - border_size_gl.x,   border_size_gl.y,               1.0f,   // bottom right   1
        border_size_gl.x,               border_size_gl.y,               1.0f,   // bottom left    2
        border_size_gl.x,               size_gl.y - border_size_gl.y,   1.0f,   // top left       3

        // border top
        size_gl.x,                      size_gl.y,                      1.2f,   // top right      4
                                                                                // bottom right   0
                                                                                // bottom left    3
        0.0f,                           size_gl.y,                      1.2f,   // top left       5

        // border left
                                                                                // top right      3
                                                                                // bottom right   2
        0.0f,                           0.0f,                           0.7f,   // bottom left    6
        0.0f,                           size_gl.y,                      0.7f,   // top left       7

        // border bottom
                                                                                // top right      1
        size_gl.x,                      0.0f,                           0.4f,   // bottom right   8
        0.0f,                           0.0f,                           0.4f,   // bottom left    9
                                                                                // top left       2

        // border right
        size_gl.x,                      size_gl.y,                      0.7f,   // top right      10
        size_gl.x,                      0.0f,                           0.7f    // bottom right   11
                                                                                // bottom left    1
                                                                                // top left       0
    };

    data.number_indices = 30;
    data.indices_data = new unsigned int[data.number_indices] {
        // middle
        2, 3, 1,
        1, 3, 0,

        // border top
        3, 5, 0,
        0, 5, 4,

        // border left
        6, 7, 2,
        2, 7, 3,

        // border bottom
        9, 2, 8,
        8, 2, 1,

        // border right
        1, 0, 11,
        11, 0, 10
    };

    return data;
}

void gui_button::draw()
{
    glUseProgram(shader_);

    unsigned int color = glGetUniformLocation(shader_, "color");
    unsigned int offset = glGetUniformLocation(shader_, "offset");
    unsigned int shape_scale = glGetUniformLocation(shader_, "scale");

    glUniform2f(offset, pos_gl.x, pos_gl.y);
    glUniform2f(shape_scale, scale.x, scale.y);
    if (is_hovered)
    {
        glUniform4f(color, hover_color.r, hover_color.g, hover_color.b, 
                    hover_color.a);
    }
    else
    {
        glUniform4f(color, normal_color.r, normal_color.g, normal_color.b, 
                    normal_color.a);
    }
    glBindVertexArray(shape.vao);
    glDrawElements(GL_TRIANGLES, shape.number_indices, GL_UNSIGNED_INT, 0);

    if (show_label)
    {
        button_label.draw();
    }
}

texture_button::texture_button(vec2<unsigned int> screen, sprite_manager* sprite_manager, vec2<int> position_px, 
                               vec2<int> size_pixel, std::string texture_name) : 
                                        sprite_manager_(sprite_manager) {
    pos_px = vec2<float>(position_px.x, position_px.y);
    pos_gl = coord_pixel_to_gl(position_px, screen);
    size_gl = length_pixel_to_gl(size_pixel, screen);
    size_px = vec2<float>(size_pixel.x, size_pixel.y);
    is_selectable = true;
    has_mouse_click_event = true;
    sprite_ = sprite_manager_->create_sprite(pos_px.x + size_px.x / 2, pos_px.y + size_px.y / 2,
                                             size_px.x, size_px.y,
                                             texture_name);
    vao_ = sprite_manager_->get_rectangle();
    callback_ = [](){};
}

void texture_button::draw() {
    glUseProgram(sprite_.shader);

    unsigned int offset_uniform = glGetUniformLocation(sprite_.shader, "offset");
    unsigned int scale_uniform = glGetUniformLocation(sprite_.shader, "scale");
    unsigned int rotation_uniform = glGetUniformLocation(sprite_.shader, "rotation");
    unsigned int color_uniform = glGetUniformLocation(sprite_.shader, "color");

    if (is_hovered)
    {
        glUniform4f(color_uniform, hover_color.r, hover_color.g, hover_color.b, 
                    hover_color.a);
    }
    else
    {
        glUniform4f(color_uniform, normal_color.r, normal_color.g, normal_color.b, 
                    normal_color.a);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao_);

    glUniform2f(offset_uniform, sprite_.pos.x, sprite_.pos.y);
    glUniform2f(scale_uniform, sprite_.size.x, sprite_.size.y);
    glUniform1f(rotation_uniform, sprite_.rotation);

    glBindTexture(GL_TEXTURE_2D, sprite_.texture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

check_box::check_box(vec2<unsigned int> screen, sprite_manager* sprite_manager,
                    vec2<int> position_px,
                   vec2<int> size_pixel, std::string texture_name_1, 
                   std::string texture_name_2) : sprite_manager_(sprite_manager) {

    pos_px = vec2<float>(position_px.x, position_px.y);
    pos_gl = coord_pixel_to_gl(position_px, screen);
    size_gl = length_pixel_to_gl(size_pixel, screen);
    size_px = vec2<float>(size_pixel.x, size_pixel.y);

    is_selectable = true;
    has_mouse_click_event = true;
    sprite_ = sprite_manager_->create_sprite(pos_px.x + size_px.x / 2, pos_px.y + size_px.y / 2,
                                             size_px.x, size_px.y,
                                             texture_name_1);
    
    texture_manager* textures = sprite_manager_->get_texture_manager();
    textures->load_texture(texture_name_2, texture_name_2);
    overlay_texture_ = textures->get_texture(texture_name_2);
    vao_ = sprite_manager_->get_rectangle();
    callback_ = [](){};
}

void check_box::draw() {
    glUseProgram(sprite_.shader);

    unsigned int offset_uniform = glGetUniformLocation(sprite_.shader, "offset");
    unsigned int scale_uniform = glGetUniformLocation(sprite_.shader, "scale");
    unsigned int rotation_uniform = glGetUniformLocation(sprite_.shader, "rotation");
    unsigned int color_uniform = glGetUniformLocation(sprite_.shader, "color");

    if (is_hovered)
    {
        glUniform4f(color_uniform, hover_color.r, hover_color.g, hover_color.b, 
                    hover_color.a);
    }
    else
    {
        glUniform4f(color_uniform, normal_color.r, normal_color.g, normal_color.b, 
                    normal_color.a);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao_);

    glUniform2f(offset_uniform, sprite_.pos.x, sprite_.pos.y);
    glUniform2f(scale_uniform, sprite_.size.x, sprite_.size.y);
    glUniform1f(rotation_uniform, sprite_.rotation);

    if (!is_checked || (is_checked && !switch_textures)) {
        glBindTexture(GL_TEXTURE_2D, sprite_.texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (is_checked) {
        if (is_hovered)
        {
            glUniform4f(color_uniform, overlay_hover_color.r, overlay_hover_color.g, 
                        overlay_hover_color.b, overlay_hover_color.a);
        }
        else
        {
            glUniform4f(color_uniform, overlay_normal_color.r, overlay_normal_color.g, 
                        overlay_normal_color.b, overlay_normal_color.a);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(vao_);

        glBindTexture(GL_TEXTURE_2D, overlay_texture_);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}