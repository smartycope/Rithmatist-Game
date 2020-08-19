#pragma once

#include <GL/glew.h>

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#define GLEW_STATIC

#include "Arena.hpp"
#include "Globals.hpp"

// Nuklear includes
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"
// #include "nuklear_sdl_gl3.h"
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

#define MAX_FPS 60
#define USE_VSYNC 0

namespace g{ extern unsigned int windowWidth, windowHeight; }

class Gui{
private:
    Arena arena;
    Color drawColor;
    GLint colorLoc;

    //std::vector<int> indecies;
    Point windowPosition;
    SDL_Window* window;
    SDL_GLContext context;
    GLuint vao;
    GLuint shaderProgram;
    struct nk_context* ctx;
    // struct nk_font_atlas *atlas;

    void init(std::string title);
    void setSDL_GLAttributes();
    void initLines();
    void createLines();
    void updateLines();
    void initGLEW();
    void initSDL(std::string title);
    void createVAO();
    GLuint createVertexShader();
    GLuint createFragmentShader();
    void compileShaders(GLuint vertex, GLuint fragment);
    void arrangeLines();
    void addManualLines(Player player);
    void run();
    void draw(bool points = false);
    void drawNuklear();
    void cleanup(GLuint vertexShader, GLuint fragmentShader);
    void updateMouse(int x, int y);
    
public:
    unsigned int width, height;
    Point mouseLoc;

    Gui(std::string title, unsigned int width, unsigned int height):
        width(width),
        height(height),
        windowPosition(Point(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED))
        { init(title); };
    Gui(std::string title, unsigned int width, unsigned int height, Point position):     
        width(width), 
        height(height), 
        windowPosition(position)                                              
        { init(title); };
    Gui(std::string title, unsigned int width, unsigned int height, int xPos, int yPos): 
        width(width), 
        height(height), 
        windowPosition(Point(xPos, yPos))                                     
        { init(title); };
    ~Gui();

    void printMouseLoc();
};