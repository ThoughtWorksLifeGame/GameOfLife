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
    Matrix(int n = 10) : matrixDim(n)
    {
        matrix.resize(n);
        for (auto& vec : matrix)
        {
            vec.resize(n);
        }
    }

    void AssignInitState(const MatrixType& input)
    {
        if (input.size() != matrixDim)
        {
            throw std::exception();
        }
        for (auto& vec : input)
        {
            if (vec.size() != matrixDim)
            {
                throw std::exception();
            }
        }
        matrix = input;
    }

    bool IsCoordLegal(int x, int y)
    {
        auto func = [this](int val) {
            return val >= 0 && val < matrixDim;
        };
        return func(x) && func(y);
    }

    int GetCountOfAliveCellsAround(int x, int y)
    {
        int aliveCellsAroundCount = 0;
        int off[] = {-1, 0, 1};
        for (auto xoff : off)
        {
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

    void GetNetMatrixByAliveCells()
    {
        for (auto& aliveCell : aliveCells)
        {
            int x = aliveCell.first, y = aliveCell.second;
            int aliveCount = GetCountOfAliveCellsAround(x, y);

            bool aliveRes;

            if (aliveCount == 3)
            {
                aliveRes = true;
            }
            else if (aliveCount == 2)
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

    const MatrixType& GetNextMatrix()
    {
        prevMatrix = matrix;
        GetNetMatrixByAliveCells();
        return prevMatrix;
    }
    const MatrixType& getcurrentMatrix()
    {
        return matrix;
    }
};


#endif //GAMEOFLIFE_MATRIX_H
