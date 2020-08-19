#include "Nuklear.hpp"

void Nuklear::init(){
    ctx = nk_sdl_init(this->window);

    // Load Fonts: if none of these are loaded a default font will be used
    // Load Cursor: if you uncomment cursor loading please hide the cursor
    
    //* nk_sdl_font_stash_begin(&atlas);
    // struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14, 0);
    // struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 16, 0);
    // struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);
    // struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);
    // struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);
    // struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);
    //* nk_sdl_font_stash_end();
    // nk_style_load_all_cursors(ctx, atlas->cursors);
    // nk_style_set_font(ctx, &roboto->handle);

    // style.c
    // set_style(ctx, THEME_WHITE);
    // set_style(ctx, THEME_RED);
    // set_style(ctx, THEME_BLUE);
    // set_style(ctx, THEME_DARK);
}    

void Nuklear::startInput(){
    nk_input_begin(ctx);
}

void Nuklear::handleEvent(SDL_Event& evt){
    nk_sdl_handle_event(&evt);
    // // struct nk_context *ctx = &sdl.ctx;
    // if (evt.type == SDL_KEYUP || evt.type == SDL_KEYDOWN) {
    //     /* key events */
    //     int down = evt.type == SDL_KEYDOWN;
    //     const Uint8* state = SDL_GetKeyboardState(0);
    //     SDL_Keycode sym = evt.key.keysym.sym;
    //     if (sym == SDLK_RSHIFT || sym == SDLK_LSHIFT)
    //         nk_input_key(ctx, NK_KEY_SHIFT, down);
    //     else if (sym == SDLK_DELETE)
    //         nk_input_key(ctx, NK_KEY_DEL, down);
    //     else if (sym == SDLK_RETURN)
    //         nk_input_key(ctx, NK_KEY_ENTER, down);
    //     else if (sym == SDLK_TAB)
    //         nk_input_key(ctx, NK_KEY_TAB, down);
    //     else if (sym == SDLK_BACKSPACE)
    //         nk_input_key(ctx, NK_KEY_BACKSPACE, down);
    //     else if (sym == SDLK_HOME) {
    //         nk_input_key(ctx, NK_KEY_TEXT_START, down);
    //         nk_input_key(ctx, NK_KEY_SCROLL_START, down);
    //     } else if (sym == SDLK_END) {
    //         nk_input_key(ctx, NK_KEY_TEXT_END, down);
    //         nk_input_key(ctx, NK_KEY_SCROLL_END, down);
    //     } else if (sym == SDLK_PAGEDOWN) {
    //         nk_input_key(ctx, NK_KEY_SCROLL_DOWN, down);
    //     } else if (sym == SDLK_PAGEUP) {
    //         nk_input_key(ctx, NK_KEY_SCROLL_UP, down);
    //     } else if (sym == SDLK_z)
    //         nk_input_key(ctx, NK_KEY_TEXT_UNDO, down && state[SDL_SCANCODE_LCTRL]);
    //     else if (sym == SDLK_r)
    //         nk_input_key(ctx, NK_KEY_TEXT_REDO, down && state[SDL_SCANCODE_LCTRL]);
    //     else if (sym == SDLK_c)
    //         nk_input_key(ctx, NK_KEY_COPY, down && state[SDL_SCANCODE_LCTRL]);
    //     else if (sym == SDLK_v)
    //         nk_input_key(ctx, NK_KEY_PASTE, down && state[SDL_SCANCODE_LCTRL]);
    //     else if (sym == SDLK_x)
    //         nk_input_key(ctx, NK_KEY_CUT, down && state[SDL_SCANCODE_LCTRL]);
    //     else if (sym == SDLK_b)
    //         nk_input_key(ctx, NK_KEY_TEXT_LINE_START, down && state[SDL_SCANCODE_LCTRL]);
    //     else if (sym == SDLK_e)
    //         nk_input_key(ctx, NK_KEY_TEXT_LINE_END, down && state[SDL_SCANCODE_LCTRL]);
    //     else if (sym == SDLK_UP)
    //         nk_input_key(ctx, NK_KEY_UP, down);
    //     else if (sym == SDLK_DOWN)
    //         nk_input_key(ctx, NK_KEY_DOWN, down);
    //     else if (sym == SDLK_LEFT) {
    //         if (state[SDL_SCANCODE_LCTRL])
    //             nk_input_key(ctx, NK_KEY_TEXT_WORD_LEFT, down);
    //         else nk_input_key(ctx, NK_KEY_LEFT, down);
    //     } else if (sym == SDLK_RIGHT) {
    //         if (state[SDL_SCANCODE_LCTRL])
    //             nk_input_key(ctx, NK_KEY_TEXT_WORD_RIGHT, down);
    //         else nk_input_key(ctx, NK_KEY_RIGHT, down);
    //     } else return 0;
    //     return 1;
    // } else if (evt.type == SDL_MOUSEBUTTONDOWN || evt.type == SDL_MOUSEBUTTONUP) {
    //     /* mouse button */
    //     int down = evt.type == SDL_MOUSEBUTTONDOWN;
    //     const int x = evt.button.x, y = evt.button.y;
    //     if (evt.button.button == SDL_BUTTON_LEFT) {
    //         if (evt.button.clicks > 1)
    //             nk_input_button(ctx, NK_BUTTON_DOUBLE, x, y, down);
    //         nk_input_button(ctx, NK_BUTTON_LEFT, x, y, down);
    //     } else if (evt.button.button == SDL_BUTTON_MIDDLE)
    //         nk_input_button(ctx, NK_BUTTON_MIDDLE, x, y, down);
    //     else if (evt.button.button == SDL_BUTTON_RIGHT)
    //         nk_input_button(ctx, NK_BUTTON_RIGHT, x, y, down);
    //     return 1;
    // } else if (evt.type == SDL_MOUSEMOTION) {
    //     /* mouse motion */
    //     if (ctx.input.mouse.grabbed) {
    //         int x = (int)ctx.input.mouse.prev.x, y = (int)ctx.input.mouse.prev.y;
    //         nk_input_motion(ctx, x + evt.motion.xrel, y + evt.motion.yrel);
    //     } else nk_input_motion(ctx, evt.motion.x, evt.motion.y);
    //     return 1;
    // } else if (evt.type == SDL_TEXTINPUT) {
    //     /* text input */
    //     nk_glyph glyph;
    //     memcpy(glyph, evt.text.text, NK_UTF_SIZE);
    //     nk_input_glyph(ctx, glyph);
    //     return 1;
    // } else if (evt.type == SDL_MOUSEWHEEL) {
    //     /* mouse wheel */
    //     nk_input_scroll(ctx,nk_vec2((float)evt.wheel.x,(float)evt.wheel.y));
    //     return 1;
    // }
    // return 0;
// }

}

