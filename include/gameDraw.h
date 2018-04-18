#ifndef TETRIS_SDL_GAMEDRAW_H
#define TETRIS_SDL_GAMEDRAW_H

#include <shape.h>

enum objectTypes {
    OTYPE_T,
    OTYPE_L,
    OTYPE_J,
    OTYPE_SQ,
    OTYPE_I,
    OTYPE_S,
    OTYPE_Z
};

enum objectRotation{
    ROTATION_NONE,
    ROTATION_LEFT,
    ROTATION_RIGHT,
    ROTATION_UPDOWN
};

class gameDraw {
    SDL_Renderer *renderer = nullptr;

    SDL_Rect main;

    std::vector<std::vector<int>> matrix =
            {
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
            };

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

    bool moveDown(int x, int y, objectTypes otype,objectRotation rotation){
        switch(otype) {
            case OTYPE_I:
                switch (rotation) {
                    case ROTATION_NONE:
                    case ROTATION_UPDOWN:
                        return x + 4 < matrix.size() && matrix[x + 4][y] == 0;
                    case ROTATION_LEFT:
                    case ROTATION_RIGHT:
                        return x + 1 < matrix.size()
                               && matrix[x + 1][y] == 0
                               && matrix[x + 1][y + 1] == 0
                               && matrix[x + 1][y + 2] == 0
                               && matrix[x + 1][y + 3] == 0;
                    default:
                        return false;
                }

            case OTYPE_L:
                switch(rotation){
                    case ROTATION_NONE:
                        return x+3 < matrix.size() && matrix[x+3][y] == 0 && matrix[x+3][y+1] == 0;
                    case ROTATION_LEFT:
                        return x+1 < matrix.size()
                               && matrix[x+1][y] == 0
                               && matrix[x+1][y+1] == 0
                               && matrix[x+1][y+2] == 0;
                    case ROTATION_RIGHT:
                        return x+2 < matrix.size() && matrix[x+2][y] == 0;
                    case ROTATION_UPDOWN:
                        return x+3 < matrix.size() && matrix[x+3][y+1] == 0;
                    default:
                        return false;
                }
            default:
                return false;
        }
    }

    void eraseObject(int x,int y,std::vector<std::vector<int>>& objmx){
        for(int i=0;i<objmx.size();i++){
            for(int j=0;j<objmx[0].size();j++){
                matrix[x+i][y+j] = 0;
            }
        }
    }

    void spawnObject(int x,int y,objectTypes otype,int color){
        std::vector<std::vector<int>> shapemx;
        switch(otype){
            case OTYPE_I:
                shapemx = OTYPE_I_SHAPE;
                break;
            case OTYPE_J:
                shapemx = OTYPE_J_SHAPE;
                break;
            case OTYPE_L:
                shapemx = OTYPE_L_SHAPE;
                break;
            case OTYPE_S:
                shapemx = OTYPE_S_SHAPE;
                break;
            case OTYPE_SQ:
                shapemx = OTYPE_SQ_SHAPE;
                break;
            case OTYPE_Z:
                shapemx = OTYPE_Z_SHAPE;
                break;
            case OTYPE_T:
                shapemx = OTYPE_T_SHAPE;
                break;
            default:
                return;
        }
        if(x!=0) eraseObject(x-1,y,shapemx);
        for(int i=0;i<shapemx.size();i++){
            for (int j=0;j<shapemx[0].size();j++){
                if(shapemx[i][j]>0) matrix[x+i][y+j] = color;
            }
        }
    }

    void drawElement(int x, int y) {
        if (matrix[y][x]) {
            int w = main.w / (int)matrix[0].size(), h = main.h / (int)matrix.size();
            SDL_Rect elem;
            elem.x = main.x + x * w;
            elem.y = main.y + y * h;
            elem.w = w;
            elem.h = h;

            SDL_SetRenderDrawColor(renderer, Uint8((matrix[y][x] & 4) * 255), Uint8((matrix[y][x] & 2) * 255),
                                   Uint8((matrix[y][x] & 1) * 255), 255);
            SDL_RenderFillRect(renderer, &elem);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_Surface *sur = SDL_LoadBMP((global::programDir + "bitmap/frame.bmp").c_str());
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, sur);
            SDL_RenderCopy(renderer, texture, nullptr, &elem);
            SDL_FreeSurface(sur);
        }
    }

    friend class gameLogic;

public:

    void drawGrid() {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                drawElement(j, i);
            }
        }
    }
    explicit gameDraw(SDL_Renderer *&renderer_) : renderer(renderer_) {}
    gameDraw(SDL_Renderer *&renderer_,const std::vector<std::vector<int>>& baseMatrix) : renderer(renderer_) {
        matrix.clear();
        matrix = baseMatrix;
    }

    void init(int x, int y, int w, int h) {
        main.x = x;
        main.y = y;
        main.w = w;
        main.h = h;
    }


    void operator()() {
        SDL_RenderClear(renderer);
        drawGrid();
        SDL_RenderPresent(renderer);
    }

    std::vector<int> firstRow() {
        return matrix[0];
    }
};

#endif //TETRIS_SDL_GAMEDRAW_H
