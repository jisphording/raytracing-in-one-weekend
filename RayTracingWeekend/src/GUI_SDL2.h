#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

namespace GUI_SDL2 {

    // SETTINGS
    // ---------- ---------- ---------- ---------- ---------- //

    const char* title = "SDL2 Template";
    int width = 500, height = 500;
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* screen;
    SDL_Rect screensize;
    int frameCount, timerFPS, lastFrame, fps, lastTime;
    int setFPS = 60;
    SDL_Point mouse;
    const Uint8* keystates;
    Uint32 mousestate;
    SDL_Event event;
    bool running;

    // INIT
    // ---------- ---------- ---------- ---------- ---------- //

    void sdl() {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
        SDL_Init(SDL_INIT_EVERYTHING);
        window =
            SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                width, height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        running = 1;
        screensize.x = screensize.y = 0;
        screensize.w = width; screensize.h = height;
        screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    }

    void sdl(const char* t, int w, int h) {
        title = t;
        width = w;
        height = h;
        sdl();
    }

    // COLOR FUNCTIONS
    // ---------- ---------- ---------- ---------- ---------- //

    void drawPoint(SDL_Point p) { SDL_RenderDrawPoint(renderer, p.x, p.y); }
    void drawPoint(int x, int y) { SDL_RenderDrawPoint(renderer, x, y); }
    void setDrawColor(SDL_Color c) { SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a); }

    // UPDATE KEYS
    // ---------- ---------- ---------- ---------- ---------- //

    void updateKeys() {
        keystates = SDL_GetKeyboardState(NULL);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }
        mousestate = SDL_GetMouseState(&mouse.x, &mouse.y);
    }

    // RENDERING
    // ---------- ---------- ---------- ---------- ---------- //

    void begin_render() {
        SDL_SetRenderTarget(renderer, screen);
    }

    void end_render() {
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, screen, &screensize, &screensize);
        SDL_RenderPresent(renderer);
    }

    void quit() {
        running = 0;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(screen);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // UPDATE
    // ---------- ---------- ---------- ---------- ---------- //

    void update() {
        end_render();
        updateKeys();
        begin_render();
    }

    // SAVE IMAGE TO DISK
    // ---------- ---------- ---------- ---------- ---------- //

    void save_texture(const char* file_name, SDL_Renderer* m_renderer = renderer, SDL_Texture* m_texture = screen) {
        SDL_Texture* target = SDL_GetRenderTarget(m_renderer);
        SDL_SetRenderTarget(m_renderer, m_texture);
        SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
        SDL_RenderReadPixels(m_renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
        IMG_SavePNG(surface, file_name);
    }

} // namespace sdltemplate