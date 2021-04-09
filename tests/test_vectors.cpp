/**
 * @file test_vectors.cpp
 * @author Stefan de Souza (stefan.de-souza@uni-bayreuth.de)
 * @brief Test routines for vectors
 * @version 0.1
 * @date 2021-03-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <limits> //epsilon()
#include <vector_seq.h>
#include <vector_parallel.h>
#include <cmath>
#include <chrono> //Time measurements
using namespace std::chrono;



/**
 * @brief Tests my functions for the sequential and parallel vectors
 * 
 * @tparam Vector 
 * @param dimension 
 * @param epsilon 
 * @return int 
 */
/*
auto start = high_resolution_clock::now();
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop-start);
std::cout<<"The time taken in microseconds: "<< duration.count() <<std::endl;
*/

template<typename Vector>
int test_constantInitialization(const int dimension, const double epsilon){
    int randomNumber = rand() % 100;
   
    Vector vector1(dimension, randomNumber);
    std::vector<double> vector2(dimension, randomNumber);


    if (abs(pnla::norm(vector1)-randomNumber*sqrt(dimension))>epsilon){
        return 1;
    }
    return 0;
}

template<typename Vector>
int test_linearInitialization(const int dimension, const double epsilon){
   
    Vector vector1(dimension);


    for(int i = 0; i<dimension; i++){
        if(abs(vector1.values[i]-i)>epsilon){
            return 1;
        }
    }
    return 0;
}


template<typename Vector>
int test_vectorInitialization(const int dimension, const double epsilon){
    int randomNumber = rand() % 100;
    std::vector<double> vector2(dimension, randomNumber);
    
    Vector vector1(vector2);
    

    if (abs(pnla::norm(vector1)-randomNumber*sqrt(dimension))>epsilon){
        return 1;
    }
    return 0;
}

template<typename Vector>
int test_copyVector(const int dimension, const double epsilon){
    Vector vector1(dimension);
    std::vector<double> vector2(dimension, 1.0);
    
    pnla::copyVector(vector1,vector2);
    

    if (abs(pnla::norm(vector1)-sqrt(dimension))>epsilon){
        return 1;
    }
    return 0;
}

template<typename Vector>
int test_scaleVector(const int dimension, const double epsilon){
    int randomNumber = rand() % 100;
    Vector vector1(dimension, 1.0);
    
    pnla::scaleVector(vector1,randomNumber);
    

    if (abs(pnla::norm(vector1)-randomNumber*sqrt(dimension))>epsilon){
        return 1;
    }
    return 0;
}

template<typename Vector>
int test_dotProduct(const int dimension, const double epsilon){
    int randomNumber = rand() % 100;
    Vector vector1(dimension, 1.0);
    Vector vector2(dimension, randomNumber);
    
    double dot = pnla::dotProduct(vector1,vector2);
    

    if((dot - dimension*randomNumber)>epsilon){
        return 1;
    }
    return 0;

}

template<typename Vector>
int test_norm(const int dimension, const double epsilon){
    Vector vector1(dimension, 1.0);
    
    double norm = pnla::norm(vector1);
    
    
    if((norm - sqrt(dimension))>epsilon){
        return 1;
    }
    return 0;
}

template<typename Vector>
int test_scaledAddition(const int dimension, const double epsilon){
    int randomNumber = rand() % 100;
    Vector vector1(dimension, 0.0);
    Vector vector2(dimension, 1.0);
    
    pnla::scaledAddition(vector2, vector1, randomNumber);
    

    if (abs(pnla::norm(vector1)-randomNumber*sqrt(dimension))>epsilon){
        return 1;
    }
    return 0;
}

template<typename Vector>
int test_vector_routines(const int dimension, const double epsilon)
{   
    int test_sucess = 0;
    auto start = high_resolution_clock::now();

    // Initialization tests

    test_sucess += test_constantInitialization<Vector>(dimension, epsilon);
    test_sucess += test_linearInitialization<Vector>(dimension, epsilon);
    test_sucess += test_vectorInitialization<Vector>(dimension, epsilon);

    
    // Function tests
    
    test_sucess += test_copyVector<Vector>(dimension, epsilon);
    test_sucess += test_scaleVector<Vector>(dimension, epsilon);
    test_sucess += test_dotProduct<Vector>(dimension, epsilon);
    test_sucess += test_norm<Vector>(dimension, epsilon);
    test_sucess += test_scaledAddition<Vector>(dimension, epsilon);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    std::cout<<"The time taken in microseconds: "<< duration.count() <<std::endl;
 
    
    return test_sucess;
}

/**
 * @brief Test Programm for pnla's vector structs/classes
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
    omp_set_num_threads(8);

    const double epsilon(std::numeric_limits<double>::epsilon()); 
    int test_result_seq = 0;
    int test_result_parallel = 0;

    std::cout<<"Testing Sequential Vectors"<<std::endl;
    test_result_seq = test_vector_routines<pnla::sequentialVector>(dim, epsilon);

    if(test_result_seq !=0){
        std::cout<< "One or more of the sequential tests failed!" <<std::endl;
        return test_result_seq;
    }
    if(test_result_seq == 0){
        std::cout<< "All sequential tests passed" <<std::endl;;
    }

    std::cout<<"Testing Parallel Vectors"<<std::endl;
    test_result_parallel = test_vector_routines<pnla::parallelVector>(dim, epsilon);

    if(test_result_parallel !=0){
        std::cout<< "One or more of the parallel tests failed!" <<std::endl;
        return test_result_parallel;
    }

    if(test_result_seq == 0 && test_result_parallel == 0){
        std::cout<< "All parallel tests passed" <<std::endl;
        return test_result_parallel;
    }


}
