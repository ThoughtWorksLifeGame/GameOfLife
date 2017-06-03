//
// Created by Digong Jiang on 2017/6/3.
//

#ifndef GAMEOFLIFE_MATRIX_H
#define GAMEOFLIFE_MATRIX_H

#ifdef GTEST
#define private public
#define protected public
#endif

#include <vector>


class Matrix {
public:
    typedef std::vector<std::vector<bool>> MatrixType;
private:
    int matrixDim;
    std::vector<std::pair<int, int>> aliveCells;
    MatrixType matrix, prevMatrix;
public:
    Matrix(int n);
    void AssignInitState(const MatrixType& input);

    bool IsCoordLegal(int x, int y);

    int GetCountOfAliveCellsAround(int x, int y);

    void GetNetMatrixByAliveCells();

    const MatrixType& GetNextMatrix();

    const MatrixType& getcurrentMatrix();

};


#endif //GAMEOFLIFE_MATRIX_H
