#ifndef TETRIS_SDL_GAMELOGIC_H
#define TETRIS_SDL_GAMELOGIC_H

#include <vector>

class gameLogic {

    objectTypes thisType;
    objectTypes nextType;

    int drawingColor;

    gameDraw *draw;

    bool running = false;
    int x=0,y=5;
    void generateObject() {
        thisType = nextType;
        //nextType = (objectTypes) global::random(0, 7);
        drawingColor = global::random(1,7);
        x=0;y=5;
        draw->spawnObject(x,y,thisType,drawingColor);
        draw->drawGrid();
    }

    void update() {
        SDL_Delay(800);
        if(draw->moveDown(x,y,thisType,ROTATION_NONE)){
            x+=1;
            draw->spawnObject(x,y,thisType,drawingColor);
        } else running = false;
        draw->drawGrid();

    }

    bool checkConditions() {
        bool toret = true;
        for (auto &elem:draw->firstRow()) {
            if (elem > 0) toret = false;
        }
        return toret || running;
    }

    friend class gameDraw;

public:

    gameLogic(gameDraw *&gd) : draw(gd) {
        //nextType = (objectTypes) global::random(0, 7);
        nextType = OTYPE_L;
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
