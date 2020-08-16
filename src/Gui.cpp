#include "Gui.hpp"
#include "Arena.hpp"
#include "Geometry.hpp"
#include "Globals.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <string>
#include <vector>

// this line is intelligent
#define GLSL(src) "#version 330 core\n" #src 

#define addLine(player, where)         \
    Line newLine(where);               \
    (*arena.players)[player].lines->push_back(newLine);

// #define finishLine(player, where, data) \
//     (*arena.players)[player].lines->back().finish(where, data);

#define finishLine(player, where, identify) \
    (*arena.players)[player].lines->back().finish(where, identify);

#define addData(player, where) \
    (*arena.players)[player].lines->back().append(where);

#define USER ((*arena.players)["user"])
    

void Gui::printMouseLoc(){
    std::cout << "Mouse is at ";
    mouseLoc.print();
    std::cout << std::endl;
}

void Gui::setSDL_GLAttributes(){
    // tell openGL I want a forward compatible context of my version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    // Setup SDL for OpenGL
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
    // SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, “1”);
}

void Gui::initGLEW(){
    //-----------------------------------------GLEW----------------------------------------//
    g::log("Setting up GLEW...");

    // GLEW -- enables specific features of certain graphics cards (not strictly necissary)
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        exit(1);
    }

    // GLuint vertexBuffer;
    // glGenBuffers(1, &vertexBuffer);

    // printf("%u\n", vertexBuffer);

    // std::cout << glGenBuffers << std::endl;

    g::log("Successfully set up GLEW.");
}

void Gui::initLines(){
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Gui::createLines(){
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arena.vertices->size(), arena.vertices->data(), GL_DYNAMIC_DRAW);
}

void Gui::updateLines(){
    arena.update();
}

