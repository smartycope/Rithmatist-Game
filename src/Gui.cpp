#include "Gui.hpp"
// #include "Debug.hpp"
// Debug d;
// #include "LineForbiddence.hpp"

// this line is intelligent
#define GLSL(src) "#version 330 core\n" #src 

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
    d.logger("Setting up GLEW...");

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

    d.logger("Successfully set up GLEW.");
}

void Gui::initLines(){
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Gui::createLines(){
    // d.logger("Creating Triangle...", 5);
    // float vertices[] = {
    //  0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
    //  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
    // -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
    // };
    
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // int totalLines;
    // for (auto players: arena.players)
    //     totalLines += players.lines.size();

    // GLuint vbo;
    // glGenBuffers(1, &vbo); // Generate 1 buffer

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);

    auto l = arena.getLineVertices().data();

    // float result[l.size()];
    // std::copy(std::begin(l), std::end(l), result);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(l), l, GL_STATIC_DRAW);
    

    // vbos.push_back(vbo);

    // int grandTotalIndecies = 0;
    // for (int i: totalIndecies)
    //     grandTotalIndecies += i;

    // GLuint elements[grandTotalIndecies];


    // GLuint ebo;
    // glGenBuffers(1, &ebo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

void Gui::initSDL(std::string title){
    d.logger("Initializing SDL...");

    // initalize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING))
        std::cerr << "Can't initialize SDL2" << std::endl;

    setSDL_GLAttributes();

    // make the SDL window
    window = SDL_CreateWindow(title.c_str(), windowPosition.x, windowPosition.y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
     /* other options here:
        in place of x and y: SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED
        in place of SDL_WINDOW_OPENGL: SDL_WINDOW_RESIZABLE, SDL_WINDOW_FULLSCREEN (optional)
     */
    // check that it worked
    if (!window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    d.logger("Creating OpenGL context...", 5);
    // Create the OpenGL context (finally)
    context = SDL_GL_CreateContext(window);
    // SDL_GL_MakeCurrent(window, context);
    
}

void Gui::createVAO(){
    d.logger("Creating VAO...", 5);
    // Create Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

GLuint Gui::createVertexShader(){
    d.logger("Creating vertex shader...", 5);
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
    
    d.logger("compiling vertex shader...", 5);
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
    d.logger("Creating fragment shader...", 5);
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

    d.logger("Compiling fragment shader...", 5);
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
    d.logger("Linking shaders...", 5);
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
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    // glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
    //                                                          stride                 offset
}

void Gui::run(){
    d.logger("Starting window proper...");

    // the event loop
    SDL_Event event;
    bool fullscreen = false, run = true, trackMouse = false;
    Uint32 windowFlags = 0; // fudge variable
    std::vector<Point> lineData;

    while (run){
        SDL_GetMouseState(&mouseLoc.x, &mouseLoc.y);

        if (SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    run = false; break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            run = false; break;

                        case 'f':
                            fullscreen = !fullscreen;
                            if (fullscreen){
                                SDL_SetWindowFullscreen(window, windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                            }
                            else{
                                SDL_SetWindowFullscreen(window, windowFlags);
                            }
                            break;
                        // add key here
                    }

                case SDL_MOUSEBUTTONDOWN:
                {
                    trackMouse = true;

                    Line newLine(mouseLoc);
                    arena.players.front().lines.push_back(newLine);

                    // createLines();

                    d.logger("Mouse pressed", 4);
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                    trackMouse = false;

                    assert(not arena.players.front().lines.back().isFinished);
                    // assert(not lineData.empty()); // This is just a dot.
                    arena.players.front().lines.back().finish(mouseLoc, lineData);

                    createLines();
                    
                    // d.printVector(indecies, -1, 0);
                    d.logger("Mouse released", 4);
                    break;
                case SDL_MOUSEMOTION:
                    if (trackMouse){
                        lineData.push_back(mouseLoc);

                        d.logger("Mouse is moving, and I'm tracking it.", 5);
                    }
                    break;
            }
        }
        
        // now draw everything in the vector of things we need to draw
        // for(auto players: arena.players)
        //     for(auto line: players.lines)
        //         line.draw();

        //                 type, start, count
        
        int offset = 0;
        for (auto i: arena.players.front().lines){
            glDrawArrays(GL_LINES_ADJACENCY, offset, i.getDataLen());
            offset += i.getDataLen();
            // d.logger("Drawing lines", 5);
        }
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        if (!trackMouse)
            lineData.clear();

        // lastly, swap the buffers so everything you just did is now being shown.
        SDL_GL_SwapWindow(window);
        // clear the screen
        glClearColor(arena.background.r, arena.background.g, arena.background.b, arena.background.a);
        // glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // "Show what you need to shooow, show what you need to shoow..."
        // glViewport(0, 0, width, height);
    }

    d.logger("Exit signal recieved, closing window.");
}

void Gui::cleanup(GLuint vertexShader, GLuint fragmentShader){
    d.logger("Cleaning Up...");

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
    drawColor = arena.players.front().lineColor;

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