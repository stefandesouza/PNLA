/**
 * @file test_matrix.cpp
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Unit test for the CRS matrix
 * @version 0.1
 * @date 2021-03-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <limits> //epsilon()
#include <matrix_seq.h>
#include <matrix_parallel.h>
#include <cmath>
#include <FD_linear_system.h>
#include <chrono>
using namespace std::chrono;

/**
 * @brief Tests my sequential and parallel implementations 
 * 
 * @tparam Matrix
 * @param dimension 
 * @param epsilon 
 * @return int 
 */

template<typename Vector,typename Matrix>
int test_scalarVectorMultiplication(const double epsilon, const int dimension){
   FD_Linear_System linearSystem(dimension, 1.0/dimension);
    std::vector<double> values;
    std::vector<int> col_indices;
    std::vector<int> row_indices;
    linearSystem.get_crs_matrix_vectors(values, col_indices, row_indices);

    std::vector<double> testVector;
    linearSystem.get_test_vector(testVector);


    
    
    Matrix crsMatrix(values, col_indices, row_indices);
    Vector rowSum(testVector);
    Vector unitVector(rowSum.dimension, 1.0);
    Vector zeroVector(rowSum.dimension, 0.0);


    auto start = high_resolution_clock::now();
    scaleVectorMatrixMultiplication(zeroVector, unitVector, crsMatrix, 1.0, 0.0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    std::cout<<"The time taken in microseconds: "<< duration.count() <<std::endl;

    if (abs(norm(rowSum)-norm(zeroVector))>epsilon){
        return 1;
    }
    
    
    return 0;
}



template<typename Vector,typename Matrix>
int test_matrix_routines(const int dimension, const double epsilon)
{   
    int test_sucess = 0;

    test_sucess += test_scalarVectorMultiplication<Vector,Matrix>(epsilon, dimension);

    return test_sucess;
}

/**
 * @brief Test Programm for pnla's matrix structs/classes
 * 
 * @param argc Number of arguments  
 * @param argv Programm argument list
 * @return int On sucess = 0, if return value != 0 some test failed
 */
int main(int argc, char *argv[])
{
    int dim = 10;

 	if(argc == 2)
	{
        dim = std::stoi(argv[1]);
	}


    const double epsilon(std::numeric_limits<double>::epsilon()); 
    int test_result_seq = 0;
    int test_result_parallel = 0;

    std::cout<<"Test Sequential Matrix"<<std::endl;
    test_result_seq = test_matrix_routines<pnla::sequentialVector,pnla::sequentialMatrix>(dim, epsilon);

    if(test_result_seq !=0 )
        std::cout<< "One or more sequential routines has failed!" <<std::endl;
    if(test_result_seq ==0 )
        std::cout<< "All sequential tests passed" <<std::endl;

    std::cout<<"Test Parallel Matrix"<<std::endl;
    test_result_parallel = test_matrix_routines<pnla::parallelVector,pnla::parallelMatrix>(dim, epsilon);

    if(test_result_parallel !=0 )
        std::cout<< "One or more parallel routines has failed!" <<std::endl;
    if(test_result_parallel ==0 )
        std::cout<< "All sequential tests passed" <<std::endl;

    return test_result_seq+test_result_parallel;
}