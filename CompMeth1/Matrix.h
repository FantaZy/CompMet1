#include <iostream>
#include <cmath>
#include <array>
#include <functional>
#include <vector>


class Matrix
{
private:
	typedef double(Matrix::*func_ptr)(double, double);
	func_ptr function_pointer;
	double points_numb;
	double u = 1;
	double x_min;
	double x_max;
	std::vector<double> matrix;
	double dt;
	double time;
	double dx = 80.0 / (100.-1.);
	double sign(double x);
	void calc_dx();
	
	
	
public:
	Matrix();
	Matrix(double points_numb, double x_min, double x_max, double time);
	~Matrix();

	void setVectorSize(double size);
	void setDt();
	void setTime(double time);
	void setPointsNumber(double points_numb);
	void saveToFile(std::vector<double> arr, std::string filename);
	void setRange(double min, double max);
	double f0_num(double x, double nothing = 0);
	double f1_num(double x, double nothing = 0);	
	double f0_analytical(double x, double t);
	double f1_analytical(double x, double t);
	std::vector<double>  upwind_scheme(func_ptr func);
	std::vector<double> central_scheme(func_ptr func);
	std::vector<double> lax_friedrichs(func_ptr func);

	
};