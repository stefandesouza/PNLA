/**
 * @file vector_seq.h
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Declaration of the parallel vector class and routines
 * @version 0.1
 * @date 2021-03-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#pragma once
#include <vector>
#include <omp.h>
#include <memory>
#include <utility>



namespace pnla{

    struct parallelVector {
    
            int dimension;
            std::unique_ptr<double[]> values;
            
            /**
             * @brief Allocares memory to the pointer
             * 
             * @param pointer 
             * @param dim 
             */
            void allocate(std::unique_ptr<double []> &pointer, const int dim); //Declaring the allocate function

            parallelVector(){
            }
            /**
             * @brief Construct a new parallel Vector object with linear values
             * 
             * @param dim 
             */
            parallelVector(const int dim){
                dimension = dim;
                allocate(values,dimension);
            
                #pragma omp parallel for schedule(static)
                for (int i=0; i < dimension;i++)
                {
                    values[i] = i;
                }

            }

            /**
             * @brief Construct a new constant parallel Vector object with a given value constantEntry
             * 
             * @param dim 
             * @param constantEntry 
             */
            parallelVector(const int dim, const double constantEntry){
                dimension = dim;
                allocate(values,dimension);

                #pragma omp parallel for schedule(static)
                for (int i=0 ; i<dimension; i++)
                {
                    values[i] = constantEntry;
                }
            }

            /**
             * @brief Construct a new parallel Vector object from a given std::vector object
             * 
             * @param y 
             */
            parallelVector(const std::vector<double> &y){
                dimension = y.size();
                allocate(values,dimension);
            
                #pragma omp parallel for schedule(static)
                for (int i=0; i<dimension; i++)
                {
                    values[i] = y[i];
                }
            }
            
            

    };

            /**
             * @brief Copies the contents of 'Vector2' onto 'Vector1'
             * 
             * @param Vector1 
             * @param Vector2 
             */
            void copyVector(parallelVector &Vector1, const parallelVector &Vector2);

            /**
             * @brief Scales a given vector by a double 'alpha'
             * 
             * @param givenVector 
             * @param alpha 
             */
            void scaleVector(parallelVector &givenVector, const double alpha);

            /**
             * @brief Calculates the dot product of 'Vector1' with 'Vector2'
             * 
             * @param Vector1 
             * @param Vector2 
             */
            double dotProduct(const parallelVector &Vector1, const parallelVector &Vector2);

            /**
             * @brief Finds the norm of a given vector
             * 
             * @param givenVector 
             */
            double norm(const parallelVector &Vector1);

            /**
             * @brief Scales the 'Vector1' by a double 'alpha' and adds it to 'Vector2'
             * 
             * @param Vector1 
             * @param Vector2 
             * @param alpha 
             */
            void scaledAddition(const parallelVector &Vector1, parallelVector &Vector2, const double alpha);

            /**
             * @brief Allocates memory to the empty container 
             * 
             * @param pointer 
             * @param dim 
             */
            

}//end namespace pnla