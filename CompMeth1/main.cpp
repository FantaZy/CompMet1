#include <stdio.h>
#include <ostream>
#include <cmath>
#include "Matrix.h"
#define FILENAME "results.dat"

double tmpfunc(double x)
{
	return 0.;
}

int main()
{
	Matrix mat(100., -40., 40.,5.);	
	//mat.saveToFile(mat.upwind_scheme(&Matrix::f0_analytical), FILENAME);
	//mat.saveToFile(mat.upwind_scheme(&Matrix::f0_num), FILENAME);
	//mat.saveToFile(mat.upwind_scheme(&Matrix::f1_analytical), FILENAME);
	//mat.saveToFile(mat.upwind_scheme(&Matrix::f1_num), FILENAME);
	mat.saveToFile(mat.central_scheme(&Matrix::f0_analytical), FILENAME);
	
	
	system("PAUSE");
	return 0;
}