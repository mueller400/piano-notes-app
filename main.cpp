/*
 * Copyright (c) 20021-2021 Erik Mueller (erikmueller400 at gmx dot de)
 */

#include "code/headers/gl_context.hpp"

int main(int argc, const char* argv[])
{
    gl_context context(1920, 900);
    context.framerate = 20;
    int status = context.init();
    return status;
}