/**
 * @file vector_seq.cpp
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Implementation of sequential vector routines
 * @version 0.1
 * @date 2021-03-18
 * 
 * @copyright Copyright (c) 2021
 *  
 */

#include <vector_seq.h>
#include <cmath>

namespace pnla{
    
    void copyVector(sequentialVector &Vector1, const sequentialVector &Vector2){
                    Vector1 = Vector2;
                }
                

    void scaleVector(sequentialVector &givenVector, const double alpha){
        for (int i=0; i<givenVector.dimension; i++){
            givenVector.values[i] *= alpha;
        }
    }

    double dotProduct(const sequentialVector &Vector1, const sequentialVector &Vector2){
                double sum = 0.0;
                for (int i=0; i<Vector1.dimension; i++){
                    sum += Vector1.values[i]*Vector2.values[i];
                }
                return sum;
    }

    double norm(const sequentialVector &Vector1){
                return sqrt(dotProduct(Vector1,Vector1));
    }

    void scaledAddition(const sequentialVector &Vector1, sequentialVector &Vector2, const double alpha){
                for (int i=0; i<Vector1.dimension; i++){
                    Vector2.values[i] += alpha*Vector1.values[i];
                }      
    }
} 

