/**
 * @file test_pcg.cpp
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Unit test for the pcg implementation
 * @version 0.1
 * @date 2021-03-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <limits> //epsilon()
#include <FD_linear_system.h>
#include <cmath>
#include <pcg.h>
#include <chrono>
using namespace std::chrono;


/**
 * @brief Tests my PCG implementation with sequential and parallel variants
 * 
 * @tparam Matrix
 * @param dimension 
 * @param epsilon 
 * @return int 
 */

template<typename Vector,typename Matrix>
int test_poisson(const int points, const double epsilon, const int maxIterations){
    FD_Linear_System linearSystem(points, 1.0/points); //Initializes a system with number of inner points = dimension
    std::vector<double> values;
    std::vector<int> col_indices;
    std::vector<int> row_indices;
    linearSystem.get_crs_matrix_vectors(values, col_indices, row_indices); //Creates the CRS matrix
    std::vector<double> b;
    linearSystem.get_b(b); //Stores the RHS b
    std::vector<double> x;
    linearSystem.get_x(x); //Stores the true solution x
 

    Vector rhsVector(b); //Stores the RHS to be used by the pcg function
    Vector xVector(points*points, 0.0); //Dummy vector to store the pcg solution
    Matrix crsMatrix(values, col_indices, row_indices); //Store the CRS matrix
    Vector xSolution(x); //Stores the true solution to test it against the pcg solution

    auto start = high_resolution_clock::now();
    int numberOfIterations = pnla::PCG(xVector, rhsVector, crsMatrix, epsilon, maxIterations);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);
    
    scaledAddition(xVector,xSolution,-1.0);
    scaleVectorMatrixMultiplication(rhsVector, xVector, crsMatrix, 1.0, -1.0);
    double finalResidue = norm(rhsVector);

    std::cout<<"The number of points is: "<<points<<std::endl;
    std::cout<<"The norm of Ax-b is: "<<finalResidue<<std::endl;
    std::cout<<"The number of iterations taken: "<< numberOfIterations <<std::endl;
    std::cout<<"The time taken in milliseconds: "<< duration.count() <<std::endl;

    if (finalResidue>pow(10,-10)){
        return 1;
    }
    return 0;

}


template<typename Vector,typename Matrix>
int test_pcg(const int points, const double epsilon, const int maxIterations)
{   
    int test_sucess = 0;

    test_sucess += test_poisson<Vector,Matrix>(points, epsilon, maxIterations);
    
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
    int maxIterations = 10000;

 	if(argc == 2)
	{
        dim = std::stoi(argv[1]);
	}

    if(argc == 3)
	{
        maxIterations = std::stoi(argv[2]);
	}

    const double epsilon(std::numeric_limits<double>::epsilon()); 
    
    int test_result_seq = 0;
    int test_result_parallel = 0;
    
    std::cout<<"Test PCG with sequential implementations"<<std::endl;
    test_result_seq = test_pcg<pnla::sequentialVector,pnla::sequentialMatrix>(dim, epsilon, maxIterations);


    if(test_result_seq !=0 )
        std::cout<< "The PCG implementation with sequential elements has failed!" <<std::endl;
    if(test_result_seq ==0 )
        std::cout<< "All sequential tests passed" <<std::endl;
    
    omp_set_num_threads(8);

    std::cout<<"Test PCG with parallel implementations"<<std::endl;
    test_result_parallel = test_pcg<pnla::parallelVector,pnla::parallelMatrix>(dim, epsilon, maxIterations);


    if(test_result_parallel !=0 )
        std::cout<< "The PCG implementation with parallel elements has failed!" <<std::endl;
    if(test_result_parallel ==0 )
        std::cout<< "All parallel tests passed" <<std::endl;
        
    return test_result_seq+test_result_parallel;
}