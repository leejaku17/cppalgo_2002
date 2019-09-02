#ifndef _SparseMatrix_h
#define _SparseMatrix_h

#include "../Search/RBTreeMap.h"
#include <stdio.h>
#include <float.h>
#include <math.h>

namespace cppalgo 
{
	class SparseMatrix 
	{
	public:
		enum Exception {
			ERR_INVALID_SIZE,
			ERR_OUT_OF_MEMORY,
			ERR_INVALID_RANGE,
			ERR_SIZE_MISMATCH,
			ERR_SINGULAR,
			ERR_MUSTSQUARE
		};
	public:
		SparseMatrix(int rsize, int csize);
		~SparseMatrix();

		SparseMatrix(const SparseMatrix& m);
		const SparseMatrix& operator=(const SparseMatrix& m);

		double A(int r, int c) const;
		void Set(int r, int c, double v);
		int GetRow() const { return m_nRow; }
		int GetCol() const { return m_nCol; }
		void Print() const;
		bool IsSquare() const { return m_nCol == m_nRow; }

		bool ExchangeRow(int r1, int r2);

		SparseMatrix operator+(const SparseMatrix& m) const;
		SparseMatrix operator-(const SparseMatrix& m) const;
		SparseMatrix operator*(const SparseMatrix& m) const;

		double Determinant() const;
		SparseMatrix Solve(SparseMatrix Y);
		SparseMatrix Inverse() const;

	protected:
		int m_nRow;
		int m_nCol;
		
		struct MatrixElem {
			int row;
			int col;
			double value;
			MatrixElem() { row = col = 0; value = 0.0; }
			bool operator==(const MatrixElem& e) const {
				if (row == e.row && col == e.col) return true;
				else return false;
			}
			bool operator>(const MatrixElem& e) const {
				if (row > e.row) return true;
				else if (row == e.row && col > e.col) return true;
				else return false;
			}
		};
		RBTreeMap<MatrixElem> m_mapElem;
	};

	SparseMatrix::SparseMatrix(int rsize, int csize)
	{
		if (rsize <= 0 || csize <= 0) throw ERR_INVALID_SIZE;
		m_nRow = rsize;
		m_nCol = csize;
	}

	SparseMatrix::~SparseMatrix()
	{
	}

	SparseMatrix::SparseMatrix(const SparseMatrix& m)
	{
		m_nRow = m.m_nRow;
		m_nCol = m.m_nCol;
		m_mapElem = m.m_mapElem;
	}

	const SparseMatrix& SparseMatrix::operator=(const SparseMatrix& m)
	{
		m_nRow = m.m_nRow;
		m_nCol = m.m_nCol;
		m_mapElem = m.m_mapElem;
		return *this;
	}

	double SparseMatrix::A(int r, int c) const
	{
		MatrixElem e, ev;
		e.row = r; e.col = c;

		if (!m_mapElem.Find(e, ev)) return 0.0;
		else return ev.value;
	}

	void SparseMatrix::Set(int r, int c, double v)
	{
		MatrixElem e, ev;
		e.row = r; e.col = c;

		if (v == 0.0) {
			m_mapElem.Remove(e);
			return;
		}
		
		if (!m_mapElem.Find(e, ev)) {
			e.value = v;
			m_mapElem.Insert(e);
			return;
		} else {
			m_mapElem.Remove(e);
			e.value = v;
			m_mapElem.Insert(e);
		}
	}

	void SparseMatrix::Print() const
	{
		for (int r = 0; r < m_nRow; r++) {
			for (int c = 0; c < m_nCol; c++) {
				printf("%2.4lg\t", A(r, c));	
			}
			printf("\n");
		}
		printf("-------\n");
	}

