#include <iostream>
#include <cmath>
#include <array>
#include <functional>


class Matrix
{
private:
	typedef double(Matrix::*func_ptr)(double, double);
	func_ptr function_pointer;
	double points_numb = 100.0;
	double u = 1;
	double matrix[100];
	double dt;
	double dx = 80.0 / (100.-1.);
	double sign(double x);
	void calc_dx();
	
	
	
public:
	Matrix();
	~Matrix();
	
	void saveToFile(double* arr, std::string filename);
	double f0_num(double x, double nothing = 0);
	double f1_num(double x, double nothing = 0);

	double* upwind_scheme(func_ptr func);
	double f0_analytical(double x, double t);
	double f1_analytical(double x, double t);

	
};