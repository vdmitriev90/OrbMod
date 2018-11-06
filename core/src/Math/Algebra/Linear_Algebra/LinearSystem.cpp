#include "stdafx.h"
#include "LinearSystem.h"
namespace Algebra
{
	//
	SLAU::SLAU()
	{
	}
	//
	SLAU::~SLAU()
	{
	}
	//
	void SLAU::init(const Matrix &A, const Matrix &b)
	{
		//if (A.nCols() != b.nCols())	throw ("");

		this->n = A.nRows();
		this->m = A.nCols();

		//if (n<m) throw ("");

		this->A = A;
		this->b = b;

	}
	//
	int SLAU::SolveWithOtlsRej(Matrix &X, Matrix &Q, float nsig)
	{
		Nouts = 0;
		do
		{
			Outs.clear();
			if (!LinAlgAux::LSSolve(A, b, x, sigma, this->Q, nsig, Outs)) return 0;
			int nOuts = Outs.size();

			if (nOuts > 0)
			{
				int nnew = n - nOuts;
				if (nnew < m) return 0;
				Matrix newA(nnew, m), newb(nnew, 1);
				int i_ = 0;
				for (size_t i = 0; i < n; ++i)
				{
					if (i_ < Outs.size() && i == Outs[i_])
					{
						++i_;
						continue;
					}
					newb(i - i_, 0) = b(i, 0);
					for (size_t j = 0; j < m; ++j)
						newA(i - i_, j) = A(i, j);
				}
				A = newA;
				b = newb;
				n = A.nRows();
			}
			Nouts += nOuts;
		} while (Outs.size() > 0);

		return 1;
	}
	//
	SLAU::SLAU(const Matrix &A, const Matrix &b)
	{
		init(A, b);
	}
	//
	void SLAU::addEq(const Matrix &l, const Matrix &r)
	{
		A.addRows(l);
		b.addRows(r);
		n = A.nRows();
		m = A.nCols();
	}
	//
	int SLAU::Solve()
	{
		return(LinAlgAux::LSSolve(A, b, x, sigma, Q));
	}
	//
	int  SLAU::Solve(Matrix &X, Matrix &Q)
	{
		if (!LinAlgAux::LSSolve(A, b, x, sigma, this->Q))return 0;
		Q = this->Q;

		return 1;
	}
	//
	int  SLAU::Solve(Matrix &X, Matrix &Q, bool b_rej, float nsig)
	{
		if (b_rej)
			return SolveWithOtlsRej(X, Q, nsig);
		else
			return Solve(X, Q);
	}
	//
	unsigned SLAU::N() const
	{
		return n;
	}
	//
	unsigned SLAU::M() const
	{
		return m;
	}
	//
	Matrix SLAU::getX() const
	{
		return x;
	}
	//
	Matrix SLAU::getA() const
	{
		return A;
	}
	//
	Matrix SLAU::getb() const
	{
		return b;
	}
	//
	unsigned SLAU::getOuts() const
	{
		return Nouts;
	}
	//
	double SLAU::getSigma() const
	{
		return sigma;
	}
	//
	void SLAU::Clear()
	{
		A.Clear();
		b.Clear();
		x.Clear();
		n = m = 0;
	}
}