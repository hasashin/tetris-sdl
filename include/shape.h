#ifndef TETRIS_SDL_SHAPE_H
#define TETRIS_SDL_SHAPE_H

#define OTYPE_T_SHAPE {{0,8},{8,8},{0,8}}
#define OTYPE_L_SHAPE {{8,0},{8,0},{8,8}}
#define OTYPE_J_SHAPE {{0,8},{0,8},{8,8}}
#define OTYPE_I_SHAPE {{8},{8},{8},{8}}
#define OTYPE_SQ_SHAPE {{8,8},{8,8}}
#define OTYPE_Z_SHAPE {{0,8},{8,8},{8,0}}
#define OTYPE_S_SHAPE {{8,0},{8,8},{0,8}}


enum objectType {
    OTYPE_T,
    OTYPE_L,
    OTYPE_J,
    OTYPE_SQ,
    OTYPE_I,
    OTYPE_S,
    OTYPE_Z
};

enum objectRotation {
    ROTATION_NONE,
    ROTATION_RIGHT,
    ROTATION_UPDOWN,
    ROTATION_LEFT
};

class shape {
protected:
    tetrisMatrix matrix;
    objectRotation& rotation;

    shape(
            tetrisMatrix matrix_,
            objectRotation& rotation_
    ) : matrix(matrix_), rotation(rotation_){}

public:
    virtual ~shape() {}

    virtual bool canMoveDown(int x, int y,tetrisMatrix& baseMatrix) = 0;

    bool canMoveLeft(int y) {
        return y > 0;
    }

    bool canMoveRight(int y, tetrisMatrix& baseMatrix) {
        switch (rotation) {
            case ROTATION_NONE:
            case ROTATION_UPDOWN:
                return y + matrix[0].size() < baseMatrix[0].size()-1;
            case ROTATION_RIGHT:
            case ROTATION_LEFT:
                return y + matrix.size() < baseMatrix[0].size()-1;
            default:
                return false;
        }
    }

public:
    std::vector<std::vector<int>> &getMatrix() {
        return matrix;
    }
};

class I_shape : public shape {
public:
    explicit I_shape(objectRotation& rotation) : shape(OTYPE_I_SHAPE, rotation) {}

    ~I_shape() = default;

    bool canMoveDown(int x, int y,tetrisMatrix& baseMatrix) {
        switch (rotation) {
            case ROTATION_NONE:
            case ROTATION_UPDOWN:
                return x + matrix.size() < baseMatrix.size() && baseMatrix[x + 4][y] == 0;
            case ROTATION_LEFT:
            case ROTATION_RIGHT:
                return x + 1 < baseMatrix.size()
                       && baseMatrix[x + 1][y] == 0
                       && baseMatrix[x + 1][y + 1] == 0
                       && baseMatrix[x + 1][y + 2] == 0
                       && baseMatrix[x + 1][y + 3] == 0;
            default:
                return false;
        }
    }
};

class J_shape : public shape {
public:
    explicit J_shape(objectRotation& rotation) : shape(OTYPE_J_SHAPE, rotation) {}

    bool canMoveDown(int x, int y,tetrisMatrix& baseMatrix) {
        switch (rotation) {
            case ROTATION_NONE:
                return x + matrix.size() < baseMatrix.size()
                       && baseMatrix[x + 3][y] == 0
                       && baseMatrix[x + 3][y + 1] == 0;
            case ROTATION_RIGHT:
                return x + matrix[0].size() < baseMatrix.size()
                       && baseMatrix[x + 2][y] == 0
                       && baseMatrix[x + 2][y + 1] == 0
                       && baseMatrix[x + 2][y + 2] == 0;
            case ROTATION_LEFT:
                return x + matrix[0].size() < baseMatrix.size()
                       && baseMatrix[x + 1][y] == 0
                       && baseMatrix[x + 1][y + 1] == 0
                       && baseMatrix[x + 2][y + 2] == 0;
            case ROTATION_UPDOWN:
                return x + matrix.size() < baseMatrix.size()
                       && baseMatrix[x + 3][y] == 0
                       && baseMatrix[x + 1][y + 1] == 0;
            default:
                return false;
        }
    }
};

class L_shape : public shape {
public:
    explicit L_shape(objectRotation& rotation) : shape(OTYPE_L_SHAPE, rotation) {}

