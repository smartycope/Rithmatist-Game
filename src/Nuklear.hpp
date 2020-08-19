#pragma once

#include "Gui.hpp"
#include "Point.hpp"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sdl_gl3.h"
// #include "../style.c"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024


class Nuklear: private Gui{ 
private:
    struct nk_context* ctx;
    // struct nk_font_atlas *atlas;

public:
    Nuklear(std::string title, unsigned int width, unsigned int height): Gui(title, width, height) { init(); };

    void init();
    void startInput();
    void handleEvent(SDL_Event& evt);
    void endInput();
    void draw();
    void render();
    void cleanup();
};