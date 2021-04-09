/**
 * @file matrix_parallel.cpp
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Implementation of parallel matrix routines
 * @version 0.1
 * @date 2021-03-18
 * 
 * @copyright Copyright (c) 2021
 *  
 */

#include <matrix_parallel.h>
#include <cmath>
#include <iostream>

namespace pnla{

    void scaleVectorMatrixMultiplication(parallelVector &Vector1, const parallelVector &Vector2, const parallelMatrix &Matrix, const double alpha, const double beta){
        
        parallelVector tempVector(Vector2.dimension,0.0);
        copyVector(tempVector, Vector2);
        scaleVector(Vector1, beta);
        scaleVector(tempVector, alpha);
        
        #pragma omp parallel for
        for (int i=0; i<Matrix.numberOfRows; i++){
            for (int j=Matrix.Rows[i]; j<Matrix.Rows[i+1]; j++){
                Vector1.values[i] += Matrix.Values[j]*tempVector.values[Matrix.Columns[j]] ;
            }
        }
    }

    void allocate(std::shared_ptr<double []> &pointer,const int dim){
        pointer.reset(new double[dim]);
    }

    void allocate(std::shared_ptr<int []> &pointer,const int dim){
        pointer.reset(new int[dim]);
    }          

    

} // end namespace pnla