/**
 * @file vector_seq.cpp
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Implementation of sequential matrix routines
 * @version 0.1
 * @date 2021-03-18
 * 
 * @copyright Copyright (c) 2021
 *  
 */

#include <vector_seq.h>
#include <matrix_seq.h>
#include <cmath>

namespace pnla{
    
    void scaleVectorMatrixMultiplication(sequentialVector &Vector1, const sequentialVector &Vector2, const sequentialMatrix &Matrix, const double alpha, const double beta){
        sequentialVector tempVector;
        copyVector(tempVector, Vector2);
        scaleVector(Vector1, beta);
        scaleVector(tempVector, alpha);

        for (int i=0; i<Matrix.numberOfRows; i++){

            for (int j=Matrix.Rows[i]; j<Matrix.Rows[i+1]; j++){
                Vector1.values[i] += Matrix.Values[j]*tempVector.values[Matrix.Columns[j]] ;
            }
        }
    }            
} 