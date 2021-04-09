/**
 * @file vector_seq.h
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Declaration of the sequential vector class and routines
 * @version 0.1
 * @date 2021-03-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#pragma once
#include <vector>


namespace pnla{
 
    struct sequentialVector {
    
            int dimension;
            std::vector<double> values;

            sequentialVector(){
            }

            /**
             * @brief Construct a new sequential Vector object with linear values
             * 
             * @param dim 
             */
            sequentialVector(const int dim){
                dimension = dim;
                values = std::vector<double>(dimension);
                for (int i=0 ; i<dimension; i++){
                    values[i] = i;
                }
            }

            /**
             * @brief Construct a new constant sequential Vector object with a given value constantEntry
             * 
             * @param dim 
             * @param constantEntry 
             */
            sequentialVector(const int dim, const double constantEntry){
                dimension = dim;
                values = std::vector<double>(dimension);
                for (int i=0 ; i<dimension; i++){
                    values[i] = constantEntry;
                }
            }

            /**
             * @brief Construct a new sequential Vector object from a given std::vector object
             * 
             * @param y 
             */
            sequentialVector(const std::vector<double> &y){
                dimension = y.size();
                values = y;
            }
            
            

    };

            /**
             * @brief Copies the contents of 'Vector2' onto 'Vector1'
             * 
             * @param Vector1 
             * @param Vector2 
             */
            void copyVector(sequentialVector &Vector1, const sequentialVector &Vector2);

            /**
             * @brief Scales a given vector by a double 'alpha'
             * 
             * @param givenVector 
             * @param alpha 
             */
            void scaleVector(sequentialVector &givenVector, const double alpha);

            /**
             * @brief Calculates the dot product of 'Vector1' with 'Vector2'
             * 
             * @param Vector1 
             * @param Vector2 
             */
            double dotProduct(const sequentialVector &Vector1, const sequentialVector &Vector2);

            /**
             * @brief Finds the norm of a given vector
             * 
             * @param givenVector 
             */
            double norm(const sequentialVector &Vector1);

            /**
             * @brief Scales the 'Vector1' by a double 'alpha' and adds it to 'Vector2'
             * 
             * @param Vector1 
             * @param Vector2 
             * @param alpha 
             */
            void scaledAddition(const sequentialVector &Vector1, sequentialVector &Vector2, const double alpha);

}

