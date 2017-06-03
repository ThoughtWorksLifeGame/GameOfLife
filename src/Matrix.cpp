//
// Created by Digong Jiang on 2017/6/3.
//
#include "Matrix.h"

Matrix::Matrix(int n) : matrixDim(n)
{
    matrix.resize(n);
    for (auto &vec : matrix)
    {
        vec.resize(n);
    }
}

void Matrix::AssignInitState(const MatrixType &input)
{
    if (input.size() != matrixDim)
    {
        throw std::exception();
    }
    for (auto &vec : input)
    {
        if (vec.size() != matrixDim)
        {
            throw std::exception();
        }
    }
    matrix = input;
}

bool Matrix::IsCoordLegal(int x, int y)
{
    auto func = [this](int val)
    {
        return val >= 0 && val < matrixDim;
    };
    return func(x) && func(y);
}

int Matrix::GetCountOfAliveCellsAround(int x, int y)
{
    int aliveCellsAroundCount = 0;
    int off[] = {-1, 0, 1};
    for (auto xoff : off) {
        for (auto yoff : off)
        {
            int newx = x - xoff, newy = y - yoff;
            if ((xoff == 0 && yoff == 0) || !IsCoordLegal(newx, newy))
                continue;
            if (prevMatrix[newx][newy])
                aliveCellsAroundCount++;
        }
    }
    return aliveCellsAroundCount;
}

void Matrix::GenerateNextMatrix()
{
    std::vector<std::pair<int, int>> newAlives;
    for (int x = 0; x < matrixDim; x++)
    {
        for (int y = 0; y < matrixDim; y++)
        {
            int aliveCount = GetCountOfAliveCellsAround(x, y);

            bool aliveRes;

            if (aliveCount == 3)
            {
                aliveRes = true;
            } else if (aliveCount == 2)
            {
                aliveRes = prevMatrix[x][y];
            }
            else
            {
                aliveRes = false;
            }

            matrix[x][y] = aliveRes;
        }
    }
}

const Matrix::MatrixType &Matrix::GetNextMatrix()
{
    prevMatrix = matrix;
    Matrix::GenerateNextMatrix();
    return prevMatrix;
}

const Matrix::MatrixType &Matrix::getcurrentMatrix()
{
    return matrix;
}
