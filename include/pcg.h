/**
 * @file pcg.h
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Implements the PCG iterative linear system solver
 * @version 0.1
 * @date 2021-03-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <vector_seq.h>
#include <matrix_seq.h>
#include <vector_parallel.h>
#include <matrix_parallel.h>

namespace pnla{

    /**
     * @brief Solves the linear system Ax=b using the PCG algorithm, and returns the number of iterations taken
     * 
     * @param xVector Dummy vector to hold the solution
     * @param rhsVector The vector b
     * @param crsMatrix The matrix A
     * @param epsilon The tolerance
     * @param maxIterations The maximum number of iterations allowed
     */

    template<typename Vector,typename Matrix>
    int PCG(Vector &xVector, const Vector &rhsVector, const Matrix &crsMatrix, const double epsilon, const int maxIterations);

} // end namespace pnla