    bool canMoveDown(int x, int y,tetrisMatrix& baseMatrix) {
        switch (rotation) {
            case ROTATION_NONE:
                return x + matrix.size() < baseMatrix.size()
                       && baseMatrix[x + 3][y] == 0
                       && baseMatrix[x + 3][y + 1] == 0;
            case ROTATION_RIGHT:
                return x + matrix[0].size() < baseMatrix.size()
                       && baseMatrix[x + 2][y] == 0
                       && baseMatrix[x + 1][y + 1] == 0
                       && baseMatrix[x + 1][y + 2] == 0;
            case ROTATION_LEFT:
                return x + matrix[0].size() < baseMatrix.size()
                       && baseMatrix[x + 2][y] == 0
                       && baseMatrix[x + 2][y + 1] == 0
                       && baseMatrix[x + 2][y + 2] == 0;
            case ROTATION_UPDOWN:
                return x + matrix.size() < baseMatrix.size()
                       && baseMatrix[x + 1][y] == 0
                       && baseMatrix[x + 3][y + 1] == 0;
            default:
                return false;
        }
    }
};

class T_shape : public shape {
public:
    explicit T_shape(objectRotation& rotation) : shape(OTYPE_T_SHAPE, rotation) {}

    bool canMoveDown(int x, int y,tetrisMatrix& baseMatrix) {
        switch (rotation) {
            case ROTATION_NONE:
                return x + matrix.size() < baseMatrix.size()
                       && baseMatrix[x + 2][y] == 0
                       && baseMatrix[x + 3][y + 1] == 0;
            case ROTATION_RIGHT:
                return x + matrix[0].size() < baseMatrix.size()
                       && baseMatrix[x + 2][y] == 0
                       && baseMatrix[x + 2][y + 1] == 0
                       && baseMatrix[x + 2][y + 2] == 0;
            case ROTATION_LEFT:
                return x + matrix[0].size() < baseMatrix.size()
                       && baseMatrix[x + 1][y] == 0
                       && baseMatrix[x + 2][y + 1] == 0
                       && baseMatrix[x + 1][y + 2] == 0;
            case ROTATION_UPDOWN:
                return x + matrix.size() < baseMatrix.size()
                       && baseMatrix[x + 3][y] == 0
                       && baseMatrix[x + 2][y + 1] == 0;
            default:
                return false;
        }
    }
};

class S_shape : public shape {
public:
    explicit S_shape(objectRotation& rotation) : shape(OTYPE_S_SHAPE, rotation) {}

    bool canMoveDown(int x, int y,tetrisMatrix& baseMatrix) {
        switch (rotation) {
            case ROTATION_LEFT:
            case ROTATION_RIGHT:
                return x + matrix[0].size() < baseMatrix.size()
                       && baseMatrix[x + 2][y] == 0
                       && baseMatrix[x + 2][y + 1] == 0
                       && baseMatrix[x + 1][y + 2] == 0;
            case ROTATION_NONE:
            case ROTATION_UPDOWN:
                return x + matrix.size() < baseMatrix.size()
                       && baseMatrix[x + 2][y] == 0
                       && baseMatrix[x + 3][y + 1] == 0;
            default:
                return false;
        }
    }
};

class Z_shape : public shape {
public:
    explicit Z_shape(objectRotation& rotation) : shape(OTYPE_Z_SHAPE, rotation) {}

    bool canMoveDown(int x, int y,tetrisMatrix& baseMatrix) {
        switch (rotation) {
            case ROTATION_LEFT:
            case ROTATION_RIGHT:
                return x + matrix[0].size() < baseMatrix.size()
                       && baseMatrix[x + 1][y] == 0
                       && baseMatrix[x + 2][y + 1] == 0
                       && baseMatrix[x + 2][y + 2] == 0;
            case ROTATION_NONE:
            case ROTATION_UPDOWN:
                return x + matrix.size() < baseMatrix.size()
                       && baseMatrix[x + 3][y] == 0
                       && baseMatrix[x + 2][y + 1] == 0;
            default:
                return false;
        }
    }
};

class SQ_shape : public shape {
public:
    explicit SQ_shape(objectRotation& rotation) : shape(OTYPE_SQ_SHAPE, rotation) {}

    bool canMoveDown(int x, int y,tetrisMatrix& baseMatrix) {
        switch (rotation) {
            case ROTATION_LEFT:
            case ROTATION_RIGHT:
            case ROTATION_NONE:
            case ROTATION_UPDOWN:
                return x + matrix.size() < baseMatrix.size()
                       && baseMatrix[x + 2][y] == 0
                       && baseMatrix[x + 2][y + 1] == 0;
            default:
                return false;
        }
    }
};

#endif //TETRIS_SDL_SHAPE_H
