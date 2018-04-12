#ifndef TETRIS_SDL_PAUSE_H
#define TETRIS_SDL_PAUSE_H

#include <control.h>

class pause : public object {
    SDL_Renderer *renderer;

    void drawPause() {
        SDL_Rect pause;
        pause.x = 0;
        pause.y = 0;
        pause.w = global::SCREEN_W;
        pause.h = global::SCREEN_H;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
        SDL_RenderFillRect(renderer, &pause);
        SDL_Texture *text = global::renderText(renderer, "PAUZA", {255, 255, 255, 255}, "title");
        int w, h, x, y;
        SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
        x = global::SCREEN_W / 2 - w / 2;
        y = global::SCREEN_H / 2 - h / 2;
        global::drawScaledTexture(x, y, w, h, text, renderer);
        SDL_RenderPresent(renderer);
    }

    void keyboardInputControl(SDL_Scancode scancode) override {
        switch (scancode) {
            case SDL_SCANCODE_ESCAPE:
                global::pause = false;
                break;
            default:
                break;
        }
    }

public:
    explicit pause(SDL_Renderer *renderer_) : renderer(renderer_) {}

    void operator()() {
        drawPause();
    }
};

#endif //TETRIS_SDL_PAUSE_H