void Gui::initSDL(std::string title){
    g::log("Initializing SDL...");

    // initalize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING))
        std::cerr << "Can't initialize SDL2" << std::endl;

    setSDL_GLAttributes();

    // make the SDL window
    window = SDL_CreateWindow(title.c_str(), windowPosition.x, windowPosition.y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
     /* other options here:
        in place of x and y: SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED
        in place of SDL_WINDOW_OPENGL: SDL_WINDOW_RESIZABLE, SDL_WINDOW_FULLSCREEN (optional)
     */
    // check that it worked 
    if (!window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    g::log("Creating OpenGL context...", 5);
    // Create the OpenGL context (finally)
    context = SDL_GL_CreateContext(window);
    // SDL_GL_MakeCurrent(window, context);
    
}

void Gui::createVAO(){
    g::log("Creating VAO...", 5);
    // Create Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

GLuint Gui::createVertexShader(){
    g::log("Creating vertex shader...", 5);
    // Create and compile the vertex shader
    const char* vertexSource = GLSL(
        in vec2 position;
        in vec4 color;
        out vec4 Color;
        
        void main() {
            Color = color;
            gl_Position = vec4(position, 0.0, 1.0);
        }
    );
    
    g::log("compiling vertex shader...", 5);
    // compile it
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // check if that actually worked
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status){
        char buffer[1024];
        glGetShaderInfoLog(vertexShader, 1024, NULL, buffer);
        std::cerr << buffer << std::endl;
    }
    return vertexShader;
}

GLuint Gui::createFragmentShader(){
    g::log("Creating fragment shader...", 5);
    // Create and compile the fragment shader
    const char* fragmentSource = GLSL(
        uniform vec4 drawColor;
        out vec4 outColor;
        in vec4 Color;
        
        void main() {
            // outColor = drawColor;
            outColor = Color;
        }
    );

    g::log("Compiling fragment shader...", 5);
    // compile it
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // now check if it worked
    /*
    glGetFragmentiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status){
        char buffer[1024];
        glGetShaderInfoLog(fragmentShader, 1024, NULL, buffer);
        std::cerr << buffer << std::endl;
    }
    */
    return fragmentShader;
}

void Gui::compileShaders(GLuint vertex, GLuint fragment){
    g::log("Linking shaders...", 5);
    // Link the vertex and fragment shader into a shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glBindFragDataLocation(shaderProgram, 0, "outColor"); // specifies which framebuffer to use
    glLinkProgram(shaderProgram);                         //  (right now there's only one)
    glUseProgram(shaderProgram);
}

void Gui::arrangeLines(){
    // specify how the data is organized within the array you just made

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);//      normalize
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    // glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);//      normalize
    glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
    //                                                          stride                 offset
}

void Gui::updateMouse(int x, int y){
    mouseLoc.x = x;
    mouseLoc.y = y;
}
/* Draw everything in the vector of things we need to draw
void Gui::draw(bool points){
    // Returns a vector of tuples
    auto arr = arena.getArrangement();
    
    for (auto itP: arr)
        if(std::get<0>(itP).data() and std::get<1>(itP).data())
            //                type                     offset                   count                    num primitives
            glMultiDrawArrays(points ? GL_POINTS : GL_LINE_STRIP_ADJACENCY, std::get<0>(itP).data(), std::get<1>(itP).data(), std::get<2>(itP));
}
*/
void Gui::draw(bool points){
    std::vector<GLint>   offsets;
    std::vector<GLsizei> lengths;
    int playerSpecificOffset = 0;
    int count  = 0;
    int offset = 0;

    // Iterate through all the players
    for (auto p: *arena.players){
        // Iterate through all that players lines'
        for (auto i: *(p.second.lines)){
            assert(offsets.size() == lengths.size());
            if (not i.isNull()){
                lengths.push_back(i.getDataLen());
                offsets.push_back(offset);
                ++count;
            }
            // Add an extra offset if the line is erased
            offset += i.getDataLen();
        }
    }
    //                                     type                     offset          count           num primitives
    glMultiDrawArrays(points ? GL_POINTS : GL_LINE_STRIP_ADJACENCY, offsets.data(), lengths.data(), count);
}

void Gui::addManualLines(Player player){
    Geometry geo;

    Point center(243, 150);
    Point randEnd(125, 185);
    auto data = geo.genOptLine(center, randEnd);
    logVal(data.size())
    Line optStraight(center, randEnd, data);

    player.lines->push_back(optStraight);

    updateLines();
    createLines();
    // delete lineData;
}

void Gui::run(){
    g::log("Starting window proper...");

    SDL_Event event;
    bool fullscreen = false, run = true, trackMouse = false, identify = true;
    bool shift = false, ctrl = false, alt = false;
    Uint32 windowFlags = 0; // fudge variable
    unsigned int previousTime, currentTime, lastOutput = 0;
    (*arena.players)["root"] = Player("root");
    
    addManualLines((*arena.players)["root"]);

    while (run){
        // Update the mouse location - now done as needed
        // SDL_GetMouseState(&mouseLoc.x, &mouseLoc.y);

        // The event loop
        while (SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    run = false; break;
                case SDL_KEYDOWN:
                    // logVal(SDL_GetScancodeName(event.key.keysym.scancode)) // physical key
                    // logVal(SDL_GetKeyName(event.key.keysym.sym))           // simulated key 
                    switch (event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            run = false; break;

                        case 'f':
                            fullscreen = !fullscreen;
                            if (fullscreen)
                                SDL_SetWindowFullscreen(window, windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                            else
                                SDL_SetWindowFullscreen(window, windowFlags);
                            break;
                        case 'c':
                            arena.clear();
                            trackMouse = false;
                            break;
                        case SDLK_RCTRL:
                        case SDLK_LCTRL:
                            ctrl = true;
                            break;
                        case SDLK_LSHIFT:
                        case SDLK_RSHIFT:
                            shift = true;
                            break;
                        case SDLK_RALT:
                        case SDLK_LALT:
                            alt = true;
                            break;
                        case 'z':
                            if(ctrl){
                                _log("Ctrl + z pressed");
                                USER.lines->back().erase();
                            }
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym){
                        case SDLK_RCTRL:
                        case SDLK_LCTRL:
                            ctrl = false;
                            break;
                        case SDLK_LSHIFT:
                        case SDLK_RSHIFT:
                            shift = false;
                            break;
                        case SDLK_RALT:
                        case SDLK_LALT:
                            alt = false;
                            break;
                        }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    updateMouse(event.button.x, event.button.y);
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        g::log("Mouse pressed", 3);
                        // lastOutput = SDL_GetTicks();

                        if (not trackMouse){
                            trackMouse = true;

                            addLine("user", mouseLoc);

                            updateLines();
                        }
                        break;
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT){
                        break;
                    }
                    else if (event.button.button == SDL_BUTTON_MIDDLE){
                        _log("The mouse is at " + std::to_string(event.button.x) + ", " + std::to_string(event.button.y));
                        break;
                    }
                // Mouse leaves the window or the window is resized
                case 512:
                    if (not trackMouse)
                        break;
                    identify = false;
                case SDL_MOUSEBUTTONUP:
                    updateMouse(event.button.x, event.button.y);
                    if (event.button.button == SDL_BUTTON_LEFT or event.type == 512){
                        g::log("Mouse released", 3);

                        // if(USER.lines->back().lineData->size()){
                        finishLine("user", mouseLoc, identify);
                        identify = true;
                        // }
                        // else{
                        //     std::vector<Point> end = {mouseLoc};
                        //     (*arena.players)["user"].lines->back().finish(mouseLoc, end);
                        // }

                        // logVal(USER.lines->size())

                        // assert(trackMouse);
                        trackMouse = false;
                        
                        updateLines();
                        createLines();

                        break;
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT){
                        break;
                    }
                    else if (event.button.button == SDL_BUTTON_MIDDLE){
                        break;
                    }
                case SDL_MOUSEMOTION:
                    updateMouse(event.button.x, event.button.y);
                    if (trackMouse){
                        
                        addData("user", mouseLoc);

                        updateLines();
                        createLines();

                        g::log("Mouse is moving, and I'm tracking it.", 5);
                        
                        // lastOutput = SDL_GetTicks();
                    /*
                        // Behold my superb debugging skillz
                        logVal(arena.vertices->size() / 6);
                        logVal((*arena.players)["user"].lines->size());
                        // for (auto i: *(*arena.players)["user"].lines){
                        for (auto i = (*arena.players)["user"].lines->begin(); i != (*arena.players)["user"].lines->end(); ++i){
                            g::log("--- " + std::to_string(i - (*arena.players)["user"].lines->begin()) + " ---");
                            logVal(i->lineData->size());
                            logVal(i->vertices->size() / 6);
                            logVal(i->isFinished);
                        }
                        _endl; g::log("--------------");
                    */
                    }
                    break;
                case SDLK_PRINTSCREEN:
                    break;
                default:
                    std::cout << "Unknown event type: " << event.type << std::endl;
                    break;
            }
        }

        draw(0);

        // Sets vsync
        SDL_GL_SetSwapInterval(USE_VSYNC);

        // Limit the FPS
        previousTime = currentTime;
        currentTime = SDL_GetTicks();

        // if (currentTime - lastOutput >= 1000)
        //    lastOutput = currentTime;
        if (currentTime - previousTime < 1000 / MAX_FPS)
            SDL_Delay((1000 / MAX_FPS) - (currentTime - previousTime));

        // Swap the buffers so everything you just did is now being shown.
        SDL_GL_SwapWindow(window);
        // Clear the screen and show the background color
        glClearColor(arena.background.r, arena.background.g, arena.background.b, arena.background.a);
        glClear(GL_COLOR_BUFFER_BIT);
        // "Show what you need to shooow, show what you need to shoow..."
        // glViewport(0, 0, width, height);
    }
}

void Gui::cleanup(GLuint vertexShader, GLuint fragmentShader){
    g::log("Cleaning Up...");

    // delete everything and clean up
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    // for(auto& i: stuffToDraw)
        // i->deleteVBOs();
    // stuffToDraw[0]->deleteVBOs();
    // firstLine.deleteVBOs();
    // glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    SDL_GL_DeleteContext(context);
    SDL_Quit();
}

void Gui::init(std::string title){
    g::windowWidth = width; 
    g::windowHeight = height;

    drawColor = (*arena.players)["user"].drawColor;

    initSDL(title);
    initGLEW();
    initLines();
    // createLines();
    createVAO();
    GLuint vertexShader   = createVertexShader();
    GLuint fragmentShader = createFragmentShader();
    compileShaders(vertexShader, fragmentShader);

    colorLoc = glGetUniformLocation(shaderProgram, "drawColor");
    glUniform4f(colorLoc, drawColor.r, drawColor.g, drawColor.b, drawColor.a);

    arrangeLines();
    run();
    cleanup(vertexShader, fragmentShader);
}

Gui::~Gui() {}