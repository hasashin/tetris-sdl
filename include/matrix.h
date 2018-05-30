#ifndef TETRIS_SDL_MATRIX_H
#define TETRIS_SDL_MATRIX_H

#include <vector>


class gameMatrix {
    tetrisMatrix baseMatrix;

public:
    explicit gameMatrix(tetrisMatrix matrix) : baseMatrix(matrix) {}

    gameMatrix() = delete;

    void drawShape(int x, int y, int &color, objectRotation rotation, tetrisMatrix &matrix) {
        switch (rotation) {
            case ROTATION_NONE:
                for (int i = 0; i < matrix.size(); i++) {
                    for (int j = 0; j < matrix[0].size(); j++) {
                        if (matrix[i][j] > 0) baseMatrix[x + i][y + j] = color;
                    }
                }
                break;
            case ROTATION_LEFT:
                for (int i = 0; i < matrix.size(); i++) {
                    for (int j = (int) matrix[0].size() - 1; j >= 0; j--) {
                        if (matrix[i][j] > 0) baseMatrix[x + matrix[0].size() - 1 - j][y + i] = color;
                    }
                }
                break;
            case ROTATION_UPDOWN:
                for (int i = (int) matrix.size() - 1; i >= 0; i--) {
                    for (int j = (int) matrix[0].size() - 1; j >= 0; j--) {
                        if (matrix[matrix.size() - 1 - i][matrix[0].size() - 1 - j] > 0)
                            baseMatrix[x + i][y + j] = color;
                    }
                }
                break;
            case ROTATION_RIGHT:
                for (int i = (int) matrix.size() - 1; i >= 0; i--) {
                    for (int j = 0; j < matrix[0].size(); j++) {
                        if (matrix[i][j] > 0) baseMatrix[x + j][y + matrix.size() - 1 - i] = color;
                    }
                }
                break;
            default:
                break;
        }
    }

    void eraseShape(int x, int y, objectRotation rotation, tetrisMatrix &matrix) {
        switch (rotation) {
            case ROTATION_NONE:
                for (int i = 0; i < matrix.size(); i++) {
                    for (int j = 0; j < matrix[0].size(); j++) {
                        if (matrix[i][j] > 0) baseMatrix[x + i][y + j] = 0;
                    }
                }
                break;
            case ROTATION_LEFT:
                for (int i = 0; i < matrix.size(); i++) {
                    for (int j = (int) matrix[0].size() - 1; j >= 0; j--) {
                        if (matrix[i][j] > 0) baseMatrix[x + matrix[0].size() - 1 - j][y + i] = 0;
                    }
                }
                break;
            case ROTATION_UPDOWN:
                for (int i = (int) matrix.size() - 1; i >= 0; i--) {
                    for (int j = (int) matrix[0].size() - 1; j >= 0; j--) {
                        if (matrix[matrix.size() - 1 - i][matrix[0].size() - 1 - j] > 0) baseMatrix[x + i][y + j] = 0;
                    }
                }
                break;
            case ROTATION_RIGHT:
                for (int i = (int) matrix.size() - 1; i >= 0; i--) {
                    for (int j = 0; j < matrix[0].size(); j++) {
                        if (matrix[i][j] > 0) baseMatrix[x + j][y + matrix.size() - 1 - i] = 0;
                    }
                }
                break;
            default:
                break;
        }
    }

    void moveDown(int& x, int y, objectRotation rotation,int color, tetrisMatrix& matrix) {
       eraseShape(x,y,rotation,matrix);
       drawShape(++x,y,color,rotation,matrix);
    }
    void moveLeft(int x, int &y, objectRotation rotation,int color, tetrisMatrix& matrix){
        eraseShape(x,y,rotation,matrix);
        drawShape(x,--y,color,rotation,matrix);
    }
    void moveRight(int x, int &y,objectRotation rotation, int color, tetrisMatrix& matrix){
        eraseShape(x,y,rotation,matrix);
        drawShape(x,++y,color, rotation,matrix);
    }

    std::vector<int>& operator[](int i){
        return baseMatrix[i];
    }

    tetrisMatrix& get(){
        return baseMatrix;
    }
};

#endif //TETRIS_SDL_MATRIX_H
