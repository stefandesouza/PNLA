/**
 * @file CRS_seq.h
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Header file for storing the CRS matrix
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
#include <vector_seq.h>


namespace pnla{

    struct sequentialMatrix {
        int numberOfRows;
        std::vector<double> Values;
        std::vector<int> Columns;
        std::vector<int> Rows;

        sequentialMatrix(std::vector<double> matrixValues , std::vector<int> matrixColumns , std::vector<int> matrixRows ){
            Values = matrixValues;
            Columns = matrixColumns;
            Rows = matrixRows;
            numberOfRows = matrixRows.size()-1;
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
    void scaleVectorMatrixMultiplication(sequentialVector &Vector1, const sequentialVector &Vector2, const sequentialMatrix &Matrix, const double alpha, const double beta);

}
