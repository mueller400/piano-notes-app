/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef PROGRAM_STATE_HPP
#define PROGRAM_STATE_HPP

#include <vector>

struct pitch {
    bool is_used = false;
    int definition[7];

    pitch(){};
    pitch(int def1, int def2, int def3, int def4, int def5, int def6, int def7) {
            definition[0] = def1;   // a
            definition[1] = def2;   // b
            definition[2] = def3;   // c
            definition[3] = def4;   // d
            definition[4] = def5;   // e 
            definition[5] = def6;   // f
            definition[6] = def7;   // g
    }
    int operator[] (unsigned int i) {
        return definition[i];
    }
};

class program_state {
public:
    program_state() {
        // create chromatic pitches
        //                              a   b   c   d   e   f   g
        chromatic_pitches[0]  = pitch({ 0,  0,  0,  0,  0,  0,  0}); // c major
        chromatic_pitches[1]  = pitch({ 0,  0,  0,  0,  0,  1,  0}); // g major
        chromatic_pitches[2]  = pitch({ 0,  0,  1,  0,  0,  1,  0}); // d major
        chromatic_pitches[3]  = pitch({ 0,  0,  1,  0,  0,  1,  1}); // a major
        chromatic_pitches[4]  = pitch({ 0,  0,  1,  1,  0,  1,  1}); // e major
        chromatic_pitches[5]  = pitch({ 1,  0,  1,  1,  0,  1,  1}); // b major
        chromatic_pitches[6]  = pitch({-1, -1, -1, -1, -1, -1, -1}); // c flat major
        chromatic_pitches[7]  = pitch({ 1,  0,  1,  1,  1,  1,  1}); // f sharp major
        chromatic_pitches[8]  = pitch({-1, -1, -1, -1, -1,  0, -1}); // g flat major
        chromatic_pitches[9]  = pitch({-1, -1,  0, -1, -1,  0, -1}); // d flat major
        chromatic_pitches[10] = pitch({ 1,  1,  1,  1,  1,  1,  1}); // c sharp major
        chromatic_pitches[11] = pitch({-1, -1,  0, -1, -1,  0,  0}); // a flat major
        chromatic_pitches[12] = pitch({-1, -1,  0,  0, -1,  0,  0}); // e flat major
        chromatic_pitches[13] = pitch({ 0, -1,  0,  0, -1,  0,  0}); // b flat major
        chromatic_pitches[14] = pitch({ 0, -1,  0,  0,  0,  0,  0}); // f major

        // set c major as default
        chromatic_pitches[0].is_used = true;
        random_chromatic_pitches.push_back(0);

        // set no accidental as default
        accidentals[0] = true;
        random_accidentals.push_back(0);
    };

    void update_random_chromatic_pitches() {
        random_chromatic_pitches.clear();
        for (unsigned int i = 0; i < 15; i++) {
            if (chromatic_pitches[i].is_used) {
                random_chromatic_pitches.push_back(i);
            }
        }

        // if no chromatic pitch is selected set c major as default
        if (random_chromatic_pitches.size() == 0) {
            chromatic_pitches[0].is_used = true;
            random_chromatic_pitches.push_back(0);
        }
    };

    void update_random_accidentals() {
        random_accidentals.clear();
        for (unsigned int i = 0; i < 6; i++) {
            if (accidentals[i]) {
                random_accidentals.push_back(i);
            }
        }        
        // if no accidental is selected the none accidental as default
        if (random_accidentals.size() == 0) {
            accidentals[0] = true;
            random_accidentals.push_back(0);
        }
    }

    void update_violin_bass_options() {
        if (!show_violin_notes && !show_bass_notes) {
            show_violin_notes = true;
        }
    }

    bool close_application = false;
    bool new_event = false;
    int button_event = 0;
    bool show_options_menu = false;

    // options
    bool show_violin_notes = true;
    bool show_bass_notes = true;

    // chromatic pitches
    pitch chromatic_pitches[15];
    std::vector<unsigned int> random_chromatic_pitches;
    // 0:none, 1:sharp, 2:double sharp, 3:flat, 4:double flat, 5:natural
    bool accidentals[6] = {false, false, false, false, false, false};
    std::vector<int> random_accidentals;
};

#endif