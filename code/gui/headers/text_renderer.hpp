/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include "../../../dependencies/glad/glad.h"
#include "../../headers/units.hpp"
#include "../../headers/shaders.hpp"
#include <map>
#include <vector>
#include <locale>

#include <ft2build.h>
#include FT_FREETYPE_H

struct glyph 
{
    vec2<int> size;
    vec2<int> bearing;
    long int offset_x;
    unsigned int texture;
};

struct glyph_data
{
    vec2<float> pos_gl;
    vec2<float> size_gl;
    unsigned int texture;
};

struct word
{
    vec2<float> pos;
    vec2<float> size;
    std::vector<glyph_data> glyphs;
    unsigned short int whitespace_count = 0;
    bool end_of_line = false;
};

struct text_line
{
    float length;
    vec2<float> pos;
    std::vector<word> words;
};

struct text_block
{
    vec2<float> boundary;
    float offset_y;
    std::vector<text_line> lines;
};

typedef std::map<unsigned short int, glyph> font;
typedef std::map<std::string, font> font_map;

enum class TEXT_ALIGNMENT
{
    LEFT = -1,
    CENTER = 0,
    RIGHT = 1
};

class text_renderer
{
public:
    font_map fonts;
    
    text_renderer(shader_manager *sm);
    void init(vec2<unsigned int> screen);
    bool load_font_from_file(std::string font_name, std::string font_file, unsigned int font_size,
                             std::string character_map);
    bool load_font_from_file(std::string font_name, std::string font_file, unsigned int font_size, 
                             unsigned short int character_count);

    text_block create_text_block(std::string text,
                                 vec2<float> bounding_box_px,
                                 TEXT_ALIGNMENT text_alignment = TEXT_ALIGNMENT::LEFT,
                                 std::string font_name = "arial_24");

    void render_text(text_block &text, vec2<float> pos, vec2<float> scale, 
                     color<float> color_ = color<float>{0.0f, 0.0f, 0.0f, 1.0f});

private:
    shader_manager *shaders_;
    vec2<unsigned int> screen_resolution_;
    unsigned int text_shader_;
    unsigned int vao_;
    unsigned int vbo_;
    unsigned int ebo_;

    std::vector<uint16_t> convert_utf_8_to_unicode(std::string &str);
    bool load_font_from_file(std::string font_name, std::string font_file, unsigned int font_size, 
                             std::string character_map, unsigned short int character_count);
};

#endif