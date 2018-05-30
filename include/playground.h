#ifndef TETRIS_SDL_PLAYGROUND_H
#define TETRIS_SDL_PLAYGROUND_H

using tetrisMatrix=std::vector<std::vector<int>>;

#include <shape.h>
#include <matrix.h>
#include <gameDraw.h>
#include <gameLogic.h>


class playground : public object {

    gameDraw *drawer;

    gameMatrix matrix = gameMatrix({
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
                                   });

    gameLogic *logic = new gameLogic(drawer, matrix);

    void keyboardInputControl(SDL_Scancode scancode) override {
        switch (scancode) {
            case SDL_SCANCODE_ESCAPE:
                global::pause = true;
                break;
            case SDL_SCANCODE_LEFT:
                if (logic->fallShape->canMoveLeft(logic->y))
                    logic->matrix.moveLeft(
                            logic->x,
                            logic->y,
                            logic->thisRotation,
                            logic->thisColor,
                            logic->fallShape->getMatrix()
                    );
                break;
            case SDL_SCANCODE_RIGHT:
                if (logic->fallShape->canMoveRight(logic->y, logic->matrix.get()))
                    logic->matrix.moveRight(
                            logic->x,
                            logic->y,
                            logic->thisRotation,
                            logic->thisColor,
                            logic->fallShape->getMatrix()
                    );
                break;
            case SDL_SCANCODE_UP:
                logic->chngRotation = true;
                break;
            case SDL_SCANCODE_DOWN:
                logic->speed=20;
                break;
            default:
                break;
        }
    }

public:
    explicit playground(SDL_Renderer *&ren,SDL_Window* window) : object(ren) {
        int x = global::SCREEN_W / 4;
        int y = global::SCREEN_H / 2;
        drawer = new gameDraw(window,x,y);
    }

    ~playground() {
        delete drawer;
        delete logic;
    }

    void operator()() {
        logic->run();
    }
};

#endif //TETRIS_SDL_PLAYGROUND_H
