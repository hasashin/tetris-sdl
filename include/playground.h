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



class playground {

    gameDraw* drawer;

    gameLogic* logic = new gameLogic(drawer);

public:
    explicit playground(SDL_Renderer *&ren):drawer(new gameDraw(ren)){
        int h = int(global::SCREEN_H * 0.9);
        int w = h / 2;
        int x = global::SCREEN_W / 4 - w / 2;
        int y = global::SCREEN_H / 2 - h / 2;
        drawer->init(x,y,w,h);
    }

    void operator()() {
        if(global::state == global::PS_PAUSE){
            drawer->drawPause();
            logic->pause();
        }
        (*drawer)();
//        (*logic)();
    }
};

#endif //TETRIS_SDL_PLAYGROUND_H