#include <stdio.h>
#include <ostream>
#include <cmath>
#include "Matrix.h"
#define FILENAME "results.txt"

double tmpfunc(double x)
{
	return 0.;
}

int main()
{
	Matrix mat;	
	mat.saveToFile(mat.upwind_scheme(&Matrix::f0_analytical), FILENAME);
	//mat.saveToFile(mat.upwind_scheme(&Matrix::f0_num), FILENAME);
	//mat.saveToFile(mat.upwind_scheme(&Matrix::f1_analytical), FILENAME);
	//mat.saveToFile(mat.upwind_scheme(&Matrix::f1_num), FILENAME);
	
	
	system("PAUSE");
	return 0;
}