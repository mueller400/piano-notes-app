/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/notes_display.hpp"

notes_display::notes_display() {

}

int notes_display::init(vec2<unsigned int> screen_resolution, sprite_manager* sprite_man, program_state* ps) {
    screen_resolution_ = screen_resolution;
    sprite_manager_ = sprite_man;
    program_state_ = ps;
    last_violin_note_ = violin_lower_bound_;
    last_bass_note_ = bass_lower_bound_;

    only_violin_notes_ = false;
    only_bass_notes_ = false;
    violin_upper_bound_ = 44;
    violin_lower_bound_ = 21;
    bass_upper_bound_ = 28;
    bass_lower_bound_ = 7;

    bool is_black_key[12] = {false, true, false, false, true, false, 
                             true, false, false, true, false, true};
    unsigned int counter = 0;
    for (int i = 0; i < 88; i++) {
        if (!is_black_key[i % 12]) {
            notes_[counter] = i + 1;
            counter++;
        }
    }

    // sheet music lines
    center_ = screen_resolution_.x / 2;
    height_ = 560;
    length_ = 600;
    line_pos_y_ = height_ + 130;
    line_width_ = 2;
    line_offset_ = 14;
    note_offset_ = line_offset_ / 2;
    note_violin_zero_pos_ = 600 - 14 * 1 + (note_offset_ * 6) - 1;
    note_bass_zero_pos_ = 600 - 14 * 1 - (note_offset_ * 16) - 1;
    sprite white_background = sprite_manager_->create_sprite(center_, height_ + 20, length_, 500, color<float>(0.95, 0.95, 0.95, 1.0),
                                                             "white.png");
    lines_.push_back(white_background);

    for (int i = 0; i < 5; i++) {
        lines_.push_back(sprite_manager_->create_sprite(center_, line_pos_y_ - line_offset_ * (i + 1), length_, line_width_, 
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "white.png"));
    }

    for (int i = 0; i < 5; i++) {
        lines_.push_back(sprite_manager_->create_sprite(center_, line_pos_y_ - line_offset_ * (i + 1 + 11), length_, line_width_, 
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "white.png"));
    }

    for (int i = 0; i < 5; i++) {
        ledger_lines_violin_upper_[4 - i] = sprite_manager_->create_sprite(center_, line_pos_y_ - line_offset_ * (i - 4), 
                                            30, line_width_, color<float>(0.05, 0.05, 0.05, 1.0), "white.png");
    }

    for (int i = 0; i < 2; i++) {
        ledger_lines_violin_lower_[i] = sprite_manager_->create_sprite(center_, line_pos_y_ - line_offset_ * (i + 6), 
                                            30, line_width_, color<float>(0.05, 0.05, 0.05, 1.0), "white.png");
    }

    for (int i = 0; i < 3; i++) {
        ledger_lines_bass_upper_[2 - i] = sprite_manager_->create_sprite(center_, line_pos_y_ - line_offset_ * (i + 9), 
                                            30, line_width_, color<float>(0.05, 0.05, 0.05, 1.0), "white.png");
    }

    for (int i = 0; i < 3; i++) {
        ledger_lines_bass_lower_[i] = sprite_manager_->create_sprite(center_, line_pos_y_ - line_offset_ * (i + 17), 
                                            30, line_width_, color<float>(0.05, 0.05, 0.05, 1.0), "white.png");
    }
    sprite clef = sprite_manager_->create_sprite(center_ - 270, line_pos_y_ - 45, 96, 96, 
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "clef.png");
    lines_.push_back(clef);

    sprite bass_clef = sprite_manager_->create_sprite(center_ - 270, line_pos_y_ - 50 - line_offset_ * 10, 96, 96,
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "bass_clef.png");
    lines_.push_back(bass_clef);

    // create 8va 8vb
    line_8va_ = sprite_manager_->create_sprite(center_, line_pos_y_ + 100, 256, 24,
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "8va.png");

    line_8vb_ = sprite_manager_->create_sprite(center_, line_pos_y_ - 300, 256, 31,
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "8vb.png");
    // create pitch symbols
    horizontal_offset_ = 15;

    create_pitch_symbols();

    // create displayed note
    note_head_ = sprite_manager_->create_sprite(center_, note_violin_zero_pos_, 20, 14,
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "note_head.png");
    note_stem_ = sprite_manager_->create_sprite(center_ + 9, note_violin_zero_pos_ + 20, 2, 38,
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "white.png");

    // create accidentals
    accidentals_[0] = sprite_manager_->create_sprite(center_ - 20, note_violin_zero_pos_, 46, 46,
                                                   color<float>(0.05, 0.05, 0.05, 0.0), "white.png");
    accidentals_[1] = sprite_manager_->create_sprite(center_ - 20, note_violin_zero_pos_, 48, 48,
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");
    accidentals_[2] = sprite_manager_->create_sprite(center_ - 20, note_violin_zero_pos_, 42, 42,
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "double_sharp.png");
    accidentals_[3] = sprite_manager_->create_sprite(center_ - 20, note_violin_zero_pos_, 46, 46,
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");
    accidentals_[4] = sprite_manager_->create_sprite(center_ - 20, note_violin_zero_pos_, 46, 46,
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "double_flat.png");
    accidentals_[5] = sprite_manager_->create_sprite(center_ - 20, note_violin_zero_pos_, 48, 48,
                                                   color<float>(0.05, 0.05, 0.05, 1.0), "natural.png");
    
    // correct some accidental positions slightly 
    accidental_position_corrections_[0] = {0, 0};
    accidental_position_corrections_[1] = {0, 0};
    accidental_position_corrections_[2] = {-5, 0};
    accidental_position_corrections_[3] = {0, note_offset_};
    accidental_position_corrections_[4] = {-5, note_offset_};
    accidental_position_corrections_[5] = {0, 0};

    // bounds notes to display in the options menu
    note_viol_upper_head_ = sprite_manager_->create_sprite(center_, note_violin_zero_pos_, 20, 14,
                                                   color<float>(0.5, 0.0, 0.0, 0.5), "note_head.png");
    note_viol_upper_stem_ = sprite_manager_->create_sprite(center_ + 9, note_violin_zero_pos_ + 20, 2, 38,
                                                   color<float>(0.5, 0.0, 0.0, 0.5), "white.png");
    note_viol_lower_head_ = sprite_manager_->create_sprite(center_, note_violin_zero_pos_, 20, 14,
                                                   color<float>(0.0, 0.5, 0.0, 0.5), "note_head.png");
    note_viol_lower_stem_ = sprite_manager_->create_sprite(center_ + 9, note_violin_zero_pos_ + 20, 2, 38,
                                                   color<float>(0.0, 0.5, 0.0, 0.5), "white.png");
    note_bass_upper_head_ = sprite_manager_->create_sprite(center_, note_violin_zero_pos_, 20, 14,
                                                   color<float>(0.5, 0.0, 0.0, 0.5), "note_head.png");
    note_bass_upper_stem_ = sprite_manager_->create_sprite(center_ + 9, note_violin_zero_pos_ + 20, 2, 38,
                                                   color<float>(0.5, 0.0, 0.0, 0.5), "white.png");
    note_bass_lower_head_ = sprite_manager_->create_sprite(center_, note_violin_zero_pos_, 20, 14,
                                                   color<float>(0.0, 0.5, 0.0, 0.5), "note_head.png");
    note_bass_lower_stem_ = sprite_manager_->create_sprite(center_ + 9, note_violin_zero_pos_ + 20, 2, 38,
                                                   color<float>(0.0, 0.5, 0.0, 0.5), "white.png");

    return next_random_note();
}

void notes_display::show_note_bounds() {
    if (violin_upper_bound_ > 44) {
        is_8va = true;
    }

    if (bass_lower_bound_ < 7) {
        is_8vb = true;
    }
    move_note_bound(0, 0);
    move_note_bound(1, 0);
    move_note_bound(2, 0);
    move_note_bound(3, 0);

    show_notes_bounds_ = true;
}

void notes_display::hide_note_bounds() {
    last_violin_note_ = violin_lower_bound_;
    last_bass_note_ = bass_lower_bound_;
    show_notes_bounds_ = false;
}

void notes_display::move_note_bound(char bound, int offset) {
    
    int add_offset = 0;
    switch (bound) {
        case 0:
            if (violin_upper_bound_ + offset >= violin_lower_bound_ + 2 &&
                violin_upper_bound_ + offset <= violin_upper_bound_max_) {
                violin_upper_bound_ += offset;
                
                if (violin_upper_bound_ > 44) {
                    is_8va = true;
                    add_offset = -7;
                } else {
                    is_8va = false;
                }
                update_note_position(note_viol_upper_head_, note_viol_upper_stem_, NOTE_ATTRIBUTE::VIOLIN_NOTE, violin_upper_bound_ - 27 + add_offset, 5);
            }
            break;
        case 1:
            if (violin_lower_bound_ + offset >= violin_lower_bound_min_ &&
                violin_lower_bound_ + offset <= violin_upper_bound_ - 2) {
                violin_lower_bound_ += offset;
                if (violin_lower_bound_ > 44) {
                    add_offset = -7;
                }
                update_note_position(note_viol_lower_head_, note_viol_lower_stem_, NOTE_ATTRIBUTE::VIOLIN_NOTE, violin_lower_bound_ - 27 + add_offset, 5);
            }
            break;
        case 2:
            if (bass_upper_bound_ + offset >= bass_lower_bound_ + 2 &&
                bass_upper_bound_ + offset <= bass_upper_bound_max_) {
                bass_upper_bound_ += offset;
                if (bass_upper_bound_ < 7) {
                    add_offset = 7; 
                }
                update_note_position(note_bass_upper_head_, note_bass_upper_stem_, NOTE_ATTRIBUTE::BASS_NOTE, bass_upper_bound_ - 15 + add_offset, 5);
            }
            break;
        case 3:
            if (bass_lower_bound_ + offset >= bass_lower_bound_min_ &&
                bass_lower_bound_ + offset <= bass_upper_bound_ - 2) {
                bass_lower_bound_ += offset;
                if (bass_lower_bound_ < 7) {
                    is_8vb = true; 
                    add_offset = 7;
                } else {
                    is_8vb = false;
                }
                update_note_position(note_bass_lower_head_, note_bass_lower_stem_, NOTE_ATTRIBUTE::BASS_NOTE, bass_lower_bound_ - 15 + add_offset, 5);
            }
            break;
        default:
            break;
    }
    draw_ledger_lines_ = 5;
}

void notes_display::draw() {
    // draw lines
    std::vector<sprite>::iterator it;
    for (it = lines_.begin(); it != lines_.end(); ++it) {
        sprite_manager_->draw(*it);
    }

    switch (draw_ledger_lines_)
    {
    case 1:
        for (int i = 0; i < number_ledger_lines_; i++) {
            sprite_manager_->draw(ledger_lines_violin_upper_[i]);
        }
        break;
    case 2:
        for (int i = 0; i < number_ledger_lines_; i++) {
            sprite_manager_->draw(ledger_lines_violin_lower_[i]);
        }
        break;
    case 3:
        for (int i = 0; i < number_ledger_lines_; i++) {
            sprite_manager_->draw(ledger_lines_bass_upper_[i]);
        }
        break;
    case 4:
        for (int i = 0; i < number_ledger_lines_; i++) {
            sprite_manager_->draw(ledger_lines_bass_lower_[i]);
        }
        break;
    case 5: // draw all ledger lines
        for (int i = 0; i < 5; i++) {
            sprite_manager_->draw(ledger_lines_violin_upper_[i]);
        }
        for (int i = 0; i < 2; i++) {
            sprite_manager_->draw(ledger_lines_violin_lower_[i]);
        }
        for (int i = 0; i < 3; i++) {
            sprite_manager_->draw(ledger_lines_bass_upper_[i]);
        }
        for (int i = 0; i < 3; i++) {
            sprite_manager_->draw(ledger_lines_bass_lower_[i]);
        }
        break;
    default:
        break;
    }

    if (is_8va) {
        sprite_manager_->draw(line_8va_);
    }

    if (is_8vb) {
        sprite_manager_->draw(line_8vb_);
    }

    if (!show_notes_bounds_) {

        // draw chromatic pitch
        for (int i = 0; i < 7; i++) {
            if (program_state_->chromatic_pitches[current_pitch_][i] == 1) {
                sprite_manager_->draw(pitch_sharp_symbols_[i]); // violin
                sprite_manager_->draw(pitch_sharp_symbols_[i + 7]); // bass
            } else if (program_state_->chromatic_pitches[current_pitch_][i] == -1) {
                sprite_manager_->draw(pitch_flat_symbols_[i]); // violin
                sprite_manager_->draw(pitch_flat_symbols_[i + 7]); // bass
            }
        }

        // draw note
        sprite_manager_->draw(note_head_);
        sprite_manager_->draw(note_stem_);
    
        // draw accidental
        sprite_manager_->draw(accidentals_[current_accidental_]);
    } else {
        sprite_manager_->draw(note_viol_upper_head_);
        sprite_manager_->draw(note_viol_upper_stem_);
        sprite_manager_->draw(note_viol_lower_head_);
        sprite_manager_->draw(note_viol_lower_stem_);
        sprite_manager_->draw(note_bass_upper_head_);
        sprite_manager_->draw(note_bass_upper_stem_);
        sprite_manager_->draw(note_bass_lower_head_);
        sprite_manager_->draw(note_bass_lower_stem_);
    }
}

int notes_display::next_random_note() {
    int add_offset = 0;
    int pitch_offset = 0;
    current_accidental_ = 0;
    is_8va = false;
    is_8vb = false;
    // get random chromatic pitch
    unsigned int index = rnd_.get_integer(0, program_state_->random_chromatic_pitches.size());
    current_pitch_ = program_state_->random_chromatic_pitches[index];

    // get random violin or bass
    float is_violin_note = rnd_.get_random_float();

    if (!program_state_->show_bass_notes) {
        is_violin_note = 1.0;
    } else if (!program_state_->show_violin_notes) {
        is_violin_note = 0.0;
    }

    // get random note
    if (is_violin_note > 0.5) {
        int range = violin_upper_bound_ - violin_lower_bound_ + 1;
        current_note_ = (last_violin_note_ - violin_lower_bound_ + rnd_.get_integer(1, range)) % (range) + violin_lower_bound_;
        if (current_note_ > 44) {
            is_8va = true;
            add_offset = -7;
        }
        last_violin_note_ = current_note_;

        // get the offset due to the chromatic pitch for this note
        pitch_offset = program_state_->chromatic_pitches[current_pitch_][(current_note_ - 1) % 7];

        // get random accidental
        if (pitch_offset == 0 && program_state_->accidentals[5] && program_state_->random_accidentals.size() > 1) {
            // choose accidental without natural accidental
            index = rnd_.get_integer(0, program_state_->random_accidentals.size() - 1);
            current_accidental_ = program_state_->random_accidentals[index];
        } else if (pitch_offset == 0 && program_state_->accidentals[5]) {
            current_accidental_ = 0;
        } else {
            index = rnd_.get_integer(0, program_state_->random_accidentals.size());
            current_accidental_ = program_state_->random_accidentals[index];
        }

        update_note_position(note_head_, note_stem_, NOTE_ATTRIBUTE::VIOLIN_NOTE, current_note_ - 27 + add_offset, current_accidental_);
    }
    else {
        int range = bass_upper_bound_ - bass_lower_bound_ + 1;
        current_note_ = (last_bass_note_ - bass_lower_bound_ + rnd_.get_integer(1, range)) % (range) + bass_lower_bound_;
        if (current_note_ < 7) {
            is_8vb = true;
            add_offset = 7;
        }
        last_bass_note_ = current_note_;

        // get the offset due to the chromatic pitch for this note
        pitch_offset = program_state_->chromatic_pitches[current_pitch_][(current_note_ - 1) % 7];

        // get random accidental
        if (pitch_offset == 0 && program_state_->accidentals[5] && program_state_->random_accidentals.size() > 1) {
            // choose accidental without natural accidental
            index = rnd_.get_integer(0, program_state_->random_accidentals.size() - 1);
            current_accidental_ = program_state_->random_accidentals[index];
        } else if (pitch_offset == 0 && program_state_->accidentals[5]) {
            current_accidental_ = 0;
        } else {
            index = rnd_.get_integer(0, program_state_->random_accidentals.size());
            current_accidental_ = program_state_->random_accidentals[index];
        }

        update_note_position(note_head_, note_stem_, NOTE_ATTRIBUTE::BASS_NOTE, current_note_ - 15 + add_offset, current_accidental_);
    }

    // natural accidental overrides the chromatic pitch offset
    if (current_accidental_ == 5) {
        pitch_offset = 0;
    }

    int note = notes_[current_note_ - 1] + pitch_offset + accidental_offsets_[current_accidental_];

    // catch border values
    if (note < 1) {
        note = 1;
    } else if (note > 88) {
        note = 88;
    }
    return note;
}

void notes_display::update_note_stem(sprite &note_stem, int note_zero_pos, NOTE_ATTRIBUTE direction, int offset, int length_addition) {

    if (direction == NOTE_ATTRIBUTE::STEM_UP) {
        note_stem.size = length_pixel_to_gl(vec2<int>(2, 38 + note_offset_ * length_addition), 
                                             screen_resolution_);
        note_stem.pos = coord_pixel_to_gl(vec2<int>(center_ + 9, note_zero_pos + note_offset_ * offset + 20 +
                                           note_offset_ * length_addition / 2), screen_resolution_);
    }
    else {
        note_stem.size = length_pixel_to_gl(vec2<int>(2, 38 + note_offset_ * length_addition), screen_resolution_);
        note_stem.pos = coord_pixel_to_gl(vec2<int>(center_ - 9, note_zero_pos + note_offset_ * offset - 20 - 
                                           note_offset_ * length_addition / 2), screen_resolution_);
    }
}

void notes_display::update_note_position(sprite &note_head, sprite &note_stem, NOTE_ATTRIBUTE note_type, int offset, unsigned int accidental) {
    draw_ledger_lines_ = 0;
    int additional_stem_length = 0;

    if (note_type == NOTE_ATTRIBUTE::VIOLIN_NOTE) {
        note_head.pos = coord_pixel_to_gl(vec2<int>(center_, note_violin_zero_pos_ + note_offset_ * offset),
                                          screen_resolution_);
        // set accidental
        accidentals_[accidental].pos = coord_pixel_to_gl(add_vec2(vec2<int>(center_ - 20, note_violin_zero_pos_ + note_offset_ * offset), 
                                                         accidental_position_corrections_[accidental]),
                                                         screen_resolution_);

        if (offset > 2) {

            // ledger lines
            if (offset > 8 && offset < 19) {
                int i = (offset - 8) + offset % 2;
                number_ledger_lines_ = i / 2;
                draw_ledger_lines_ = 1;
            }
            // note stem
            if (offset > 12) {
                additional_stem_length = offset - 12;
            }
            update_note_stem(note_stem, note_violin_zero_pos_, NOTE_ATTRIBUTE::STEM_DOWN, offset, additional_stem_length);
        }
        else {

            // ledger lines
            if (offset < -2 && offset > -7) {
                int i = (offset + 1) + offset % 2;
                number_ledger_lines_ = i / 2 * -1;
                draw_ledger_lines_ = 2;
            }
            // note stem
            update_note_stem(note_stem, note_violin_zero_pos_, NOTE_ATTRIBUTE::STEM_UP, offset, additional_stem_length);
        }


    }
    else if (note_type == NOTE_ATTRIBUTE::BASS_NOTE) {
        note_head.pos = coord_pixel_to_gl(vec2<int>(center_, note_bass_zero_pos_ + note_offset_ * offset),
                                           screen_resolution_);

        // set accidental
        accidentals_[accidental].pos = coord_pixel_to_gl(add_vec2(vec2<int>(center_ - 20, note_bass_zero_pos_ + note_offset_ * offset),
                                                         accidental_position_corrections_[accidental]),
                                                         screen_resolution_);

        if (offset > 2) {

            // ledger lines
            if (offset > 8 && offset < 14) {
                int i = (offset - 8) + offset % 2;
                number_ledger_lines_ = i / 2;
                draw_ledger_lines_ = 3;
            }
            // note stem
            if (offset > 12) {
                additional_stem_length = offset - 12;
            }
            update_note_stem(note_stem, note_bass_zero_pos_, NOTE_ATTRIBUTE::STEM_DOWN, offset, additional_stem_length);
        }
        else {

            // ledger lines
            if (offset < -2 && offset > -9) {
                int i = (offset + 1) + offset % 2;
                number_ledger_lines_ = i / 2 * -1;
                draw_ledger_lines_ = 4;
            }
            // note stem
            if (offset < -5) {
                additional_stem_length = offset * -1 - 6;
            }
            update_note_stem(note_stem, note_bass_zero_pos_, NOTE_ATTRIBUTE::STEM_UP, offset, additional_stem_length);
        }
    }
}

void notes_display::create_pitch_symbols() {
    int bass_offset = line_offset_ * 11 + note_offset_ * 2;

    // violin sharp symbols
    pitch_sharp_symbols_[5] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 0,
                                                             line_pos_y_ - note_offset_ * 2 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");

    pitch_sharp_symbols_[2] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 1,
                                                             line_pos_y_ - note_offset_ * 5 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");

    pitch_sharp_symbols_[6] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 2,
                                                             line_pos_y_ - note_offset_ * 1 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");

    pitch_sharp_symbols_[3] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 3,
                                                             line_pos_y_ - note_offset_ * 4 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");

    pitch_sharp_symbols_[0] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 4,
                                                             line_pos_y_ - note_offset_ * 7 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");                                                   

    pitch_sharp_symbols_[4] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 5,
                                                             line_pos_y_ - note_offset_ * 3 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");

    pitch_sharp_symbols_[1] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 6,
                                                             line_pos_y_ - note_offset_ * 6 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");
    // bass sharp symbols
    pitch_sharp_symbols_[12] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 0,
                                                             line_pos_y_ - bass_offset - note_offset_ * 2 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");

    pitch_sharp_symbols_[9] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 1,
                                                             line_pos_y_ - bass_offset - note_offset_ * 5 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");

    pitch_sharp_symbols_[13] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 2,
                                                             line_pos_y_ - bass_offset - note_offset_ * 1 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");

    pitch_sharp_symbols_[10] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 3,
                                                             line_pos_y_ - bass_offset - note_offset_ * 4 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");

    pitch_sharp_symbols_[7] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 4,
                                                             line_pos_y_ - bass_offset - note_offset_ * 7 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");                                                   

    pitch_sharp_symbols_[11] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 5,
                                                             line_pos_y_ - bass_offset - note_offset_ * 3 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");

    pitch_sharp_symbols_[8] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 6,
                                                             line_pos_y_ - bass_offset - note_offset_ * 6 + 2, 48, 48,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "sharp.png");

    // violin flat symbols
    pitch_flat_symbols_[0] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 2,
                                                             line_pos_y_ - note_offset_ * 6 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");

    pitch_flat_symbols_[1] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 0,
                                                             line_pos_y_ - note_offset_ * 5 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");

    pitch_flat_symbols_[2] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 5,
                                                             line_pos_y_ - note_offset_ * 4 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");

    pitch_flat_symbols_[3] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 3,
                                                             line_pos_y_ - note_offset_ * 3 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");

    pitch_flat_symbols_[4] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 1,
                                                             line_pos_y_ - note_offset_ * 2 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");                                                   

    pitch_flat_symbols_[5] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 6,
                                                             line_pos_y_ - note_offset_ * 8 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");

    pitch_flat_symbols_[6] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 4,
                                                             line_pos_y_ - note_offset_ * 7 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");
    // bass flat symbols
    pitch_flat_symbols_[7] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 2,
                                                             line_pos_y_ - bass_offset - note_offset_ * 6 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");

    pitch_flat_symbols_[8] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 0,
                                                             line_pos_y_ - bass_offset - note_offset_ * 5 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");

    pitch_flat_symbols_[9] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 5,
                                                             line_pos_y_ - bass_offset - note_offset_ * 4 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");

    pitch_flat_symbols_[10] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 3,
                                                             line_pos_y_ - bass_offset - note_offset_ * 3 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");

    pitch_flat_symbols_[11] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 1,
                                                             line_pos_y_ - bass_offset - note_offset_ * 2 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");                                                   

    pitch_flat_symbols_[12] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 6,
                                                             line_pos_y_ - bass_offset - note_offset_ * 8 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");

    pitch_flat_symbols_[13] = sprite_manager_->create_sprite(center_ - 235 + horizontal_offset_ * 4,
                                                             line_pos_y_ - bass_offset - note_offset_ * 7 + 2, 46, 46,
                                                             color<float>(0.05, 0.05, 0.05, 1.0), "flat.png");
}