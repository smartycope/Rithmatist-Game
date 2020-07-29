#pragma once

#include <GL/glew.h>

// #include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <SDL.h>
// #include <GLFW/glfw3.h>
#define GLEW_STATIC
// #include <GL/glew.h>

#include <iostream>
#include <string>
#include <cassert>

#include "Point.hpp"
#include "Line.hpp"
#include "Arena.hpp"
#include "Color.hpp"
#include "Globals.hpp"

// using std::vector;
namespace g{
extern unsigned int windowWidth, windowHeight;
}

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
    void run();
    void cleanup(GLuint vertexShader, GLuint fragmentShader);
    
public:
    unsigned int width, height;
    Point mouseLoc;

    // Gui() {}; // just for getting the window width and height 
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

    void printMouseLoc();
};