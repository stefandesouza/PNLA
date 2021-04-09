/**
 * @file vector_seq.cpp
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Implementation of parallel vector routines
 * @version 0.1
 * @date 2021-03-18
 * 
 * @copyright Copyright (c) 2021
 *  
 */

#include <cmath>
#include <vector_parallel.h>

namespace pnla{
    
    void copyVector(parallelVector &Vector1, const parallelVector &Vector2){
                    #pragma omp parallel for schedule(static)
                    for (int i=0; i<Vector1.dimension; i++){
                        Vector1.values[i] = Vector2.values[i];
                    }
    }
                

    void scaleVector(parallelVector &givenVector, const double alpha){
                    #pragma omp parallel for schedule(static)
                    for (int i=0; i<givenVector.dimension; i++){
                        givenVector.values[i] *= alpha;
                    }
    }

    double dotProduct(const parallelVector &Vector1, const parallelVector &Vector2){
                    double sum = 0.0;
                    #pragma omp parallel for reduction(+: sum)
                    for (int i=0; i<Vector1.dimension; i++){
                        sum += Vector1.values[i]*Vector2.values[i];
                    }
                    return sum;
    }

    double norm(const parallelVector &Vector1){
                    return sqrt(dotProduct(Vector1,Vector1));
    }

    void scaledAddition(const parallelVector &Vector1, parallelVector &Vector2, const double alpha){
                    #pragma omp parallel for schedule(static)
                    for (int i=0; i<Vector1.dimension; i++){
                        Vector2.values[i] += alpha*Vector1.values[i];
                    }
                
    }

    void parallelVector::allocate(std::shared_ptr<double []> &pointer,const int dim){
                    pointer.reset(new double[dim]);
    }

} // end namespace pnla

