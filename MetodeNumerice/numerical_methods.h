#ifndef NUMERICAL_METHODS_H
#define NUMERICAL_METHODS_H

#include"constants.h"
#include<math.h>
#include <string>
#include<error.h>
#include"Lepton_parser/Lepton.h"
#include "utilities.h"


double chio_method(double a[MAX_LINE][MAX_COL],int n);

bool gauss_method(double matrix[MAX_LINE][MAX_COL],int n,
                      double sol[MAX_LINE],double triangularMatrix[MAX_LINE][MAX_COL]);

bool lr_factorization(double matrix[MAX_LINE][MAX_COL],int n,double sol[MAX_LINE],
                  double lowerTriangularMatrix[MAX_LINE][MAX_COL]=nullptr,
                  double upperTriangularMatrix[MAX_LINE][MAX_COL]=nullptr);

bool jacobi_method(double m[MAX_LINE][MAX_COL],int n,int maxIterationNumber,
                   double precision,double initialSolution[MAX_LINE][MAX_COL],double solution[MAX_LINE],
                   int &iterationNumber);

bool seidel_gauss_method(double m[MAX_LINE][MAX_COL],int n,int maxIterationNumber,
                   double precision,double initialSolution[MAX_LINE][MAX_COL],double solution[MAX_LINE],
                   int &iterationNumber);

bool seidel_gauss_method(double m[MAX_LINE][MAX_COL],int n,int maxIterationNumber,
                   double precision,double initialSolution[MAX_LINE][MAX_COL],double solution[MAX_LINE],
                   int &iterationNumber);

bool krylov(double a[MAX_LINE][MAX_COL],double y[MAX_LINE][MAX_COL],int dim,double sol[MAX_LINE]);

bool fadeev(double m[MAX_LINE][MAX_COL],double invMatrix[MAX_LINE][MAX_COL],double coeff[MAX_LINE],int dim);

double lagrange_interpolation(double points[MAX_LINE][MAX_COL],int dim,double x_coord);

double newton_interpolation(double points[MAX_LINE][MAX_COL],int dim,double x_coord);

bool spline_interpolation(double points[MAX_LINE][MAX_COL],int dim,double x_coord,double &y_coord);

bool mas_method(std::string function,double initial_value,int it_max,double precison,double &final_value);

bool newton_approximation_method(std::string fct,std::string fct_der,double initial_value,
                                 int it_max,double precison,double &final_value);

double integral_trapezoidal_rule(double a,double b,double precison,std::string function);

double simpson_rule(double a,double b,double precison,std::string function);

double double_integration(double vertices[MAX_LINE][MAX_COL],std::string function);

bool euler_chauchy(double points[MAX_LINE][MAX_COL],int dim,std::string function,
                   double iteration,double precision,double initial_value,double calculus[MAX_LINE][2]);

bool runge_kutta(double points[MAX_LINE][MAX_COL],int dim,std::string function,
                   double iteration,double precision,double initial_value,double calculus[MAX_LINE][2]);

#endif // NUMERICAL_METHODS_H