void Nuklear::endInput(){
    nk_input_end(ctx);
}

void Nuklear::draw(){
    if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)){
        enum {EASY, HARD};
        static int op = EASY;
        static int property = 20;
        struct nk_colorf bg;
        bg.r = this->arena.background.r; bg.g = this->arena.background.g; bg.b = this->arena.background.b; bg.a = this->arena.background.a;

        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button"))
            printf("button pressed!\n");

        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
        nk_layout_row_dynamic(ctx, 22, 1);
        nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);

        if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx),400))){
            nk_layout_row_dynamic(ctx, 120, 1);
            bg = nk_color_picker(ctx, bg, NK_RGBA);
            nk_layout_row_dynamic(ctx, 25, 1);
            this->arena.background.r = nk_propertyf(ctx, "#R:", 0, this->arena.background.r, 1.0f, 0.01f,0.005f);
            this->arena.background.g = nk_propertyf(ctx, "#G:", 0, this->arena.background.g, 1.0f, 0.01f,0.005f);
            this->arena.background.b = nk_propertyf(ctx, "#B:", 0, this->arena.background.b, 1.0f, 0.01f,0.005f);
            this->arena.background.a = nk_propertyf(ctx, "#A:", 0, this->arena.background.a, 1.0f, 0.01f,0.005f);
            nk_combo_end(ctx);
        }
    }
    nk_end(ctx);
}

void Nuklear::render(){
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
}

void Nuklear::cleanup(){
    nk_sdl_shutdown();
}