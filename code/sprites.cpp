/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/sprites.hpp"

sprite_manager::sprite_manager() {

}

sprite_manager::sprite_manager(vec2<unsigned int> screen, std::string texture_folder_path) : textures_(texture_folder_path)
{
    screen_resolution_ = screen;
    shaders_.create_default_shader();
    default_shader_ = shaders_.get_default_shader();
    create_rectangle();
}

void sprite_manager::init(vec2<unsigned int> screen, std::string texture_folder_path)
{
    textures_ = texture_manager(texture_folder_path);
    screen_resolution_ = screen;
    shaders_.create_default_shader();
    default_shader_ = shaders_.get_default_shader();
    create_rectangle();
}

sprite sprite_manager::create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                                     color<float> col, unsigned int texture, unsigned int shader)
{
    sprite spr;
    spr.pos = coord_pixel_to_gl(vec2<int>(pos_px_x, pos_px_y), screen_resolution_);
    spr.size = length_pixel_to_gl(vec2<int>(size_px_x, size_px_y), screen_resolution_);
    spr.rotation = 0.0;
    spr.col = col;
    spr.texture = texture;
    spr.shader = shader;
    return spr;
}

sprite sprite_manager::create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                                     unsigned int texture, unsigned int shader)
{
    return create_sprite(pos_px_x, pos_px_y, size_px_x, size_px_y,
                         color<float>(1.0f, 1.0f, 1.0f, 1.0f), texture, shader);
}

sprite sprite_manager::create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                                     color<float> col, unsigned int texture)
{
    return create_sprite(pos_px_x, pos_px_y, size_px_x, size_px_y, col, texture, default_shader_);
}

sprite sprite_manager::create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                                     unsigned int texture)
{
    return create_sprite(pos_px_x, pos_px_y, size_px_x, size_px_y, 
                         color<float>(1.0f, 1.0f, 1.0f, 1.0f), texture, default_shader_);
}

sprite sprite_manager::create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                                     color<float> col, std::string texture_name)
{
    textures_.load_texture(texture_name, texture_name);
    return create_sprite(pos_px_x, pos_px_y, size_px_x, size_px_y, col, textures_[texture_name], 
                         default_shader_);
}

sprite sprite_manager::create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                                     std::string texture_name)
{
    textures_.load_texture(texture_name, texture_name);
    return create_sprite(pos_px_x, pos_px_y, size_px_x, size_px_y, 
                         color<float>(1.0f, 1.0f, 1.0f, 1.0f), textures_[texture_name], 
                        default_shader_);
}

sprite sprite_manager::create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                                     color<float> col, std::string texture_name, 
                                     unsigned int shader)
{
    textures_.load_texture(texture_name, texture_name);
    return create_sprite(pos_px_x, pos_px_y, size_px_x, size_px_y, col, textures_[texture_name], 
                         shader);
}

sprite sprite_manager::create_sprite(int pos_px_x, int pos_px_y, int size_px_x, int size_px_y, 
                                     std::string texture_name, unsigned int shader)
{
    textures_.load_texture(texture_name, texture_name);
    return create_sprite(pos_px_x, pos_px_y, size_px_x, size_px_y, 
                         color<float>(1.0f, 1.0f, 1.0f, 1.0f), textures_[texture_name], shader);
}

void sprite_manager::create_rectangle() {

    float vertices[] = {
        // positions    // texture coords
        0.5f,  0.5f,  1.0f, 0.0f, // top right
        0.5f,  -0.5f,  1.0f, 1.0f, // bottom right
        -0.5f,  -0.5f,  0.0f, 1.0f, // bottom left
        -0.5f,  0.5f,  0.0f, 0.0f  // top left 
    };

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &rectangle_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(rectangle_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 
                         (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void sprite_manager::draw(sprite &spr) {

    glUseProgram(spr.shader);

    unsigned int offset_uniform = glGetUniformLocation(spr.shader, "offset");
    unsigned int scale_uniform = glGetUniformLocation(spr.shader, "scale");
    unsigned int rotation_uniform = glGetUniformLocation(spr.shader, "rotation");
    unsigned int color_uniform = glGetUniformLocation(spr.shader, "color");

    glUniform4f(color_uniform, spr.col.r, spr.col.g, spr.col.b, spr.col.a);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(rectangle_);

    glUniform2f(offset_uniform, spr.pos.x, spr.pos.y);
    glUniform2f(scale_uniform, spr.size.x, spr.size.y);
    glUniform1f(rotation_uniform, spr.rotation);

    glBindTexture(GL_TEXTURE_2D, spr.texture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int sprite_manager::get_rectangle() {
    return rectangle_;
}