	SparseMatrix SparseMatrix::operator+(const SparseMatrix& m) const 
	{
		if (m_nRow != m.m_nRow || m_nCol != m.m_nCol) throw ERR_SIZE_MISMATCH;

		SparseMatrix result(m_nRow, m_nCol);
		
		int r, c;
		for (r = 0; r < m_nRow; r++) {
			for (c = 0; c < m_nRow; c++) {
				result.Set(r, c, A(r, c) + m.A(r, c));
			}
		}
		return result;
	}

	SparseMatrix SparseMatrix::operator-(const SparseMatrix& m) const
	{
		if (m_nRow != m.m_nRow || m_nCol != m.m_nCol) throw ERR_SIZE_MISMATCH;

		SparseMatrix result(m_nRow, m_nCol);
		
		int r, c;
		for (r = 0; r < m_nRow; r++) {
			for (c = 0; c < m_nRow; c++) {
				result.Set(r, c, A(r, c) - m.A(r, c));
			}
		}
		return result;
	}

	SparseMatrix SparseMatrix::operator*(const SparseMatrix& m) const
	{
		if (m_nCol != m.m_nRow) throw ERR_SIZE_MISMATCH;

		SparseMatrix result(m_nRow, m.m_nCol);

		int r, c, k;
		for (r = 0; r < m_nRow; r++) {
			for (c = 0; c < m.m_nCol; c++) {
				for (k = 0; k < m_nCol; k++) {
					result.Set(r, c, result.A(r, c) + A(r, k) * m.A(k, c));
				}
			}
		}
		return result;
	}

	bool SparseMatrix::ExchangeRow(int r1, int r2)
	{
		if (r1 < 0 || r1 >= m_nRow || r2 < 0 || r2 >= m_nRow) return false;
		double temp;
		for (int c = 0; c < m_nCol; c++) {
			temp = A(r2, c); Set(r2, c, A(r1, c)); Set(r1, c, temp);
		}
		return true;
	}

	SparseMatrix SparseMatrix::Solve(SparseMatrix Y)
	{
		if (!IsSquare()) throw ERR_MUSTSQUARE;
		// Gauss Elimination
		int r, r2, c, pv;
		double temp;
		SparseMatrix X(Y.GetRow(), 1);
		for (r = 0; r < m_nRow - 1; r++) {
			// pivotting
			pv = r;
			for (r2 = r + 1; r2 < m_nRow; r2++) {
				if (fabs(A(pv, r)) < fabs(A(r2, r))) pv = r2;
			}
			// 더좋은 축값이 있으면 교환 
			if (pv != r) {
				ExchangeRow(pv, r);
				Y.ExchangeRow(pv, r);
			}
			if (A(r, r) == 0) throw ERR_SINGULAR;

			// forward elimination
			for (r2 = r + 1; r2 < m_nRow; r2++) {
				if (A(r2, r) == 0) continue;
				double rmv = A(r2, r) / A(r, r);
				for (c = 0; c < m_nCol; c++) {
					temp = A(r2, c);
					Set(r2, c, A(r2, c) - rmv*A(r, c));
					if (fabs(A(r2, c)) < DBL_EPSILON*temp*2) Set(r2, c, 0);
				}
				temp = Y.A(r2, 0);
				Y.Set(r2, 0, Y.A(r2, 0) - rmv*Y.A(r, 0));
				if (fabs(Y.A(r2, 0)) < DBL_EPSILON*temp*2) Y.Set(r2, 0, 0);
			}
		}
		temp = 1;
		for (r = 0; r < m_nRow; r++) temp *= A(r, r);
		if (temp == 0) throw ERR_SINGULAR;

		// backward substitution
		for (r = m_nRow - 1; r >= 0; r--) {
			for (c = m_nCol - 1; c > r; c--) Y.Set(r, 0, Y.A(r, 0) - A(r, c)*X.A(c, 0));
			X.Set(r, 0, Y.A(r, 0) / A(r, r));
		}
		return X;
	}

