#ifndef TETRIS_SDL_GAMELOGIC_H
#define TETRIS_SDL_GAMELOGIC_H

#include <vector>

enum objectTypes {
    OTYPE_T,
    OTYPE_L,
    OTYPE_J,
    OTYPE_SQ,
    OTYPE_I,
    OTYPE_S,
    OTYPE_Z
};

class gameLogic {

    objectTypes thisType;
    objectTypes nextType;

    gameDraw *draw;

    bool running = false;

    void generateObject() {
        thisType = nextType;
        nextType = (objectTypes) global::random(0, 7);
    }

    void update() {

    }

    bool checkConditions() {
        bool toret = true;
        for (auto &elem:draw->firstRow()) {
            if (elem == 1) toret = false;
        }
        return toret || running;
    }

    friend class gameDraw;

public:

    gameLogic(gameDraw *&gd) : draw(gd) {
        nextType = (objectTypes) global::random(0, 7);
    }

    void operator()() {
        if (checkConditions()) {
            if (!running) {
                running = true;
                generateObject();
                update();
            } else {
                update();
            }
        } else {
            global::state = global::PS_GAMEOVER;
        }
    }


};


#endif //TETRIS_SDL_GAMELOGIC_H
