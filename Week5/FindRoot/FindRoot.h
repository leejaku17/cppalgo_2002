#ifndef _FindRoot_h
#define _FindRoot_h

#include <float.h>
#include <math.h>
#include <stdio.h>

#include "../DiffInt/Differential.h"

// DBL_EPSILON = 2.2204460492503131e-016
#define TOLERANCE		(DBL_EPSILON*10)
#define MAX_TRY			1000

namespace cppalgo
{
	double FindRoot_Bisect(double (*f)(double), double x1, double x2)
	{
		if (f(x1)*f(x2) > 0.0) throw "ERR_INVALIDARG";

		double m;
		int ntry = 0;
		while (fabs(x1 - x2) > TOLERANCE) {
			m = (x1 + x2) / 2.0;
			if (f(x1)*f(m) <= 0.0) x2 = m;
			else x1 = m;
			ntry++;
		}
		printf("%d tries\n", ntry);
		return (x1 + x2) / 2.0;
	}

	double FindRoot_RF(double (*f)(double), double x1, double x2)
	{
		double xp;
		double div;
		if (f(x1)*f(x2) > 0.0) throw "ERR_INVALIDARG";
		int ntry = 0;

		do {
			div = f(x2) - f(x1);
			if (fabs(div) < TOLERANCE) throw "ERR_DIVIDEBYZERO";

			xp = x1 - f(x1)*(x2 - x1)/div;

			if (f(x1)*f(xp) < 0.0) x2 = xp;
			else if (f(xp) == 0.0) break;
			else x1 = xp;

			ntry++;
			if (ntry > MAX_TRY) throw "ERR_TOOMANYTRY";
		} while (fabs(f(xp)) > TOLERANCE);
		printf("%d tries\n", ntry);
		return xp;
	}

	double FindRoot_MRF(double (*f)(double), double x1, double x2)
	{
		if (f(x1)*f(x2) > 0.0) throw "ERR_INVALIDARG";

		double xp;
		double div;
		int ntry = 0;
		// c는 x1과 x2가 고정되었던 횟수 저장  c1, c2는 f(x1), f(x2)에서 나눌 값. 
		int c = 0, c1 = 1, c2 = 1;  									

		do {
			div = f(x2)/c2 - f(x1)/c1;
			if (fabs(div) < TOLERANCE) throw "ERR_DIVIDEBYZERO";

			xp = x1 - (f(x1)/c1)*(x2 - x1)/div;
			
			if (f(x1)*f(xp) < 0.0) {	// x2가 이동하는 경우 
				x2 = xp;
				if (c < 0) c = 0;   // 전에 x1이 이동했다면 clear
				else c++;     // 아니라면 그냥 증가 
			} else if (f(xp) == 0.0) {
				break;	// 근을 찾았음. 
			} else {
				x1 = xp;
				if (c > 0) c = 0;
				else c--;
			}

			if (c > 1) { 
				c1 *= 2; c2 = 1;
			} else if (c < -1) {
				c1 = 1; c2 *= 2;
			} else {
				c1 = 1; c2 = 1;
			}

			ntry++;
			if (ntry > MAX_TRY) throw "ERR_TOOMANYTRY";
		} while (fabs(f(xp)) > TOLERANCE);
		printf("%d tries\n", ntry);
		return xp;
	}

	double FindRoot_Secant(double (*f)(double), double x1, double x2)
	{
		double xp;
		double div;
		int ntry = 0;

		while (fabs(x1-x2) > TOLERANCE) {
			div = f(x2) - f(x1);
			if (fabs(div) < TOLERANCE) throw "ERR_DIVIDEBYZERO";

			xp = x1 - f(x1)*(x2 - x1)/div;
			x1 = x2;
			x2 = xp;
			
			ntry++;
			if (ntry > MAX_TRY) throw "ERR_TOOMANYTRY";
		}
		printf("%d tries\n", ntry);
		return xp;
	}

	double FindRoot_Newton(double (*f)(double), double (*df)(double), double x0)
	{
		double xp = x0;
		double div;
		int ntry = 0;

		do {
			x0 = xp;

			div = df(x0);
			if (fabs(div) < TOLERANCE) throw "ERR_DIVIDEBYZERO";
			xp = x0 - f(x0)/div;
			ntry++;
			if (ntry > MAX_TRY) throw "ERR_TOOMANYTRY";
		} while (fabs(x0 - xp) > TOLERANCE);

		printf("%d tries\n", ntry);
		return xp;
	}

	double FindRoot_Newton2(double (*f)(double), double x0)
	{
		double xp = x0;
		double div;
		int ntry = 0;

		do {
			x0 = xp;

			div = Differential_Oh4(f, x0);
			if (fabs(div) < TOLERANCE) throw "ERR_DIVIDEBYZERO";
			xp = x0 - f(x0)/div;
			ntry++;
			if (ntry > MAX_TRY) throw "ERR_TOOMANYTRY";
		} while (fabs(x0 - xp) > TOLERANCE);

		printf("%d tries\n", ntry);
		return xp;
	}
};

#endif