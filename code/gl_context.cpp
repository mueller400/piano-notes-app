/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/gl_context.hpp"

double mouse_x = 1.0;
double mouse_y = 1.0;
bool mouse_click_event = false;
char mouse_button = 0;
int screen_x = 0;
int screen_y = 0;

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    mouse_x = xpos;
    mouse_y = ypos;
}

gl_context::gl_context(unsigned int x, unsigned int y)
{
    screen_x = x;
    screen_y = y;
    screen_size_x = x;
    screen_size_y = y;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        mouse_click_event = true;
        mouse_button = 1;
    }

    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        mouse_click_event = true;
        mouse_button = 3;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        mouse_click_event = true;
        mouse_button = 2;
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    screen_x = (unsigned int)width;
    screen_y = (unsigned int)height;
}

void gl_context::process_button_event(int button_event) {
    if (button_event > 0 && button_event < 89) {
        if (button_event == current_note_) {
            current_note_ = notes_display_.next_random_note();
        }
    } else if (button_event > 89) {
        switch (button_event)
        {
        case 90:
            gui_pointer_->update_options_menu();
            program_state_.show_options_menu = true;
            notes_display_.show_note_bounds();
            break;
        case 91:
            program_state_.show_options_menu = false;
            notes_display_.hide_note_bounds();
            program_state_.update_violin_bass_options();
            program_state_.update_random_chromatic_pitches();
            program_state_.update_random_accidentals();
            current_note_ = notes_display_.next_random_note();
            break;
        case 100:
            notes_display_.move_note_bound(0, 1);
            break;
        case 101:
            notes_display_.move_note_bound(0, -1);
            break;
        case 110:
            notes_display_.move_note_bound(1, 1);
            break;
        case 111:
            notes_display_.move_note_bound(1, -1);
            break;
        case 120:
            notes_display_.move_note_bound(2, 1);
            break;
        case 121:
            notes_display_.move_note_bound(2, -1);
            break;
        case 130:
            notes_display_.move_note_bound(3, 1);
            break;
        case 131:
            notes_display_.move_note_bound(3, -1);
            break;
        default:
            break;
        }
    }

    program_state_.button_event = 0;
}

bool gl_context::check_note(int button) {
    return button == current_note_ ? true : false;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int gl_context::init()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(screen_size_x, screen_size_y, "Piano", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    sprites_ = sprite_manager(vec2<unsigned int>(screen_size_x, screen_size_y), "src/pictures");


    gui_manager gui(screen_size_x, screen_size_y, "src/shaders", &program_state_);
    gui.create_scenes();
    gui_pointer_ = &gui;

    current_note_ = notes_display_.init(vec2<unsigned int>(screen_size_x, screen_size_y), &sprites_, &program_state_);

    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    double delta_time = 0.0;
    double last_frame = 0.0;
    double time = 0.0;

    double mouse_x;
    double mouse_y;

    while (!glfwWindowShouldClose(window))
    {
        if (program_state_.close_application) {
            glfwSetWindowShouldClose(window, 1);
        }

        if (program_state_.button_event != 0) {
            process_button_event(program_state_.button_event);
            program_state_.button_event = 0;
        }
        double current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        time += delta_time;

        if (time > 1.0f / (double)framerate)
        {
            time = 0.0f;

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            if (!glfwWindowShouldClose(window))
            {
                if (mouse_click_event) {
                    mouse_click_event = false;
                    gui.mouse_click_event(mouse_button);
                    mouse_button = 0;
                }
                glfwGetCursorPos(window, &mouse_x, &mouse_y);
                vec2<double> mouse_position = coord_pixel_to_gl(vec2<double>(mouse_x, mouse_y), 
                                                                {screen_x, screen_y});
                gui.update_mouse_position(mouse_position.x, mouse_position.y);
            }
            
            gui.render_gui();
            notes_display_.draw();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}