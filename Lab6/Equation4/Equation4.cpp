// Equation4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EquationProcessor.h"

using namespace std;

void ReadCoefficients(vector<double> &coefficients)
{
	cout << "Enter coefficients: ";
	for (size_t i = 0; i < 5; ++i)
	{
		cin >> coefficients[i];
	}
	cout << endl;
}


int main()
{
	vector<double> coef = { 0, 0, 0, 0, 0 };
	ReadCoefficients(coef);
	try
	{
		Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
	}
	catch (const exception & ex)
	{
		cerr << ex.what() << endl;
	}


	return EXIT_SUCCESS;
}