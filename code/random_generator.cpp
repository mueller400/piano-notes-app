/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "headers/random_generator.hpp"

random_generator::random_generator()
{
    generate_new_seed();
}

random_generator::random_generator(unsigned int *seed)
{
    for (unsigned int i = 0; i < 10; i++) {
        seed_[i] = seed[i];
    }
}

void random_generator::set_seed(unsigned int *seed){
    for (unsigned int i = 0; i < 10; i++) {
        seed_[i] = seed[i];
    }
}

void random_generator::generate_new_seed()
{
    time_t seconds = time(0);
    for (int i = 0; i < 10; ++i)
	{
		seed_[i] = seconds % 10; // modulo 10 of an integer type returns the last digit
		seconds = seconds / 10; // remove last digit
	}

    shuffle();
}

void random_generator::shuffle()
{
    for (int i = 0; i < 10; ++i)
	{
        int sum = 0;
        for (int j = 0; j < 10; ++j)
        {
            sum += seed_[j];
        }
        seed_[i] = sum % 10;
	}
}

int random_generator::get_random_digit()
{
    int sum = 0;
    for (int j = 0; j < 10; ++j)
    {
        sum += seed_[j];
    }
    unsigned int i = index_ % 10;
    seed_[i] = sum % 10;
    ++index_;

    return seed_[i];
}

float random_generator::get_random_float()
{
    return (float)(get_random_digit() * 0.1f + get_random_digit() * 0.01f + get_random_digit() * 0.001f +
                   get_random_digit() * 0.0001f + get_random_digit() * 0.00001f);
}

int random_generator::get_integer(int min, int max)
{
    return (int)((max - min) * get_random_float() + min);
}

float random_generator::get_float(float min, float max)
{
    return (max - min) * get_random_float() + min;
}

