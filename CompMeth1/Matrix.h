#include <iostream>
#include <cmath>
#include <array>
#include <functional>

class Matrix
{
private:
	typedef double(Matrix::*func_ptr)(double);
	func_ptr function_pointer;
	double points_numb = 100.0;
	double u = 1;
	double matrix;
	double dt;
	double dx = 80.0 / (100.-1.);
	
public:
	Matrix(int row, int col);
	Matrix();
	~Matrix();
	void calc_dx();
	double sign(double x);
	double f0_num(double x);
	double f1_num(double x);

	void upwind_scheme_F0();
	void upwind_scheme_F1(func_ptr func);
	double f0_analytical(double x, double t);
	double f1_analytical(double x, double t);
	void upwind_scheme_f0_analytic();
	void upwind_scheme_f1_analytic();
	
};