#ifndef _Power_h
#define _Power_h

#include "../Search/RBTreeMap.h"

namespace cppalgo
{
	double power_simple(double x, int n)
	{
		double r = 1.0;
		while (n--) {
			r *= x;
		}
		return r;
	}

	double power_recur(double x, int n)
	{
		if (n == 0) return 1.0;
		return x * power_recur(x, n - 1);
	}

	double power_dnq(double x, int n)
	{
		if (n == 0) return 1.0;
		if (n == 1) return x;
		double half = power_dnq(x, n/2);
		if (n % 2 == 0)
			return half * half;
		else
			return half * half * x;
	}

	struct PowerTerm {
		int n;
		double power;
		bool operator==(const PowerTerm& pt) const { return n == pt.n; }
		bool operator>(const PowerTerm& pt) const { return n > pt.n; }
	};

	double power_dynamic_sub(double x, int n, RBTreeMap<PowerTerm>& map)
	{
		if (n == 0) return 1.0;
		PowerTerm pt;
		pt.n = n/2;
		PowerTerm rpt;
		
		double half;
		if (map.Find(pt, rpt)) {
			half = rpt.power;
		} else {
			half = power_dynamic_sub(x, n/2, map);
			rpt.n = n/2; rpt.power = half;
			map.Insert(rpt);
		}
		if (n % 2 == 0) return half*half;
		else return half*half*x;
	}

	double power_dynamic(double x, int n)
	{
		RBTreeMap<PowerTerm> map;
		return power_dynamic_sub(x, n, map);
	}
};

#endif