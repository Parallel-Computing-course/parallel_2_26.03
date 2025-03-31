#include "matrix_mult.h"
#include <mpi.h>
#include <iostream>
#include <vector>

const int MatrixSize = 500;
const int DisplayElements = 5;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int processId, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &processId);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rowsEach = MatrixSize / size;
    std::vector<std::vector<int>> Matrix_1(MatrixSize, std::vector<int>(MatrixSize)),
                                  Matrix_2(MatrixSize, std::vector<int>(MatrixSize)),
                                  Result_Matrix(MatrixSize, std::vector<int>(MatrixSize, 0));

    if (processId == 0) {
        initializeMatrices(Matrix_1, Matrix_2, MatrixSize);
    }

    std::vector<int> localPartA(rowsEach * MatrixSize);
    MPI_Scatter(Matrix_1.data()->data(), rowsEach * MatrixSize, MPI_INT,
                localPartA.data(), rowsEach * MatrixSize, MPI_INT,
                0, MPI_COMM_WORLD);

    MPI_Bcast(Matrix_2.data()->data(), MatrixSize * MatrixSize, MPI_INT,
              0, MPI_COMM_WORLD);

    std::vector<int> localResult(rowsEach * MatrixSize, 0);
    computePartition(localPartA, Matrix_2, localResult, rowsEach, MatrixSize);

    MPI_Gather(localResult.data(), rowsEach * MatrixSize, MPI_INT,
              Result_Matrix.data()->data(), rowsEach * MatrixSize, MPI_INT,
              0, MPI_COMM_WORLD);

    double beginTime = MPI_Wtime();
    
    if (processId == 0) {
        printMatrixSection(Result_Matrix, DisplayElements);
        double finishTime = MPI_Wtime();
        std::cout << "Время выполнения: " << (finishTime - beginTime) << " s\n";
    }

    MPI_Finalize();
    return 0;
}