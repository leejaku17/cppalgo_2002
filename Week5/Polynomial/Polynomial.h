#ifndef _Polynomial_h
#define _Polynomial_h

#include "../SList/DList.h"
#include <stdio.h>	// for Print function

namespace cppalgo {
	class Polynomial
	{
	public:
		struct Term {
			int exp;
			double coef;
		};
		Polynomial() {}
		Polynomial(const Polynomial& p) { m_list = p.m_list; }
		const Polynomial& operator=(const Polynomial& p) { m_list = p.m_list; return *this; }

		void InsertTerm(int exp, double coef);
		void AddTerm(int exp, double coef);
		
		Polynomial operator+(const Polynomial& p);
		Polynomial operator-(const Polynomial& p);
		Polynomial operator*(const Polynomial& p);
		// 위엣것 외에도 많은 operator를 추가할 수 있을 것이다.
		// +=, -= 등등 

		void Differential();
		void Integral();
		double Evaluate(double x);

		void Lagrange(double pt[][2], int n);

		void Print();
	protected:
		double power(double x, int n);
		double combi(double pt[][2], int n, int r);
		DoubleList<Term> m_list;
	};

	void Polynomial::InsertTerm(int exp, double coef)
	{
		if (coef == 0.0) return;
		Term term;
		term.exp = exp; term.coef = coef;

		POS pos = m_list.GetHeadPosition();
		while (pos) {
			Term t = m_list.GetAt(pos);
			if (t.exp == term.exp) {
				m_list.GetAt(pos).coef = coef;
				return;
			}
			if (t.exp < term.exp) {
				m_list.InsertBefore(pos, term);
				return;
			}
			m_list.GetNext(pos);
		}
		m_list.AddTail(term);
	}

	void Polynomial::AddTerm(int exp, double coef)
	{
		Term term;
		term.exp = exp; term.coef = coef;

		POS pos = m_list.GetHeadPosition();
		while (pos) {
			Term t = m_list.GetAt(pos);
			if (t.exp == term.exp) {
				m_list.GetAt(pos).coef += coef;
				if (m_list.GetAt(pos).coef == 0.0) m_list.DeleteAt(pos);
				return;
			}
			if (t.exp < term.exp) {
				m_list.InsertBefore(pos, term);
				return;
			}
			m_list.GetNext(pos);
		}
		m_list.AddTail(term);
	}

	void Polynomial::Print()
	{
		POS pos = m_list.GetHeadPosition();
		while (pos) {
			Term t = m_list.GetNext(pos);
			printf("%+lgX%d ", t.coef, t.exp);
		}
		printf("\n");
	}

	Polynomial Polynomial::operator+(const Polynomial& p)
	{
		Polynomial r;

		POS pos1 = m_list.GetHeadPosition();
		POS pos2 = p.m_list.GetHeadPosition();

		Term t1, t2;

		while (pos1 && pos2) {
			t1 = m_list.GetAt(pos1);
			t2 = m_list.GetAt(pos2);
			
			if (t1.exp > t2.exp) {
				r.m_list.AddTail(t1);
				m_list.GetNext(pos1);
			} else if (t1.exp < t2.exp) {
				r.m_list.AddTail(t2);
				p.m_list.GetNext(pos2);
			} else {
				if (t1.coef + t2.coef != 0.0) {
					t1.coef += t2.coef;
					r.m_list.AddTail(t1);
				}
				m_list.GetNext(pos1);
				p.m_list.GetNext(pos2);
			}
		}

		while (pos1) {
			t1 = m_list.GetNext(pos1);
			r.m_list.AddTail(t1);
		}
		while (pos2) {
			t2 = p.m_list.GetNext(pos2);
			r.m_list.AddTail(t2);
		}
		return r;
	}

