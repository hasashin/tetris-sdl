#ifndef TETRIS_SDL_GAMEDRAW_H
#define TETRIS_SDL_GAMEDRAW_H

class gameDraw {
    SDL_Renderer *renderer = nullptr;

    SDL_Rect main;

    std::vector<std::vector<int>> matrix =
            {
                    {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
                    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                    {0, 0, 0, 2, 2, 2, 0, 0, 0, 0},
                    {0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 2, 2, 2, 0, 0, 0, 0},
                    {0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 2, 2, 2, 0, 0, 0, 0},
                    {0, 0, 0, 3, 3, 3, 0, 0, 0, 0},
                    {0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 3, 0, 0, 0, 0},
                    {0, 0, 0, 3, 3, 3, 0, 0, 0, 0},
                    {0, 0, 0, 4, 4, 4, 0, 0, 0, 0},
                    {0, 0, 0, 0, 4, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 4, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 4, 0, 0, 0, 0, 0},
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
