/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/text_renderer.hpp"

text_renderer::text_renderer(shader_manager *sm) : shaders_(sm)
{
}

void text_renderer::init(vec2<unsigned int> screen)
{
    screen_resolution_ = screen;

    std::string c_map = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890@!\"§$%&/()=?{[]},.-;:_#'+*~<>äöüÄÖÜß€\u2191\u2193";

    // load default font
    load_font_from_file("arial_24", "src/fonts/arial.ttf", 24, c_map);

    // create shader
    std::string shader_name = "text_default_shader";
    shaders_->create_shader_from_file(shader_name, "text_v_shader.glsl", "text_f_shader.glsl");
    text_shader_ = (*shaders_)[shader_name];
}

bool text_renderer::load_font_from_file(std::string font_name, std::string font_file,
                                        unsigned int font_size, std::string character_map)
{
    return load_font_from_file(font_name, font_file, font_size, character_map, 0);
}

bool text_renderer::load_font_from_file(std::string font_name, std::string font_file,
                                        unsigned int font_size, unsigned short int character_count)
{
    return load_font_from_file(font_name, font_file, font_size, "", character_count);
}

bool text_renderer::load_font_from_file(std::string font_name, std::string font_file,
                                        unsigned int font_size, std::string character_map, unsigned short int character_count)
{
    FT_Library library;

    int error = FT_Init_FreeType(&library);
    if (error)
    {
        std::cout << "Error: Could not initialize FreeType library." << std::endl;
        return false;
    }

    FT_Face face;

    error = FT_New_Face(library, font_file.c_str(), 0, &face);

    if (error == FT_Err_Unknown_File_Format)
    {
        std::cout << "Error: Could not load font: '" << font_file << "'. Unknown file format."
                  << std::endl;
        return false;
    }
    else if (error)
    {
        std::cout << "Error: Could not load font: '" << font_file << "'." << std::endl;
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, font_size);
    FT_Select_Charmap(face, ft_encoding_unicode);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    std::vector<uint16_t> list_characters;
    bool has_character_map = false;

    if (character_map != "")
    {
        list_characters = convert_utf_8_to_unicode(character_map);
        character_count = list_characters.size();
        has_character_map = true;
    }

    for (unsigned short int c = 0; c < character_count; c++)
    {
        if (has_character_map)
        {
            error = FT_Load_Char(face, list_characters[c], FT_LOAD_RENDER);
        }
        else
        {
            error = FT_Load_Char(face, c, FT_LOAD_RENDER);
        }
        
        if (error)
        {
            std::cout << "Warning: Could not load glyph from font: '" << font_file
                      << "'. Skipping glyph.." << std::endl;
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glyph gl = {
            vec2<int>(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            vec2<int>(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x,
            texture};

        if (has_character_map)
        {
            fonts[font_name].insert({std::pair<unsigned short int, glyph>(list_characters[c], gl)});
        }
        else
        {
            fonts[font_name].insert({std::pair<unsigned short int, glyph>(c, gl)});
        }
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(library);

    float vertices[] = {
        // positions     // texture coords
        1.0f, 1.0f, 1.0f, 0.0f, // top right
        1.0f, 0.0f, 1.0f, 1.0f, // bottom right
        0.0f, 0.0f, 0.0f, 1.0f, // bottom left
        0.0f, 1.0f, 0.0f, 0.0f  // top left
    };

    unsigned int indices[] = {
        2, 3, 1,
        1, 3, 0};

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return true;
}

text_block text_renderer::create_text_block(std::string text, vec2<float> bounding_box_px,
                                            TEXT_ALIGNMENT text_alignment,
                                            std::string font_name)
{
    text_block new_text;
    new_text.boundary = vec2<float>(0.0f, 0.0f);

    std::vector<uint16_t> glyph_indices = convert_utf_8_to_unicode(text);
    std::vector<uint16_t>::iterator it;

    vec2<float> glyph_offset(0.0f, 0.0f);

    word new_word = word();
    bool last_char_was_whitespace = false;

    float line_space = 0.08f; // temporary value!
    unsigned int line_count = 0;

    std::vector<word> list_words;

    // Iterate through all glyphs and create a list of words.
    for (it = glyph_indices.begin(); it != glyph_indices.end(); ++it)
    {
        switch (*it)
        {
        case '\t':
            new_word.whitespace_count += 4;
            last_char_was_whitespace = true;
            break;
        case '\n':
            new_word.size = glyph_offset;
            new_word.end_of_line = true;
            list_words.push_back(new_word);
            new_word.glyphs.clear();
            new_word = word();
            glyph_offset.x = 0.0;
            glyph_offset.y = 0.0;
            break;
        case ' ':
            ++new_word.whitespace_count;
            last_char_was_whitespace = true;
            break;
        default:
            if (last_char_was_whitespace)
            {
                new_word.size = glyph_offset;
                list_words.push_back(new_word);
                new_word.glyphs.clear();
                new_word = word();
                glyph_offset.x = 0.0;
                glyph_offset.y = 0.0;
                last_char_was_whitespace = false;
            }
            glyph gl = fonts[font_name][*it];
            glyph_data data;

            data.pos_gl = length_pixel_to_gl(vec2<int>(gl.bearing.x, gl.bearing.y - gl.size.y),
                                             screen_resolution_);
            data.pos_gl = add_vec2(data.pos_gl, glyph_offset);
            data.size_gl = length_pixel_to_gl(gl.size, screen_resolution_);

            glyph_offset = add_vec2(glyph_offset, length_pixel_to_gl(vec2<int>(gl.offset_x >> 6, 0.0f),
                                                                     screen_resolution_));

            data.texture = gl.texture;
            new_word.glyphs.push_back(data);
        }
    }
    new_word.size = glyph_offset;
    list_words.push_back(new_word);

    // Go through all words and update the position variable.
    vec2<float> word_position(0.0f, 0.0f);
    vec2<float> bounding_box_gl = length_pixel_to_gl(bounding_box_px, screen_resolution_);
    std::vector<word>::iterator word_it;

    // Get whitespace width.
    float whitespace = horizontal_length_px_to_gl(fonts[font_name][' '].offset_x >> 6, screen_resolution_.x);

    // Create lines and fill them with the words.
    text_line new_line;
    new_line.pos = vec2<float>(0.0f, 0.0f);
    float line_length = 0.0f;

    for (word_it = list_words.begin(); word_it != list_words.end(); ++word_it)
    {
        if (word_position.x + word_it->size.x > bounding_box_gl.x) // Longer than bounding box width.
        {
            // Mark as last word in the line if position is still at the 
            // beginning of the line.
            // This happens if a single word is longer than the boundary.
            if (word_position.x == 0.0f)
            {
                word_it->end_of_line = true;
            }
            else
            {
                // New line.
                new_line.length = line_length;
                new_text.lines.push_back(new_line);
                ++line_count;
                new_line.pos.x = 0.0;
                new_line.pos.y -= line_space;
                new_line.words.clear();

                word_position.x = 0.0;
            }
        }

        word_it->pos = word_position;
        line_length = word_position.x + word_it->size.x;

        if (line_length > new_text.boundary.x)
        {
            new_text.boundary.x = line_length;
        }

        word_position.x += word_it->whitespace_count * whitespace;
        new_line.words.push_back(*word_it);

        if (word_it->end_of_line)
        {
            // New line.
            new_line.length = line_length;
            new_text.lines.push_back(new_line);
            ++line_count;
            new_line.pos.x = 0.0;
            new_line.pos.y -= line_space;
            new_line.words.clear();

            word_position.x = 0.0;
        }
        else
        {
            word_position = add_vec2(word_position, word_it->size);
        }
    }
    new_line.length = line_length;
    new_text.lines.push_back(new_line);
    ++line_count;

    // Now align the lines depending on given text alignment.
    if (text_alignment != TEXT_ALIGNMENT::LEFT)
    {
        std::vector<text_line>::iterator line_it;
        for (line_it = new_text.lines.begin(); line_it != new_text.lines.end(); ++line_it)
        {
            if (text_alignment == TEXT_ALIGNMENT::CENTER)
            {
                line_it->pos.x = (bounding_box_gl.x - line_it->length) / 2.0;
            }
            else if (text_alignment == TEXT_ALIGNMENT::RIGHT)
            {
                line_it->pos.x = bounding_box_gl.x - line_it->length;
            }
        }
    }

    // Calculate text boundary box size.
    float highest_bearing_y = vertical_length_px_to_gl(fonts[font_name]['A'].bearing.y, 
                                                       screen_resolution_.y);
    float lowest_bearing_y = vertical_length_px_to_gl(fonts[font_name]['g'].size.y - fonts[font_name]['g'].bearing.y, 
                                                      screen_resolution_.y);
    new_text.boundary.y = (line_count - 1) * line_space +  highest_bearing_y + lowest_bearing_y;
    new_text.offset_y = highest_bearing_y;

    return new_text;
}

void text_renderer::render_text(text_block &text, vec2<float> pos, vec2<float> scale,
                                color<float> text_color)
{
    glUseProgram(text_shader_);

    unsigned int offset_uniform = glGetUniformLocation(text_shader_, "offset");
    unsigned int scale_uniform = glGetUniformLocation(text_shader_, "scale");
    unsigned int color_uniform = glGetUniformLocation(text_shader_, "color");

    glUniform4f(color_uniform, text_color.r, text_color.g, text_color.b, text_color.a);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao_);

    std::vector<text_line>::iterator line_it;
    std::vector<word>::iterator word_it;

    for (line_it = text.lines.begin(); line_it != text.lines.end(); ++line_it)
    {
        for (word_it = line_it->words.begin(); word_it != line_it->words.end(); ++word_it)
        {
            std::vector<glyph_data>::iterator glyph_it;
            for (glyph_it = word_it->glyphs.begin(); glyph_it != word_it->glyphs.end(); ++glyph_it)
            {
                glUniform2f(offset_uniform, pos.x + (line_it->pos.x + word_it->pos.x + glyph_it->pos_gl.x) * scale.x,
                            pos.y + (line_it->pos.y + word_it->pos.y + glyph_it->pos_gl.y) * scale.y);
                glUniform2f(scale_uniform, glyph_it->size_gl.x * scale.x, glyph_it->size_gl.y * scale.y);

                glBindTexture(GL_TEXTURE_2D, glyph_it->texture);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::vector<uint16_t> text_renderer::convert_utf_8_to_unicode(std::string &str)
{
    std::vector<uint16_t> list_unicodes;
    std::string::iterator it;

    int bytes_to_ignore = 0;
    int byte_control = 0; // Variable to control the byte flow.
    unsigned char byte_storage[] = {0, 0};

    for (it = str.begin(); it != str.end(); ++it)
    {
        unsigned char byte = (unsigned char)*it;

        // Look for multi byte sequence.
        if (byte >= 192) // 110x.xxxx
        {
            byte_storage[0] = byte;
            byte_control = 4;
            if (byte >= 224) // 1110.xxxx
            {
                byte_storage[0] = byte;
                byte_control = 3;
                if (byte >= 240) // 1111.0xxx
                {
                    byte_control = 0;
                    bytes_to_ignore = 4;
                    byte_storage[0] = 0;
                    list_unicodes.push_back(63); // 63 = '?'
                }
            }
        }

        switch (byte_control)
        {
        case 1:
        {
            uint16_t code = byte_storage[0] & 31; // 31 = 0001.1111
            code <<= 6;                           // Shift to the left.

            if (byte_storage[1] > 0) // Three bytes to process.
            {
                byte_storage[1] &= 63; // 00xx.xxx
                code |= byte_storage[1];
                code <<= 6;
            }

            byte &= 63; // 00xx.xxx
            code |= byte;

            list_unicodes.push_back(code);
            byte_control = 0;
            byte_storage[0] = 0;
            byte_storage[1] = 0;
            break;
        }
        case 2:
            byte_storage[1] = byte;
            --byte_control;
            break;
        case 3:
            --byte_control;
            break;
        case 4:
            byte_control = 1;
            break;
        default:
            if (bytes_to_ignore > 0)
            {
                --bytes_to_ignore;
            }
            else
            {
                list_unicodes.push_back(byte);
            }
        }
    }

    return list_unicodes;
}