	Polynomial Polynomial::operator-(const Polynomial& p)
	{
		Polynomial r;

		POS pos1 = m_list.GetHeadPosition();
		POS pos2 = p.m_list.GetHeadPosition();

		Term t1, t2;

		while (pos1 && pos2) {
			t1 = m_list.GetAt(pos1);
			t2 = m_list.GetAt(pos2);
			
			if (t1.exp > t2.exp) {
				r.m_list.AddTail(t1);
				m_list.GetNext(pos1);
			} else if (t1.exp < t2.exp) {
				t2.coef = -t2.coef;
				r.m_list.AddTail(t2);
				p.m_list.GetNext(pos2);
			} else {
				if (t1.coef - t2.coef != 0.0) {
					t1.coef -= t2.coef;
					r.m_list.AddTail(t1);
				}
				m_list.GetNext(pos1);
				p.m_list.GetNext(pos2);
			}
		}

		while (pos1) {
			t1 = m_list.GetNext(pos1);
			r.m_list.AddTail(t1);
		}
		while (pos2) {
			t2.coef = -t2.coef;
			t2 = p.m_list.GetNext(pos2);
			r.m_list.AddTail(t2);
		}
		return r;
	}

	Polynomial Polynomial::operator*(const Polynomial& p)
	{
		Polynomial r;

		POS pos1 = m_list.GetHeadPosition();

		Term t1, t2;

		while (pos1) {
			t1 = m_list.GetNext(pos1);
			POS pos2 = p.m_list.GetHeadPosition();
			while (pos2) {
				t2 = p.m_list.GetNext(pos2);
				r.AddTerm(t1.exp + t2.exp, t1.coef * t2.coef);
			}
		}
		return r;
	}

	void Polynomial::Differential()
	{
		Polynomial r;
		POS pos = m_list.GetHeadPosition();
		while (pos) {
			Term t = m_list.GetNext(pos);
			if (t.exp > 0) 
				r.InsertTerm(t.exp - 1, t.coef * t.exp);			
		}
		*this = r;
	}

	void Polynomial::Integral()
	{
		Polynomial r;
		POS pos = m_list.GetHeadPosition();
		while (pos) {
			Term t = m_list.GetNext(pos);
			r.InsertTerm(t.exp + 1, t.coef / (t.exp + 1));
		}
		*this = r;
	}

	double Polynomial::Evaluate(double x)
	{
		double r = 0.0;
		POS pos = m_list.GetHeadPosition();
		while (pos) {
			Term t = m_list.GetNext(pos);
			r += t.coef * power(x, t.exp);
		}
		return r;	
	}
	
	double Polynomial::power(double x, int n)
	{
		if (n == 0) return 1.0;
		if (n == 1) return x;
		double half = power(x, n/2);
		if (n % 2 == 0)
			return half * half;
		else
			return half * half * x;		
	}

	void Polynomial::Lagrange(double pt[][2], int n)
	{
		int i, j;
		int sign;
		double coef;
		double temp;
		m_list.RemoveAll();

		for (i = 0; i < n; i++) {
			if (pt[i][1] == 0.0) continue;
			coef = pt[i][1];
			// 같은 점이 있는지 테스트, x좌표가 같은 두점이 있으면 구할 수 없음 
			for (j = 0; j < n; j++) {
				if (i == j) continue;
				if (pt[i][0] == pt[j][0]) {
					m_list.RemoveAll();
					return;
				}
				coef /= pt[i][0] - pt[j][0];
			}
			// Pi를 구하기 위해 임시로 Xi를 0으로 둠 
			temp = pt[i][0];
			pt[i][0] = 0;
			for (j = 0; j < n; j++) {
				if (j % 2) sign = -1;
				else sign = 1;
				AddTerm(n - j - 1, sign * coef * combi(pt, n, j));
			}
			pt[i][0] = temp;
		}
	}

	double Polynomial::combi(double pt[][2], int n, int r)
	{
		double result = 1.0;
		if (n <= 0 || r < 0 || n < r) return 0;
		if (n == r) {
			for (int i = 0; i < n; i++) result *= pt[i][0];
			return result;
		}
		if (r == 0) return 1.0;
		else return pt[n-1][0] * combi(pt, n-1, r-1) + combi(pt, n-1, r);
	}
};

#endif