/**
 * @file vector_seq.cpp
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Implementation of pcg
 * @version 0.1
 * @date 2021-03-18
 * 
 * @copyright Copyright (c) 2021
 *  
 */

#include <pcg.h>
#include <cmath>

namespace pnla{
    
   template<typename Vector,typename Matrix>
    int PCG(Vector &xVector, const Vector &rhsVector, const Matrix &crsMatrix, const double epsilon, const int maxIterations){


        Vector residualVector(rhsVector.dimension, 0.0);
        Vector pVector(rhsVector.dimension, 0.0);
        Vector vVector(rhsVector.dimension, 0.0);
        Vector wVector(rhsVector.dimension, 0.0);
        copyVector(residualVector, rhsVector);
        copyVector(pVector, rhsVector);
        copyVector(vVector, rhsVector);

        double rho = dotProduct(vVector, residualVector);
        double alpha = 0.0;
        double gamma = 0.0;
        double error = epsilon*norm(rhsVector);
        int k = 0;


        while (k<maxIterations && norm(residualVector)>error){
            scaleVectorMatrixMultiplication(wVector, pVector, crsMatrix, 1.0, 0.0); //Performs w_k = Ap_k
            alpha = rho/dotProduct(pVector, wVector);
            
            scaledAddition(pVector, xVector, alpha); //Performs x_(k+1) = x_k + alpha_k*p_k
            scaledAddition(wVector, residualVector, -alpha); //Performs r_(k+1) = r_k - alpha_k*w_k
            copyVector(vVector, residualVector); //Placeholder for preconditioner application

            gamma = rho; //Stores the value of rho to calculate gamma later
            rho = dotProduct(vVector, residualVector); //Calculates new value of rho
            gamma = rho/gamma; //Performs gamma = rho_(k+1)/rho_k

            scaleVector(pVector, gamma);
            scaledAddition(vVector, pVector, 1.0); // Performs p_(k+1) = v_(k+1) + gamma_k*p_k
            
            k += 1;

        }
        return k;
    }
    
    template int PCG(parallelVector &xVector, const parallelVector &rhsVector, const parallelMatrix &crsMatrix, const double epsilon, const int maxIterations);
    template int PCG(sequentialVector &xVector, const sequentialVector &rhsVector, const sequentialMatrix &crsMatrix, const double epsilon, const int maxIterations);
    
} // end namespace pnla