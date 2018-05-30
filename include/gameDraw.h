#ifndef TETRIS_SDL_GAMEDRAW_H
#define TETRIS_SDL_GAMEDRAW_H

#include <exception>

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

#define BLOCK_SIZE 47

#include <shape.h>

class gameDraw {
    SDL_Renderer *renderer = nullptr;

    SDL_Rect main;

    SDL_Window *window;

    std::vector<SDL_Rect> blocks;

    const int x, y;

    void drawFrame() {
        SDL_Surface *surf = SDL_LoadBMP((global::programDir + "bitmap/mainframe.bmp").c_str());
        SDL_Texture *frames = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_Rect topleft, topright, bottomleft, bottomright;

        topleft.x = main.x - main.w / 10;
        topleft.y = main.y - main.h / 20;
        topleft.w = main.w / 20;
        topleft.h = main.h / 10;

        topright.x = main.x;
        topright.y = main.y + main.h / 20;
        topright.w = main.w / 20;
        topright.h = main.h / 10;

        bottomleft.x = main.x - main.w / 10;
        bottomleft.y = int(main.y + main.h * 1.2);
        bottomleft.w = main.w / 20;
        bottomleft.h = main.h / 10;

        bottomright.x = main.x;
        bottomright.y = int(main.y + main.h * 1.2);
        bottomright.w = main.w / 20;
        bottomright.h = main.h / 10;
    }

    void init() {
        main.x = x;
        main.y = y;
        main.w = BLOCK_SIZE;
        main.h = BLOCK_SIZE;
    }

    friend class gameLogic;

public:

    void drawGrid(tetrisMatrix &matrix) {
        SDL_Surface *sur = SDL_LoadBMP((global::programDir + "bitmap/blocks.bmp").c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, sur);
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                main.x = x + BLOCK_SIZE * j;
                main.y = y + BLOCK_SIZE * i;
                SDL_RenderCopy(renderer, texture, &blocks[matrix[i][j] - 1], &main);
            }
        }
        main.x = x;
        main.y = y;
        SDL_FreeSurface(sur);
    }

    gameDraw(SDL_Window *window_, int x_, int y_) : x(x_), y(y_), window(window_){
        renderer = SDL_GetRenderer(window);
        SDL_Rect temp;
        temp.x = 0;
        temp.y = 0;
        temp.w = BLOCK_SIZE;
        temp.h = BLOCK_SIZE;
        for (int i = 1; i < 8; i++) {
            blocks.push_back(temp);
            temp.x += BLOCK_SIZE;
        }
        init();
    }

    void run(tetrisMatrix &matrix) {
        if(window != nullptr && renderer != SDL_GetRenderer(window))
            throw std::invalid_argument("Renderer jest niepoprawny");
        SDL_RenderSetScale(renderer, global::SCREEN_W / 1680, global::SCREEN_H / 1050);
        SDL_RenderClear(renderer);
        drawGrid(matrix);
        SDL_RenderPresent(renderer);
    }

};

#endif //TETRIS_SDL_GAMEDRAW_H
