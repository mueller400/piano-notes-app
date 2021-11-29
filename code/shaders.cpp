/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/shaders.hpp"

shader_manager::shader_manager(std::string shader_folder) : shader_folder_(shader_folder)
{
}

shader_manager::shader_manager() : shader_folder_("src/shaders")
{
}

void shader_manager::create_default_shader()
{
    const char *vertex_shader_code = default_vertex_shader_code;
    const char *fragment_shader_code = default_fragment_shader_code;

    shaders_["default"] = compile_shader("default", vertex_shader_code, fragment_shader_code);
}

void shader_manager::create_shader_from_file(std::string name, std::string vertex_shader_source_file,
                                   std::string fragment_shader_source_file)
{

    std::string vertex = get_shader_code_from_file(vertex_shader_source_file);
    std::string fragment = get_shader_code_from_file(fragment_shader_source_file);
    const char *vertex_shader_code = vertex.c_str();
    const char *fragment_shader_code = fragment.c_str();

    shaders_[name] = compile_shader(name, vertex_shader_code, fragment_shader_code);
}

void shader_manager::create_shader_from_code(std::string name, const char *vertex_shader_code,
                                   const char *fragment_shader_code)
{
    shaders_[name] = compile_shader(name, vertex_shader_code, fragment_shader_code);
}

std::string shader_manager::get_shader_code_from_file(std::string shader_source_file)
{
    std::ifstream file_stream;
    std::string shader_code = "";

    file_stream.open(shader_folder_ + "/" + shader_source_file);

    if (file_stream.is_open())
    {
        std::string line;
        int counter = 0;
        while (std::getline(file_stream, line, '\n'))
        {
            shader_code += line + "\n";
        }
        file_stream.close();
    }
    else
    {
        std::cout << "ERROR: Could not open file >" << shader_folder_ + "/" + shader_source_file
                  << "<" << std::endl;
    }

    return shader_code;
}

unsigned int shader_manager::compile_shader(std::string shader_name, const char *vertex_shader_code,
                                            const char *fragment_shader_code)
{
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    bool compile_errors = false;
    glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
    glCompileShader(vertex_shader);
    if (check_compile_errors(shader_name + " (vertex)", vertex_shader))
    {
        compile_errors = true;
    }
    glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
    glCompileShader(fragment_shader);
    if (check_compile_errors(shader_name + " (fragment)", fragment_shader))
    {
        compile_errors = true;
    }

    if (compile_errors)
    {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return shaders_["default"];
    }

    unsigned int shader = glCreateProgram();
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader;
}

bool shader_manager::check_compile_errors(std::string shader_name, unsigned int shader)
{
    int compile_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

    if (!compile_status)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *error_message = new char[length];

        glGetShaderInfoLog(shader, length, &length, error_message);
        std::cout << "ERROR: Compile error in shader >" << shader_name
                  << "<: " << error_message << std::endl;
        delete[] error_message;

        return true;
    }
    return false;
}

unsigned int shader_manager::get_default_shader()
{
    return shaders_["default"];
}