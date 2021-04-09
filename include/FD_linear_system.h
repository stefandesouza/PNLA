/**
 * @file FD_linear_system.h
 * @author Thomas Rau (thomas1.rau@uni-bayreuth.de)
 * @brief Header file for Finite Differences Linear System Class
 * @version 0.1
 * @date 2021-03-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __FD_LINEAR_SYSTEM_H__
#define __FD_LINEAR_SYSTEM_H__

#include <vector>
#include <cmath>

/**
 * @brief Class provides matrix resulting from finite difference discretization of
 *        2D Poisson's equation on a square. Resulting systems equals FE discretization
 *        if courants elements are used.
 */
class FD_Linear_System{

public:

    /// deletes default constructor 
    FD_Linear_System() = delete;

    /**
     * @brief Construct a new fd linear system object
     * 
     * @param N Number of inner points per dimension
     * @param h Stepsize or mesh width
     */
    FD_Linear_System(const int N, const double h):
    m_N(N), m_h(h),pi(3.14159265358979323846){};

    /**
     * @return Number of Degrees of freedom of system 
     */
    inline int get_dofs()const 
    {
        return m_N*m_N;
    };

    /**
     * @brief Get the crs matrix vectors 
     * 
     * @param[in] values arbitrary double vector 
     * @param[out] values holds non-zero entries of FD-System matrix 
     * @param[in] col_indices arbitrary int vector 
     * @param[out] col_indices holds column indices of non-zero elements
     * @param[in] row_indices arbitrary int vector 
     * @param[out] row_indices holds row indices of non-zero elements
     */
    //void get_crs_matrix_vectors(std::vector<double> &values,
                                //std::vector<int> &col_indices,
                                //std::vector<int> &row_indices)const;



    /**
     * @brief Get the test vector. Vector is the row sum of the matrix entries.
     *        Useful for testing your crs-matrix vector multiplication
     * 
     * @param[in] test_vector arbitrary double vector
     * @param[out] test_vector holds the row sum on matrix
     */
    //void get_test_vector(std::vector<double> &test_vector)const;

    /**
     * @brief Get the x vector of the FD linear system Ax = b
     * 
     * @param[in] x arbitrary double vector
     * @param[out] x holds the the solution of the system 
     */
    //void get_x(std::vector<double> &x)const;

    /**
     * @brief Gets the right hand side of FD system Ax = b
     * 
     * @param[in] b arbitrary double vector
     * @param[out] b holds the right hand side 
     */
    //void get_b(std::vector<double> &b)const;

    void get_crs_matrix_vectors(std::vector<double> &values,
                                              std::vector<int> &col_indices,
                                              std::vector<int> &row_indices) 
{
    const int nr_non_zero_entries(5*m_N*m_N - 4*m_N);
    const int dim = m_N * m_N;
    
    ///resize vectors
    values.resize(nr_non_zero_entries);
    col_indices.resize(nr_non_zero_entries);
    row_indices.resize(dim+1);    


    if(m_N == 1)
    {
        values[0] = 4.0;
        col_indices[0] = 0;
        row_indices[1] = 1;
    }
    else
    {
        int counter = 0;
        row_indices[0] = 0;

        /// for-loop over rows of Matrix
        for(int current_row = 0; current_row < dim; current_row++)
        {   
            if(current_row >=  m_N)
            {
                values[counter] = -1.0;
                col_indices[counter] = current_row - m_N;
                counter++;
            }

            if(current_row % m_N != 0)
            {
                values[counter] = -1.0;
                col_indices[counter] = current_row -1;
                counter++;
            }

            values[counter] = 4.0;
            col_indices[counter] = current_row;
            counter++;

            if(current_row % m_N != m_N-1)
            {
                values[counter] = -1.0;
                col_indices[counter] = current_row +1;
                counter++;
            }

            if(current_row < dim-m_N)
            {
                values[counter] = -1.0;
                col_indices[counter] = current_row + m_N;
                counter++;
            }

            row_indices[current_row+1] = counter;
        }
    }

}

void get_test_vector(std::vector<double> &test_vector) 
{
    if(m_N == 1)
    {
        test_vector.resize(1, 4.0);
    }
    else
    {
        test_vector.resize(m_N*m_N, 0.0);

        for(int i=0;i<m_N;i++)
        {
            test_vector[i*m_N] += 1.0;
            test_vector[(i+1)*m_N -1] += 1.0;
        }

        for(int i=0;i<m_N;i++)
        {
            test_vector[i] += 1.0;
            test_vector[(m_N-1)*m_N +i] += 1.0;
        }
    }
}

void get_x(std::vector<double> &x) 
{
    x.resize(m_N*m_N, 0.0);
    double x_1(0);
    double x_2(0);

    for(int i=0;i<m_N;i++)
    {
        for(int j=0; j<m_N;j++)
        {
            x_1 = m_h * static_cast<double>(j+1);
            x_2 = m_h * static_cast<double>(i+1);
            x[j+i*m_N] = sin(pi*x_1) * cos(0.5*pi*x_2); 
        }
    }
}

void get_b(std::vector<double> &b) 
{
    get_x(b);
    double coefficient = 1.25 * m_h*m_h * pi*pi;

    for(unsigned int i =0; i<b.size(); i++)
        b[i] *=  coefficient;

    //Add Boundary Condition
    double x = 0.0;
    for(int i=0;i<m_N;i++)
    {
        x = m_h * static_cast<double>(i+1);
        b[i] += sin(pi*x);
    }

}


private:

    /// Stores number of inner points per dimension
    const int m_N;

    /// Stores mesh size of discretization
    const double m_h;


    /// stores \f$ \pi \f$
    const double pi;

};

#endif // __FD_LINEAR_SYSTEM_H__