	double SparseMatrix::Determinant() const
	{
		if (!IsSquare()) throw ERR_MUSTSQUARE;
		double det = 1;
		// Gauss Elimination
		int r, r2, c, pv;
		double temp;

		SparseMatrix m(*this);

		for (r = 0; r < m_nRow - 1; r++) {
			// pivotting
			pv = r;
			for (r2 = r + 1; r2 < m_nRow; r2++) {
				if (fabs(m.A(pv, r)) < fabs(m.A(r2, r))) pv = r2;
			}
			// 더좋은 축값이 있으면 교환 
			if (pv != r) {
				m.ExchangeRow(pv, r);
				det = -det;				
			}
			if (m.A(r, r) == 0) return 0;	// singular

			// forward elimination
			for (r2 = r + 1; r2 < m_nRow; r2++) {
				if (m.A(r2, r) == 0) continue;
				double rmv = m.A(r2, r) / m.A(r, r);
				for (c = 0; c < m_nCol; c++) {
					temp = m.A(r2, c);
					m.Set(r2, c, m.A(r2, c) - rmv*m.A(r, c));
					if (fabs(m.A(r2, c)) < DBL_EPSILON*temp*2) m.Set(r2, c, 0);
				}
			}
		}
		for (r = 0; r < m_nRow; r++) det *= m.A(r, r);
		return det;
	}

	SparseMatrix SparseMatrix::Inverse() const
	{
		if (!IsSquare()) throw ERR_MUSTSQUARE;

		// Gauss-Jordan Elimination
		int r, r2, c, pv;
		double temp;

		SparseMatrix M(*this);
		SparseMatrix I(GetRow(), GetCol());
		for (r = 0; r < I.GetRow(); r++) I.Set(r, r, 1);

		for (r = 0; r < m_nRow ; r++) {
			// pivotting
			pv = r;
			for (r2 = r + 1; r2 < m_nRow; r2++) {
				if (fabs(M.A(pv, r)) < fabs(M.A(r2, r))) pv = r2;
			}
			// 더좋은 축값이 있으면 교환 
			if (pv != r) {
				M.ExchangeRow(pv, r);
				I.ExchangeRow(pv, r);
			}
			if (M.A(r, r) == 0) throw ERR_SINGULAR;	// singular

			// forward elimination
			for (r2 = r + 1; r2 < m_nRow; r2++) {
				if (M.A(r2, r) == 0) continue;
				double rmv = M.A(r2, r) / M.A(r, r);
				for (c = 0; c < m_nCol; c++) {
					temp = M.A(r2, c);
					M.Set(r2, c, M.A(r2, c) - rmv*M.A(r, c));
					if (fabs(M.A(r2, c)) < DBL_EPSILON*temp*2) M.Set(r2, c, 0);

					temp = I.A(r2, c);
					I.Set(r2, c, I.A(r2, c) - rmv*I.A(r, c));
					if (fabs(I.A(r2, c)) < DBL_EPSILON*temp*2) I.Set(r2, c, 0);
				}
			}
		}

		temp = 1;
		for (r = 0; r < m_nRow; r++) temp *= M.A(r, r);
		if (temp == 0) throw ERR_SINGULAR;

		// backward elimination
		for (r = m_nRow - 1; r >= 0; r--) {
			// normalize
			for (c = 0; c < m_nCol; c++) I.Set(r, c, I.A(r, c) / M.A(r, r));
			M.Set(r, r, 1);
			for (r2 = r - 1; r2 >= 0; r2--) {
				double rmv = M.A(r2, r);
				for (c = 0; c < m_nCol; c++) {
					temp = M.A(r2, c);
					M.Set(r2, c, M.A(r2, c) - rmv*M.A(r, c));
					if (fabs(M.A(r2, c)) < DBL_EPSILON*temp*2) M.Set(r2, c, 0);

					temp = I.A(r2, c);
					I.Set(r2, c, I.A(r2, c) - rmv*I.A(r, c));
					if (fabs(I.A(r2, c)) < DBL_EPSILON*temp*2) I.Set(r2, c, 0);
				}
			}
		}

		return I;
	}
};

#endif