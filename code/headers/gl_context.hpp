/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef GL_CONTEXT_HPP
#define GL_CONTEXT_HPP

#include "../../dependencies/glad/glad.h"
#include "../gui/headers/gui.hpp"
#include "sprites.hpp"
#include "shaders.hpp"
#include <vector>
#include "../gui/headers/program_state.hpp"
#include "textures.hpp"
#include <string>
#include <iostream>
#include "random_generator.hpp"
#include "notes_display.hpp"

// OS specific path to glfw3.h
#ifdef _WIN32
#include <C:/mingw-w64/mingw64/include/GLFW/glfw3.h>
//#elif _LINUX

#elif __gnu_linux__
#include </usr/include/GLFW/glfw3.h>

#elif __APPLE__
#include </usr/local/Cellar/glfw/3.3/include/GLFW/glfw3.h>
#else
#error OS not supported
#endif

class gl_context
{
public:
    unsigned int screen_size_x = 1280;
    unsigned int screen_size_y = 720;
    unsigned int framerate = 60;
    GLFWwindow *window;

    gl_context(unsigned int screen_x, unsigned int screen_y);

    int init();
private:
    program_state program_state_;
    sprite_manager sprites_;
    notes_display notes_display_;
    gui_manager* gui_pointer_;

    int current_note_ = 0;
    bool check_note(int button);
    void next_random_note();
    void process_button_event(int button_event);
};

#endif