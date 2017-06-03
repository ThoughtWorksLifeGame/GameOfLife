//
// Created by Digong Jiang on 2017/6/3.
//

#include "gtest/gtest.h"
#include "../include/Matrix.h"
Matrix::MatrixType matrix = {
                {1,0,1,0,1},
                {0,1,0,1,0},
                {1,0,1,0,1},
                {0,1,0,1,0},
                {1,0,1,0,1},
        };
size_t dim = matrix.size();
TEST(matrix_test, AssignInitState_test)
{
    Matrix testMatrix(matrix.size());
    testMatrix.AssignInitState(matrix);
    const auto& innerMatrix= testMatrix.GetCurrentMatrix();
    for (int i=0; i<matrix.size();i++)
    {
        EXPECT_EQ(innerMatrix[i].size(),matrix[i].size());
        for (int j=0;j<matrix.size();j++)
            EXPECT_EQ(innerMatrix[i][j],matrix[i][j]);
    }
}

TEST(matrix_test, AssignInitStateDimNotEqualException)
{
    Matrix testMatrix(matrix.size() + 1);
    EXPECT_ANY_THROW(testMatrix.AssignInitState(matrix));
}

TEST(matrix_test, GetAliveCountTest)
{
    Matrix testMatrix(matrix.size());
    testMatrix.AssignInitState(matrix);
    testMatrix.prevMatrix = matrix;

    EXPECT_EQ(testMatrix.GetCountOfAliveCellsAround(4, 1), 3);
    EXPECT_EQ(testMatrix.GetCountOfAliveCellsAround(4, 0), 1);
    EXPECT_EQ(testMatrix.GetCountOfAliveCellsAround(2, 2), 4);
}
TEST(matrix_test,IsCoordLegal)
{
    Matrix testMatrix(matrix.size());
    testMatrix.AssignInitState(matrix);
    EXPECT_TRUE(testMatrix.IsCoordLegal(0,0));
    EXPECT_FALSE(testMatrix.IsCoordLegal(0,dim));
    EXPECT_FALSE(testMatrix.IsCoordLegal(dim, 0));
    EXPECT_FALSE(testMatrix.IsCoordLegal(dim, dim + 1));
    EXPECT_FALSE(testMatrix.IsCoordLegal(-1, -1));
}