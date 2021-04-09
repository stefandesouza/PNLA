
# Tests need to be added as executables first
add_executable(test_vectors test_vectors.cpp)
add_executable(test_matrix test_matrix.cpp)
add_executable(test_pcg test_pcg.cpp)


# Tells where headers of target are to be found
target_include_directories(test_vectors PUBLIC ../include)
target_include_directories(test_matrix PUBLIC ../include)
target_include_directories(test_matrix PUBLIC ../example)

# Links test_vectors against library pnla
target_link_libraries(test_vectors pnla)
target_link_libraries(test_matrix pnla)
target_link_libraries(test_pcg pnla)


### in what follows, we create a automated testing enviroment with cmake 

enable_testing()

### Test vectors
# Add a testing call of test_vectors with no arguments
add_test(NAME Test_vectors_default COMMAND test_vectors)
add_test(NAME Test_matrix_default COMMAND test_matrix)
add_test(NAME Test_pcg_default COMMAND test_pcg)

# Add a testing call of test_vectors with one argument
add_test(NAME Test_vectors_dim_10000 COMMAND test_vectors 10000) 
add_test(NAME Test_matrix_dim_100 COMMAND test_matrix 100) 
add_test(NAME Test_pcg_dim_100 COMMAND test_pcg 100) 

# Add a testing call of test_vectors with one argument
add_test(NAME Test_vectors_dim_40000 COMMAND test_vectors 40000) 
add_test(NAME Test_matrix_dim_200 COMMAND test_matrix 200) 
add_test(NAME Test_pcg_dim_200 COMMAND test_pcg 200) 

