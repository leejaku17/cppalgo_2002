#include "FindRoot.h"
#include <stdio.h>

using namespace cppalgo;

double xtriple(double x) 
{
	return x*x*x - 1;
}

double d_xtriple(double x)
{
	return 3*x*x;
}

double inverse(double x)
{
	return 1.0/x;
}

void main(void)
{
	printf("Root of f(x) = x^3 - 1\n");

	try {
		printf("Bisection Method = %lg\n", FindRoot_Bisect(xtriple, -1.5, 4.5));
	} catch (const char* err) {
		printf("Error : %s\n", err);
	}

	try {
		printf("Regular Falsi Method = %lg\n", FindRoot_RF(xtriple, -1.5, 4.5));
	} catch (const char* err) {
		printf("Error : %s\n", err);
	}

	try {
		printf("Modified Regular Falsi Method = %lg\n", FindRoot_MRF(xtriple, -1.5, 4.5));
	} catch (const char* err) {
		printf("Error : %s\n", err);
	}

	try {
		printf("Secant Method = %lg\n", FindRoot_Secant(xtriple, -1.5, 4.5));
	} catch (const char* err) {
		printf("Error : %s\n", err);
	}

	try {
		printf("Secant Method = %lg\n", FindRoot_Secant(xtriple, 4.5, 10.0));
	} catch (const char* err) {
		printf("Error : %s\n", err);
	}

	try {
		printf("Newton Method = %lg\n", FindRoot_Newton(xtriple, d_xtriple, 4.5));
	} catch (const char* err) {
		printf("Error : %s\n", err);
	}

	try {
		printf("Newton Method2 = %lg\n", FindRoot_Newton2(xtriple, 4.5));
	} catch (const char* err) {
		printf("Error : %s\n", err);
	}
}