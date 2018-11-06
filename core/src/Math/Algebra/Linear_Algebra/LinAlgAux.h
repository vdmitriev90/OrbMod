#pragma once
namespace Algebra
{
	class LinAlgAux
	{
	public:
		static Matrix initCov(double p, double q);
		static Matrix initCov(Matrix &RMS);
		static int LSSolve(Matrix &A, Matrix &b, Matrix &x, double &sigma, Matrix &Q);
		static int LSSolve(Matrix &A, Matrix &b, Matrix &x, double &sigma, Matrix &Q, float nsig, vector<int> &Outs);

		static Matrix CalcRMS(double sigma, Matrix &Q);
		static Matrix CalcRMS(double sigma, Matrix &Q, double &Prms, double &Vrms);
		static Matrix CalcDisp(double sigma, Matrix &Q);

		LinAlgAux();
		~LinAlgAux();
	};

}