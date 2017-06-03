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
#include <ostream>
#include <istream>


class Matrix {
public:
    typedef std::vector<std::vector<bool>> MatrixType;
private:
    void GenerateNextMatrix();
    int matrixDim;
    MatrixType matrix, prevMatrix;
    bool IsCoordLegal(int x, int y);
    int GetCountOfAliveCellsAround(int x, int y);
public:
    Matrix(int n);

    void AssignInitState(const MatrixType &input);

    void GetNextMatrix();

    const MatrixType &GetCurrentMatrix();

    bool operator==(const Matrix& mat);
    bool operator!=(const Matrix& mat);
    static void Export(const MatrixType& matrix, std::ostream& os);
    static MatrixType Import(std::istream& os);
};


#endif //GAMEOFLIFE_MATRIX_H
