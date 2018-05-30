#ifndef TETRIS_SDL_GAME_H
#define TETRIS_SDL_GAME_H

#include <control.h>
#include <menu.h>
#include <playground.h>
#include <tetrisFont.h>
#include <pause.h>

class game {

    friend class gameEvent;

    SDL_Window *window;

    event event_;

    void undefinedErrorLoop() {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
        event_.setObptr(nullptr);
        while (!global::close) {
            event_.callEvent();
            SDL_RenderClear(renderer);
            global::drawTexture(
                    100,
                    100,
                    global::renderText(
                            renderer,
                            "Niepoprawny stan programu. Uruchom ponownie grę",
                            {255, 0, 0, 255},
                            "default"
                    ),
                    renderer
            );
            SDL_RenderPresent(renderer);
        }
    }

    void gameLoop() {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        playground plgd(renderer,window);
        global::playgroundptr = &plgd;
        event_.setObptr(&plgd);
        while (global::state == global::PS_INGAME && !global::close) {
            if (global::pause) {
                pauseLoop(renderer);
            } else {
                event_.setObptr(&plgd);
            }
            event_.callEvent();
            getWindowSize();
            plgd();
        }
        global::playgroundptr = nullptr;
        SDL_DestroyRenderer(renderer);
    }

    void genrateTitle(SDL_Renderer* renderer,SDL_Texture* texture){
        SDL_SetRenderTarget(renderer,texture);
        SDL_RenderClear(renderer);
        int w,h,x=0;
        SDL_QueryTexture(texture,nullptr,nullptr,&w,&h);
        w = w/23;
        h = h/5;
        global::drawTetrisLetter(x,0,TETRIS_LETTER_T,window);
        x+=4*w;
        global::drawTetrisLetter(x,0,TETRIS_LETTER_E,window);
        x+=4*w;
        global::drawTetrisLetter(x,0,TETRIS_LETTER_T,window);
        x+=4*w;
        global::drawTetrisLetter(x,0,TETRIS_LETTER_R,window);
        x+=4*w;
        global::drawTetrisLetter(x,0,TETRIS_LETTER_I,window);
        x+=4*w;
        global::drawTetrisLetter(x,0,TETRIS_LETTER_S,window);
        SDL_SetRenderTarget(renderer,nullptr);
    }

    void menuLoop() {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_Texture *title=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,2300,500);
        genrateTitle(renderer,title);
        menu meni(renderer, window);
        event_.setObptr(&meni);
        global::menuptr = &meni;
        while (!global::close && global::state == global::PS_MENU) {
            getWindowSize();
            event_.callEvent();
            SDL_RenderClear(renderer);
            {
                int w, h, ratio;
                SDL_QueryTexture(title, nullptr, nullptr,&w,&h);
                ratio = w/h;
                w = int(0.6 * global::SCREEN_W);
                h = w / ratio;
                global::drawScaledTexture(global::SCREEN_W / 2 - w / 2, (global::SCREEN_H / 2 - h) / 2, w, h,
                                          title, renderer);
            }
            meni();
            SDL_RenderPresent(renderer);
            SDL_Delay(17);
        }
        global::menuptr = nullptr;
        SDL_DestroyRenderer(renderer);
    }

    void pauseLoop(SDL_Renderer *renderer) {
        pause pause_(renderer);
        event_.setObptr(&pause_);
        while (global::pause && !global::close) {
            event_.callEvent();
            getWindowSize();
            pause_();
            SDL_Delay(17);
        }

    }


public:
    game() {
        global::state = global::PS_MENU;
        auto windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
        window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, windowFlags);
        SDL_SetWindowMinimumSize(window, 800, 600);
        if (global::fullscreen) {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        global::gameptr = this;
    }

    ~game() {
        if (window) SDL_DestroyWindow(window);
        global::gameptr = nullptr;
    }

    void operator()() {

        switch (global::state) {
            case global::PS_MENU:
                menuLoop();
                break;
            case global::PS_INGAME:
                gameLoop();
                break;
            default:
                undefinedErrorLoop();
                break;
        }
    }

    void getWindowSize() {
        SDL_GetWindowSize(window, &global::SCREEN_W, &global::SCREEN_H);
    }

    SDL_Window *getWindow() {
        return window;
    }
};

#endif //TETRIS_SDL_GAME_H
