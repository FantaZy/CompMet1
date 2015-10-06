#include "Matrix.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <functional>
#define TIME 5.0


Matrix::Matrix()
{
	this->setDt();
}
Matrix::Matrix(double points_numb, double x_min, double x_max, double time)
{
	this->setDt();
	this->setTime(time);
	this->setPointsNumber(points_numb);
	this->setVectorSize(this->points_numb);
	this->setRange(x_min, x_max);

}
void Matrix::setVectorSize(double size)
{
	std::vector<double> tmp(size);
	this->matrix = tmp;
}
Matrix::~Matrix()
{

}
void Matrix::setDt()
{
	this->dt = 0.5*(dx / u);
	if ((dt / dx) >= 1.0)
	{
		std::cout << "dt: " << dt << " is lower than dx/u - solution may be not stable." << std::endl;
	}
}
void Matrix::setTime(double time)
{
	this->time = time;
}

void Matrix::setPointsNumber(double points_numb)
{
	this->points_numb = points_numb;
}
void Matrix::setRange(double min, double max)
{
	this->x_min = min;
	this->x_max = max;
}
double Matrix::sign(double x)
{
	double res;
	if (x == 0.)
	{
		return 0.0;
	}
	res = abs(x) / x;
	return res;
}
double Matrix::f0_num(double x, double nothing )
{	
	if ( ( (x > -40.0) && (x < 40.0) ) )
	{
		double result = (1.0 / 2.0)*((sign(x) + 1.0));
		std::cout << result << " " << std::endl;
		return result;
	}else 
	
	if ( (x == -40.0)  )
	{
		return 0.0;
	}else 
	
	if ( (x == 40.0)  )
	{
		return 1.0;
	}else
	return 0.;	
}
double Matrix::f1_num(double x, double nothing)
{
	if (((x > -40.0) && (x < 40.0)))
	{
		double tmp = x*x*(-1.0);
		double result = (1. / 2.)*(exp(tmp));
		std::cout << result << " " << std::endl;
		return result;
	}
	else

	if ((x == -40.0))
	{
		return 0.0;
	}
	else

	if ((x == 40.0))
	{
		return 1.0;
	}
	else
		return 0.;
}
double Matrix::f0_analytical(double x, double t)
{
	double result = 0;
	result = (1. / 2.)*(sign(x - t) + 1.);
	return result;
}
double Matrix::f1_analytical(double x, double t)
{
	double result = 0;
	result = (1. / 2.)*exp(-((x - t)*(x - t)));
	return result;
}

std::vector<double>  Matrix::upwind_scheme(func_ptr func)
{
	std::vector<double> tmpArr(this->points_numb);
	double x = this->x_min;	
	this->function_pointer = func;

	std::cout << "tmpArr is calculating \n" << std::endl;
	for (int i = 0; i < this->points_numb; i++)
	{
		tmpArr[i] = (this->*function_pointer)(x,0);
		x = (this->x_min) + i * dx;
	}
	std::cout << (dt / dx) << std::endl;
	this->matrix = tmpArr;
	for (double time = 1; time <= this->time; time += dt)
	{
		std::cout << "nxtArr is calculating \n" << std::endl;
		x = this->x_min + dx;

		for (int i = 1; i < this->points_numb; i++)
		{
			x = (this->x_min) + i * dx;
			this->matrix[i] = tmpArr[i] - (dt / dx)*(tmpArr[i] - tmpArr[i - 1]);
			std::cout << this->matrix[i] << " ";
		}
		x = this->x_min;
		tmpArr = this->matrix;
	}
	return this->matrix;

}

void Matrix::saveToFile(std::vector<double> arr, std::string filename)
{
	//save results to file
	std::ofstream file;
	file.open(filename);
	for (int i = 0; i < this->points_numb; i++)
	{
		file << i << " " << arr[i] << std::endl;
	}
	file.close();
}

std::vector<double> Matrix::central_scheme(func_ptr func)
{
	std::vector<double> tmpArr(this->points_numb);	
	double x = this->x_min;
	this->function_pointer = func;

	std::cout << "tmpArr is calculating \n" << std::endl;
	for (int i = 0; i < this->points_numb; i++)
	{
		tmpArr[i] = (this->*function_pointer)(x, 0);
		x = (this->x_min) + i * dx; //avoid increasing error by addind dx in each iteration
	}
	std::cout << (dt / dx) << std::endl;

	
	this->matrix = tmpArr;
	for (double time = 1; time <= this->time; time += dt)
	{
		std::cout << "nxtArr is calculating \n" << std::endl;
		x = this->x_min + dx;

		for (int i = 1; i < this->points_numb-1; i++)
		{
			x = (this->x_min) + i * dx;
			this->matrix[i] = tmpArr[i] - (dt / (2*dx))*(tmpArr[i+1] - tmpArr[i - 1]);
			std::cout << this->matrix[i] << " ";
		}
		x = this->x_min;		
		tmpArr = this->matrix;

	}
	return this->matrix;
}

std::vector<double> Matrix::lax_friedrichs(func_ptr func)
{
	std::vector<double> tmpArr(this->points_numb);
	double x = this->x_min;
	this->function_pointer = func;

	std::cout << "tmpArr is calculating \n" << std::endl;
	for (int i = 0; i < this->points_numb; i++)
	{
		tmpArr[i] = (this->*function_pointer)(x, 0);
		x = (this->x_min) + i * dx; //avoid increasing error by addind dx in each iteration
	}
	std::cout << (dt / dx) << std::endl;


	this->matrix = tmpArr;
	for (double time = 1; time <= this->time; time += dt)
	{
		std::cout << "nxtArr is calculating \n" << std::endl;
		x = this->x_min + dx;

		for (int i = 1; i < this->points_numb - 1; i++)
		{
			x = (this->x_min) + i * dx;
			this->matrix[i] = ((tmpArr[i + 1] + tmpArr[i - 1]) / 2.) - (dt / (2 * dx))*(tmpArr[i + 1] - tmpArr[i - 1]);

			std::cout << this->matrix[i] << " ";
		}
		x = this->x_min;
		tmpArr = this->matrix;

	}
	return this->matrix;
}