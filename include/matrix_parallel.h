/**
 * @file matrix_parallel.h
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Header file for storing the CRS matrix with parallel functionality
 * @version 0.1
 * @date 2021-03-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <vector_parallel.h>
#include <memory>
#include <utility>


namespace pnla{

    /**
     * @brief Declares allocators for double array references and int array references
     * 
     * @param pointer 
     * @param dim 
     */
    void allocate(std::shared_ptr<double []> &pointer,const int dim);
    void allocate(std::shared_ptr<int []> &pointer,const int dim);


    struct parallelMatrix {
        int numberOfRows;
        std::shared_ptr<double[]> Values;
        std::shared_ptr<int[]> Columns;
        std::shared_ptr<int[]> Rows;

        

        parallelMatrix(std::vector<double> matrixValues , std::vector<int> matrixColumns , std::vector<int> matrixRows ){
            numberOfRows = matrixRows.size()-1;
            pnla::allocate(Values,matrixValues.size());
            pnla::allocate(Columns,matrixColumns.size());
            pnla::allocate(Rows,matrixRows.size());

            #pragma omp parallel for schedule(static)
            for(unsigned int i = 0; i<matrixValues.size();i++){
                Values[i] = matrixValues[i];
            }
            #pragma omp parallel for schedule(static)
            for(unsigned int i = 0; i<matrixColumns.size();i++){
                Columns[i] = matrixColumns[i];
            }
            #pragma omp parallel for schedule(static)
            for(unsigned int i = 0; i<matrixRows.size();i++){
                Rows[i] = matrixRows[i];
            }
        }
    };

    /**
     * @brief Performs scalar vector multiplication on Vector1 with beta, add adds it to scaled vector matrix multiplication of Vector2 on Matrix with alpha
     * 
     * @param Vector1 
     * @param Vector2 
     * @param Matrix 
     * @param alpha 
     * @param beta 
     */
    void scaleVectorMatrixMultiplication(parallelVector &Vector1, const parallelVector &Vector2, const parallelMatrix &Matrix, const double alpha, const double beta);


    

}//end namespace pnla
