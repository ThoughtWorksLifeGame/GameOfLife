//
// Created by Digong Jiang on 2017/6/3.
//
#include "Matrix.h"

Matrix::Matrix(int n) : matrixDim(n) {
    matrix.resize(n);
    for (auto &vec : matrix) {
        vec.resize(n);
    }
}

void Matrix::AssignInitState(const MatrixType &input) {
    if (input.size() != (size_t)matrixDim) {
        throw std::exception();
    }
    for (auto &vec : input) {
        if (vec.size() != (size_t)matrixDim) {
            throw std::exception();
        }
    }
    matrix = input;
}

bool Matrix::IsCoordLegal(int x, int y) {
    auto func = [this](int val) {
        return val >= 0 && val < matrixDim;
    };
    return func(x) && func(y);
}

int Matrix::GetCountOfAliveCellsAround(int x, int y) {
    int aliveCellsAroundCount = 0;
    int off[] = {-1, 0, 1};
    for (auto xoff : off) {
        for (auto yoff : off) {
            int newx = x - xoff, newy = y - yoff;
            if ((xoff == 0 && yoff == 0) || !IsCoordLegal(newx, newy))
                continue;
            if (prevMatrix[newx][newy])
                aliveCellsAroundCount++;
        }
    }
    return aliveCellsAroundCount;
}

void Matrix::GenerateNextMatrix() {
    std::vector<std::pair<int, int>> newAlives;
    for (int x = 0; x < matrixDim; x++) {
        for (int y = 0; y < matrixDim; y++) {
            int aliveCount = GetCountOfAliveCellsAround(x, y);

            bool aliveRes;

            if (aliveCount == 3) {
                aliveRes = true;
            } else if (aliveCount == 2) {
                aliveRes = prevMatrix[x][y];
            } else {
                aliveRes = false;
            }

            matrix[x][y] = aliveRes;
        }
    }
}

void Matrix::GetNextMatrix() {
    prevMatrix = matrix;
    Matrix::GenerateNextMatrix();
}

const Matrix::MatrixType &Matrix::GetCurrentMatrix() {
    return matrix;
}

bool Matrix::operator==(const Matrix &mat) {
    for (int x = 0; x < matrixDim; x++)
        for (int y = 0; y < matrixDim; y++)
        {
            if (mat.matrix[x][y] != this->matrix[x][y])
                return false;
        }
    return true;
}

bool Matrix::operator!=(const Matrix &mat) {
    return !(*this == mat);
}

void Matrix::Export(const Matrix::MatrixType &matrix, std::ostream& os) {
    os << matrix.size() << std::endl;
    for (size_t x = 0; x < matrix.size(); x++)
    {
        for (size_t y = 0; y < matrix.size(); y++)
        {
            os << matrix[x][y] << ' ';
        }
        os << std::endl;
    }
}

Matrix::MatrixType Matrix::Import(std::istream &os) {
    size_t dim;
    os >> dim;
    MatrixType matrix(dim, std::vector<bool>(dim));
    for (size_t x = 0; x < dim; x++)
    {
        for (size_t y = 0; y < dim; y++)
        {
            int val;
            os >> val;
            matrix[x][y] = (bool)val;
        }
    }
    return matrix;
}
