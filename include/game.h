#ifndef TETRIS_SDL_GAME_H
#define TETRIS_SDL_GAME_H

#include <menu.h>
#include <playground.h>

class game {

    SDL_Window *window;

    event event_;

    void undefinedErrorLoop() {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
        while (!global::close) {
            executeEvents();
            SDL_RenderClear(renderer);
            global::drawTexture(100, 100,
                                global::renderText(renderer, "Niepoprawny stan programu. Uruchom ponownie grę",
                                                   {255, 0, 0, 255}, "default"), renderer);
            SDL_RenderPresent(renderer);
        }
    }

    void keyboardInputControl(SDL_Scancode keycode) {
        if (global::state == global::PS_MENU && global::menuptr) {
            switch (keycode) {
                case SDL_SCANCODE_UP:
                    global::menuptr->toggle(-1);
                    break;
                case SDL_SCANCODE_DOWN:
                    global::menuptr->toggle(1);
                    break;
                case SDL_SCANCODE_RETURN:
                    global::menuptr->doElementAction(window);
                    break;
                case SDL_SCANCODE_ESCAPE:
                    global::menuptr->toggle(INT32_MIN);
                    global::menuptr->doElementAction(window);
                default:
                    break;
            }
            return;
        }
        if(global::state == global::PS_INGAME){
            switch(keycode){
                case SDL_SCANCODE_ESCAPE:
                global::state = global::PS_PAUSE;
                    break;
                default:
                    break;
            }
            return;
        }
        if(global::state == global::PS_PAUSE){
            switch(keycode){
                case SDL_SCANCODE_ESCAPE:
                    global::state = global::PS_INGAME;
                    break;
                default:
                    break;
            }
            return;
        }
    }



    void gameLoop() {

        SDL_Renderer* renderer= SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        playground plgd(renderer);
        global::playgroundptr = &plgd;
        while(global::state == global::PS_INGAME && !global::close){
            executeEvents();
            getWindowSize();
            plgd();
            SDL_Delay(17);
        }
        global::playgroundptr = nullptr;
        SDL_DestroyRenderer(renderer);
    }

    void menuLoop() {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        menu meni(renderer);
        global::menuptr = &meni;
        while (global::state == global::PS_MENU && !global::close) {
            getWindowSize();
            executeEvents();
            SDL_RenderClear(renderer);
            {
                int w, h, ratio;
                SDL_Texture *title = global::renderText(renderer, "TETRIS", {40, 234, 132, 255}, "title");
                SDL_QueryTexture(title, nullptr, nullptr, &w, &h);
                ratio = w / h;
                w = int(0.6 * global::SCREEN_W);
                h = w / ratio;
                global::drawScaledTexture(global::SCREEN_W / 2 - w / 2, (global::SCREEN_H / 2 - h) / 2, w, h,
                                          title, renderer);
            }

            meni();
            SDL_RenderPresent(renderer);
            SDL_Delay(32);
        }
        global::menuptr = nullptr;
        SDL_DestroyRenderer(renderer);
    }

    void executeEvents(){
        SDL_Scancode scancode;
        switch(event_.executeEvents(scancode)){
            case 2:
                keyboardInputControl(scancode);
                break;
            case 1:
            default:
                break;
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

};

#endif //TETRIS_SDL_GAME_H
