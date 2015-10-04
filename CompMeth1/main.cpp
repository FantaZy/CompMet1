#include <stdio.h>
#include <ostream>
#include <cmath>
#include "Matrix.h"



int main()
{
	Matrix mat;
	//mat.upwind_scheme_F0();
	//mat.upwind_scheme_f0_analytic();
	mat.upwind_scheme_F1();
	//mat.upwind_scheme_f1_analytic();
	system("PAUSE");
	return 0;
}