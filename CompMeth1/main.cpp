#include <stdio.h>
#include <ostream>
#include <cmath>
#include "Matrix.h"


double tmpfunc(double x)
{
	return 0.;
}

int main()
{
	Matrix mat;	
	mat.upwind_scheme(&Matrix::f0_analytical);
	mat.upwind_scheme(&Matrix::f0_num);
	mat.upwind_scheme(&Matrix::f1_analytical);
	mat.upwind_scheme(&Matrix::f1_num);
	
	
	system("PAUSE");
	return 0;
}