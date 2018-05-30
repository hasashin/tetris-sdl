#ifndef TETRIS_SDL_TETRISFONTCONSTS_H
#define TETRIS_SDL_TETRISFONTCONSTS_H

#define TETRIS_LETTER_T {{7,7,7},{0,7,0},{0,7,0},{0,7,0},{0,7,0}}
#define TETRIS_LETTER_E {{7,7,7},{7,0,0},{7,7,7},{7,0,0},{7,7,7}}
#define TETRIS_LETTER_R {{7,7,0},{7,0,7},{7,7,0},{7,0,7},{7,0,7}}
#define TETRIS_LETTER_I {{0,7,0},{0,7,0},{0,7,0},{0,7,0},{0,7,0}}
#define TETRIS_LETTER_S {{7,7,7},{7,0,0},{0,7,0},{0,0,7},{7,7,7}}

namespace global{
    void drawTetrisLetter(int x,int y,std::vector<std::vector<int>> letter,SDL_Window* window){
        int color = random(1,6);
        for(auto &elem:letter){
            for(auto &value:elem) {
                if(value) value=color;
            }
        }
        gameMatrix matrix(letter);
        gameDraw drawer(window,x,y);
        drawer.drawGrid(matrix.get());
    }
}

#endif //TETRIS_SDL_TETRISFONTCONSTS_H
