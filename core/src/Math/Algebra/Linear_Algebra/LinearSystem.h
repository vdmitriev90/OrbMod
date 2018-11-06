#pragma once
namespace Algebra
{
	class SLAU
	{
	private:
		void init(const Matrix &A, const Matrix &b);
		unsigned n, m, Nouts;
		vector<int> Outs;
		Matrix A, b, x, Q;
		double sigma;
		int SolveWithOtlsRej(Matrix &X, Matrix &Q, float nsig);
	public:
		SLAU(const Matrix &A, const Matrix &b);
		void addEq(const Matrix &lPart, const Matrix &rPart);
		int Solve();
		int Solve(Matrix &X, Matrix &Q);
		int Solve(Matrix &X, Matrix &Q, bool b_rej, float nsig);

		unsigned N() const;
		unsigned M() const;
		Matrix getX() const;
		Matrix getA() const;
		Matrix getb() const;
		unsigned getOuts() const;
		double getSigma() const;

		void Clear();

		SLAU();
		~SLAU();
	};
}

