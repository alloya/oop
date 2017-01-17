#include "stdafx.h"
#include "EquationProcessor.h"
using namespace std;

EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	double temp = a;
	a = b / temp;
	b = c / temp;
	c = d / temp;
	d = e / temp;
	double p = b - 3 * a * a / 8;
	double q = a * a * a / 8 - a * b / 2 + c;
	double r = -3 * pow(a, 4) / 246 + a * a * b / 16 - c * a / 4 + d;
	double cubicResolventa = Solve3(-b, a * c - 4 * d, -a * a + 4 * b * d - c * c);
	//double A = sqrt(a * a / 4 - b + y);
	//double B = sqrt(y * y / 4 - d);
	return EquationRoot4();
}

EquationRoot2 Solve2(double a, double b, double c)
{
	EquationRoot2 equation;
	double D = b * b - 4. * a * c;
	if (D == 0)
	{
		equation.numRoots = 1;
		equation.roots[0] = equation.roots[1] = -b / (2 * a);
	}
	else if (D > 0)
	{
		equation.numRoots = 2;
		equation.roots[0] = (-b + sqrt(D)) / (2 * a);
		equation.roots[1] = (-b - sqrt(D)) / (2 * a);
	}
	else if (D < 0) 
	{
		equation.numRoots = 0;
	}
	return equation;
}
//http://www.resolventa.ru/spr/algebra/ferrary.htm
double Solve3(double a, double b, double c)
{
	array<double, 3> roots;
	double p = (3.0 * pow(a, 2) * c - pow(b, 2)) / (3.0 * pow(a, 2));
	double q = (2.0 * pow(a, 3) - 9.0 * a * b * c + 27.0 * d * pow(a, 2)) / (27.0 * pow(a, 3));
	double Q = pow(p / 3, 3) + pow(q / 2, 2);
	if (Q > 0)
	{
		double t = acos(q / sqrt(pow(p, 3))) / 3.0;
		roots[0] = -2 * sqrt(p) * cos(t) - a / 3.0;
		roots[1] = -2 * sqrt(p) * cos(t + 2 * M_PI / 3.0) - a / 3.0;
		roots[2] = -2 * sqrt(p) * cos(t - 2 * M_PI / 3.0) - a / 3.0;
	}
	else if (Q < 0)
	{
		if (p > 0)
		{
			double t = acosh(abs(q) / sqrt(pow(p, 3))) / 3.0;
			roots[0] = -2 * ((q > 0) ? 1 : ((q < 0) ? -1 : 0)) * sqrt(p) * cosh(t) - a / 3.0;
		}
		if (p < 0)
		{
			double t = asinh(abs(q) / sqrt(pow(abs(p), 3))) / 3.0;
			roots[0] = -2 * ((q > 0) ? 1 : ((q < 0) ? -1 : 0)) * sqrt(abs(p)) * sinh(t) - a / 3.0;
		}
		if (p == 0)
		{
			roots[0] = -pow((c - pow(a, 3) / 27), 1 / 3.0) - a / 3.0;
		}
	}
	else
	{
		roots[0] = -2 * ((q > 0) ? 1 : ((q < 0) ? -1 : 0)) * sqrt(p) - a / 3.0;
		roots[1] = ((q > 0) ? 1 : ((q < 0) ? -1 : 0)) * sqrt(p) - a / 3.0;
	}
	return *max_element(roots.begin(), roots.end());
}
