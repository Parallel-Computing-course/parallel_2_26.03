#include "matrix_mult.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void initializeMatrices(std::vector<std::vector<int>>& matrix_1,
                       std::vector<std::vector<int>>& matrix_2,
                       int matrixSize) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            matrix_1[i][j] = std::rand() % 10;
            matrix_2[i][j] = std::rand() % 10;
        }
    }
}

void computePartition(const std::vector<int>& localPart,
                     const std::vector<std::vector<int>>& matrix_2,
                     std::vector<int>& resultPart,
                     int rowsCount,
                     int matrixSize) {
    for (int i = 0; i < rowsCount; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            int sum = 0;
            for (int k = 0; k < matrixSize; ++k) {
                sum += localPart[i * matrixSize + k] * matrix_2[k][j];
            }
            resultPart[i * matrixSize + j] = sum;
        }
    }
}

void printMatrixSection(const std::vector<std::vector<int>>& matrix,
                       int displaySize) {
    for (int i = 0; i < displaySize; ++i) {
        for (int j = 0; j < displaySize; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}