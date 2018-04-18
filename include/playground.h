#ifndef TETRIS_SDL_PLAYGROUND_H
#define TETRIS_SDL_PLAYGROUND_H

#include <gameDraw.h>
#include <gameLogic.h>

/* Object colors definitions
 * 0 - black/no object drawing
 * 1 - blue
 * 2 - green
 * 3 - cyan
 * 4 - red
 * 5 - magenta
 * 6 - yellow
 * 7 - white
 * 8 - black/object present
 */



class playground : public object {

    gameDraw *drawer;

    gameLogic *logic = new gameLogic(drawer);

    void keyboardInputControl(SDL_Scancode scancode) override {
        switch (scancode) {
            case SDL_SCANCODE_ESCAPE:
                global::pause = true;
                break;
            default:
                break;
        }
    }

public:
    explicit playground(SDL_Renderer *&ren) : drawer(new gameDraw(ren)) {
        int h = int(global::SCREEN_H * 0.9);
        int w = h / 2;
        int x = global::SCREEN_W / 4 - w / 2;
        int y = global::SCREEN_H / 2 - h / 2;
        drawer->init(x, y, w, h);
    }

    void operator()() {
        (*drawer)();
        (*logic)();
    }
};

#endif //TETRIS_SDL_PLAYGROUND_H
