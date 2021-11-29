/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#ifndef UNITS_HPP
#define UNITS_HPP

#include <iostream>
template<typename T>
struct vec2
{
    T x;
    T y;

    vec2() {}

    vec2(T a, T b)
    {
        x = a;
        y = b;
    }
};

template<typename T>
struct vec3
{
    T x;
    T y;
    T z;

    vec3() {}

    vec3(T a, T b, T c)
    {
        x = a;
        y = b;
        z = c;
    }
};

template<typename T>
struct vec4{
    T x;
    T y;
    T z;
    T w;

    vec4() {}

    vec4(T a, T b, T c, T d)
    {
        x = a;
        y = b;
        z = c;
        w = d;
    }
};

template<typename T>
struct color{
    T r;
    T g;
    T b;
    T a;

    color() {}

    color(T x, T y, T z, T w)
    {
        r = x;
        g = y;
        b = z;
        a = w;
    }
};

// coordinate transform functions

static vec2<int> coord_gl_to_pixel(vec2<float> pos, vec2<unsigned int> screen)
{
    return vec2<int>{(int)((pos.x + 1.0f) / 2.0f * screen.x), (int)((pos.y + 1.0f) / 2.0f * screen.y)};
}

static vec2<float> coord_pixel_to_gl(vec2<int> pos, vec2<unsigned int> screen)
{
    return vec2<float>{(float)pos.x / (float)screen.x * 2.0f - 1.0f, (float)pos.y / (float)screen.y * 2.0f - 1.0f};
}

static vec2<double> coord_pixel_to_gl(vec2<double> pos, vec2<unsigned int> screen)
{
    return vec2<double>{pos.x / (float)screen.x * 2.0f - 1.0f, pos.y / (float)screen.y * 2.0f - 1.0f};
}

static vec2<float> length_pixel_to_gl(vec2<float> pos, vec2<unsigned int> screen)
{
    return vec2<float>(2.0f / (float)screen.x * pos.x, 2.0f / (float)screen.y * pos.y);
}

static vec2<float> length_pixel_to_gl(vec2<int> pos, vec2<unsigned int> screen)
{
    return vec2<float>(2.0f / (float)screen.x * (float)pos.x, 2.0f / (float)screen.y * (float)pos.y);
}

static vec2<float> length_gl_to_pixel(vec2<float> pos, vec2<unsigned int> screen)
{
    return vec2<float>(pos.x / (2.0f / (float)screen.x), pos.y / (2.0f / (float)screen.y));
}

// static vec2<int> length_gl_to_pixel(vec2<float> pos, vec2<unsigned int> screen)
// {
//     return vec2<int>(pos.x / (2.0f / (float)screen.x), pos.y / (2.0f / (float)screen.y));
// }

static float horizontal_length_px_to_gl(int length_px, unsigned int screen_width)
{
    return 2.0f / (float)screen_width * (float)length_px;
}

static int gl_to_px(float length_gl, unsigned int screen_length)
{
    return (int)(length_gl / (2.0f / (float)screen_length));
}

static float vertical_length_px_to_gl(int length_px, unsigned int screen_height)
{
    return 2.0f / (float)screen_height * (float)length_px;
}

template<typename T>
vec2<T> add_vec2(vec2<T> v1, vec2<T> v2)
{
    return vec2<T>(v1.x + v2.x, v1.y + v2.y);
}

template<typename T>
vec2<T> sub_vec2(vec2<T> v1, vec2<T> v2)
{
    return vec2<T>(v1.x - v2.x, v1.y - v2.y);
}

#endif