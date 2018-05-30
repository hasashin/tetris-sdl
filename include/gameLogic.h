#ifndef TETRIS_SDL_GAMELOGIC_H
#define TETRIS_SDL_GAMELOGIC_H

#include <vector>

class gameLogic {

    friend class playground;

    objectType thisType, nextType;

    int thisColor, nextColor;

    objectRotation thisRotation, nextRotation;

    gameDraw *draw;

    gameMatrix matrix;

    shape *fallShape;

    bool chngRotation = false;

    int speed=700;

    unsigned int lasttime=0;

    bool running = false;
    int x = 0, y = 5;

    void generateShape() {
        switch (thisType) {
            case OTYPE_I:
                fallShape = new I_shape(thisRotation);
                break;
            case OTYPE_J:
                fallShape = new J_shape(thisRotation);
                break;
            case OTYPE_L:
                fallShape = new L_shape(thisRotation);
                break;
            case OTYPE_S:
                fallShape = new S_shape(thisRotation);
                break;
            case OTYPE_Z:
                fallShape = new Z_shape(thisRotation);
                break;
            case OTYPE_SQ:
                fallShape = new SQ_shape(thisRotation);
                break;
            case OTYPE_T:
                fallShape = new T_shape(thisRotation);
        }
    }

    void changeRotation(){
        matrix.eraseShape(x,y,thisRotation,fallShape->getMatrix());
        thisRotation = (objectRotation)(((int)thisRotation+1)%4);
        SDL_Delay(32);
        matrix.drawShape(x,y,thisColor,thisRotation,fallShape->getMatrix());
    }

    void generateObject() {
        thisType = nextType;
        thisColor = nextColor;
        thisRotation = nextRotation;

        nextType = (objectType) global::random(0, 6);
        nextColor = global::random(1, 6);
        nextRotation = (objectRotation) global::random(0, 3);

        generateShape();

        x = 0;
        y = 5;
        if ((int) thisRotation == 1 || (int) thisRotation == 2) y -= 2;
    }

    void move() {
        if (fallShape->canMoveDown(x,y,matrix.get())) {
            matrix.moveDown(x,y,thisRotation,thisColor,fallShape->getMatrix());
        } else {
            running = false;
            delete fallShape;
        }
    }

    bool checkConditions() {
        bool toret = true;
        for (auto &elem:matrix[0]) {
            if (elem > 0) toret = false;
        }
        return toret || running;
    }

    friend class gameDraw;

public:

    gameLogic(gameDraw *&gameDraw_,gameMatrix& matrix_) : draw(gameDraw_),matrix(matrix_) {
        nextType = (objectType) global::random(0, 6);
        nextColor = global::random(1, 6);
        nextRotation = (objectRotation) global::random(0, 3);
    }

    void run() {
        if (checkConditions()) {
            if (!running) {
                running = true;
                generateObject();
            } else {
                if(SDL_TICKS_PASSED(SDL_GetTicks(),lasttime+speed)) {
                    move();
                    lasttime = SDL_GetTicks();
                    speed = 700;
                }
                if(chngRotation) {
                    changeRotation();
                    chngRotation = false;
                }
            }
        } else {
            global::state = global::PS_GAMEOVER;
        }
        draw->run(matrix.get());
    }


};


#endif //TETRIS_SDL_GAMELOGIC_H
