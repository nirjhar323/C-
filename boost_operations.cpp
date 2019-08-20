//Compile Command: g++ -g -std=c++11 -I c:/Users/Nirjhar/Downloads/boost_1_69_0 ODE.cpp -o ODE

//File containing implementations of various useful BOOST matrix/vector operations

#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/operations.hpp>

using namespace boost::numeric::ublas;

int main()

{
  typedef boost::numeric::ublas::matrix<double> matrix_type;
  typedef boost::numeric::ublas::vector<double> vector_type;

  matrix_type A(1,12);
  matrix_type B(12,12);

  std::cout << A.size2() << std::endl;

  
  for (int i = 0; i < A.size2(); i++)
     A(0,i) = i*2;


   std::cout << A(0,2) << std::endl;


   for (int i = 0; i < B.size1(); i++)
     for (int j = 0; j < B.size2(); j++)
       B(i,j) = 3*i;


  std::cout<< "B is \n" << B << std::endl;

  
  matrix_type C;

  C = trans(B);
  
  std::cout<< "C is \n" << C << std::endl;


  std::cout<< "A is \n" << A << std::endl;


  matrix_type D;

  D = prod(A,B);
  
  
  std::cout<< "D is \n" << D << std::endl;
  

  
  
}
