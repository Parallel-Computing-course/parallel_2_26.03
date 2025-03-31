#ifndef MATRIX_MULT_H
#define MATRIX_MULT_H

#include <vector>
#include <mpi.h>

void initializeMatrices(std::vector<std::vector<int>>& matrix_1, 
                       std::vector<std::vector<int>>& matrix_2, 
                       int matrixSize);
                       
void computePartition(const std::vector<int>& localPart,
                     const std::vector<std::vector<int>>& matrix_2,
                     std::vector<int>& resultPart,
                     int rowsCount,
                     int matrixSize);

void printMatrixSection(const std::vector<std::vector<int>>& matrix,
                       int displaySize);

#endif