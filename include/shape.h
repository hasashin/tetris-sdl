#ifndef TETRIS_SDL_SHAPE_H
#define TETRIS_SDL_SHAPE_H

#define OTYPE_T_SHAPE {{0,8},{8,8},{0,8}}
#define OTYPE_L_SHAPE {{8,0},{8,0},{8,8}}
#define OTYPE_J_SHAPE {{0,8},{0,8},{8,8}}
#define OTYPE_I_SHAPE {{8},{8},{8},{8}}
#define OTYPE_SQ_SHAPE {{8,8},{8,8}}
#define OTYPE_S_SHAPE {{0,0,8,8},{8,8,0,0}}
#define OTYPE_Z_SHAPE {{8,8,0,0},{0,0,8,8}}

class shape{
    std::vector<std::vector<int>> matrix;
protected:
    explicit shape(std::vector<std::vector<int>> matrix_):matrix(matrix_){}
    virtual bool canMoveDown() = 0;
    virtual bool canMoveLeft() = 0;
    virtual bool canMoveRight() = 0;
};

class I_shape : public shape{
public:
    I_shape() : shape(OTYPE_I_SHAPE){}
};

#endif //TETRIS_SDL_SHAPE_H
