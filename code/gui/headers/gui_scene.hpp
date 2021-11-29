/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef GUI_SCENE_HPP
#define GUI_SCENE_HPP

#include "gui_button.hpp"
#include "program_state.hpp"

class gui_scene {
public:
    bool is_visible = false;
    std::vector<gui_element*> gui_elements;

    bool overlay_is_visible = false;
    std::vector<gui_scene*> overlays;
    
    gui_scene(vec2<unsigned int> screen, float screen_ratio, 
              shader_manager* shaders, text_renderer* text_renderer, 
              unsigned int default_shader, sprite_manager* sprite_manager,
              program_state* ps) 
                : screen_resolution_(screen),
                  screen_ratio_(screen_ratio),
                  shaders_(shaders),
                  text_renderer_(text_renderer),
                  default_shader_(default_shader),
                  sprite_manager_(sprite_manager),
                  program_state_(ps) {};
    virtual void create() = 0;
    virtual void update() = 0;
    void draw();

protected:
    program_state* program_state_;
    float screen_ratio_;
    vec2<unsigned int> screen_resolution_;
    shader_manager* shaders_;
    text_renderer* text_renderer_;
    unsigned int default_shader_;
    sprite_manager* sprite_manager_;
    
    std::map<std::string, shape_buffers> gui_shapes_;

    shape_buffers create_element_shape(shape_data data)
    {
        unsigned int vao, vbo, ebo;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.number_vertices * sizeof(float), data.vertices_data, 
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.number_indices * sizeof(unsigned int), 
                     data.indices_data, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // shade attribute
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        shape_buffers shape(vao, vbo, ebo, data.number_indices);
        return shape;
    }
};

#endif