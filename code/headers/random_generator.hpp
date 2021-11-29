/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

#include <time.h>

class random_generator
{
private:
    unsigned int seed_[10];
    unsigned int index_ = 0;
    void shuffle();

public:
    random_generator();
    random_generator(unsigned int *seed);
    void set_seed(unsigned int *seed);

    void generate_new_seed();
    int get_random_digit();
    float get_random_float(); // range 0.0f - 1.0f

    int get_integer(int min, int max); // get integer within range
    float get_float(float min, float max); // get float within range
};

#endif