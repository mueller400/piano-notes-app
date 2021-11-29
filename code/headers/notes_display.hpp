/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef NOTES_DISPLAY_HPP
#define NOTES_DISPLAY_HPP

#include "sprites.hpp"
#include "random_generator.hpp"
#include "iostream"
#include <vector>
#include "../gui/headers/program_state.hpp"

enum class NOTE_ATTRIBUTE {
    STEM_UP,
    STEM_DOWN,
    VIOLIN_NOTE,
    BASS_NOTE
};

class notes_display {
public:
    notes_display();
    int init(vec2<unsigned int> screen_resolution, sprite_manager* sprite_man, program_state* ps);
    void draw();
    int next_random_note();
    void show_note_bounds();
    void hide_note_bounds();
    void move_note_bound(char bound, int offset); // bound(1:violin_upper,2:violin_lower,3:bass_upper,4:bass_lower)

private:
    program_state* program_state_;
    vec2<unsigned int> screen_resolution_;
    int center_;
    int height_;
    int length_;
    int line_pos_y_;
    int line_width_;
    int line_offset_;
    int note_offset_;
    int horizontal_offset_ = 15;
    int note_violin_zero_pos_;
    int note_bass_zero_pos_;
    int last_violin_note_ = 27;
    int last_bass_note_ = 15;
    bool only_violin_notes_ = false;
    bool only_bass_notes_ = false;
    sprite_manager * sprite_manager_;
    std::vector<sprite> lines_;
    unsigned short int draw_ledger_lines_ = 0; // 0: none, 1:upper_violin, 2:lower_violin, 3:upper_bass, 4:lower_bass
    unsigned short int number_ledger_lines_ = 0;

    sprite ledger_lines_violin_upper_[5];
    sprite ledger_lines_violin_lower_[2];
    sprite ledger_lines_bass_upper_[3];
    sprite ledger_lines_bass_lower_[3];

    sprite line_8va_;
    sprite line_8vb_;

    sprite note_head_;
    sprite note_stem_;

    sprite note_viol_upper_head_;
    sprite note_viol_upper_stem_;
    sprite note_viol_lower_head_;
    sprite note_viol_lower_stem_;
    sprite note_bass_upper_head_;
    sprite note_bass_upper_stem_;
    sprite note_bass_lower_head_;
    sprite note_bass_lower_stem_;

    sprite pitch_sharp_symbols_[14];
    sprite pitch_flat_symbols_[14];

    sprite accidentals_[6];
    unsigned int current_accidental_ = 0;
    int accidental_offsets_[6] = {0, 1, 2, -1, -2, 0};
    vec2<int> accidental_position_corrections_[6];

    random_generator rnd_;
    unsigned int current_note_ = 0;
    unsigned int current_pitch_ = 0;

    int notes_[52];
    int violin_upper_bound_ = 44;
    int violin_lower_bound_ = 21;
    int bass_upper_bound_ = 28;
    int bass_lower_bound_ = 7;

    int violin_upper_bound_max_ = 52;
    int violin_lower_bound_min_ = 21;
    int bass_upper_bound_max_ = 28;
    int bass_lower_bound_min_ = 1;

    bool is_8va = false;
    bool is_8vb = false;
    bool show_notes_bounds_ = false;

    void update_note_stem(sprite &note_stem, int note_zero_position, NOTE_ATTRIBUTE direction,
                          int offset, int length_addition);
    // the last parameter is the accidental (0:none, 1:sharp, 2:double sharp, 3:flat, 4:double flat, 5:natural)
    void update_note_position(sprite &note_head, sprite &note_stem, NOTE_ATTRIBUTE note_type, 
                              int offset, unsigned int accidental);
    void create_pitch_symbols();
};

#endif