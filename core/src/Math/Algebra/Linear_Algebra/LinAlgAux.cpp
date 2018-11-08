
#include "LinAlgAux.h"

using namespace std;

namespace Algebra
{

	LinAlgAux::LinAlgAux()
	{
	}
	LinAlgAux::~LinAlgAux()
	{
	}
	//
	Matrix LinAlgAux::initCov(double p, double q)
	{
		Matrix P0(6, 6);
		P0.Identy();

		for (size_t i = 0; i < 6; i++)
			if (i < 3)
				P0(i, i) = P0(i, i) * p;
			else
				P0(i, i) = P0(i, i) * q;
		return P0;
	}
	//
	Matrix LinAlgAux::initCov(Matrix &RMS)
	{
		int n = RMS.nRows();
		Matrix res(n, n);
		res.Identy();
		for (size_t i = 0; i < n; i++)
			res(i, i) *= RMS(i, 0);
		return res;
	}
	//
	int LinAlgAux::LSSolve(Matrix &A, Matrix &b, Matrix &x, double &sigma, Matrix &Q)
	{
		int M = A.nCols();
		int N = A.nRows();

		if (!Matrix::LeastSQRSolve(A, b, x, Q))	return 0;
		Matrix V = A*x - b;
		Matrix vv = V.Transpose()*V;
		sigma = sqrt(vv(0, 0) / (N - M));

		return 1;
	}
	int LinAlgAux::LSSolve(Matrix &A, Matrix &b, Matrix &x, double &sigma, Matrix &Q, float nsig, vector<int> &Outs)
	{
		int M = A.nCols();
		int N = A.nRows();

		if (!Matrix::LeastSQRSolve(A, b, x, Q))	return 0;
		Matrix V = A*x - b;
		Matrix vv = V.Transpose()*V;
		sigma = sqrt(vv(0, 0) / (N - M));

		//Outliers search
		Outs.clear();
		double tresh = sigma*nsig;

		for (size_t i = 0; i < V.nRows(); i++)
		{
			if (abs(V(i, 0)) >= tresh)
				Outs.push_back(i);
		}

		return 1;
	}
	//
	Matrix LinAlgAux::CalcRMS(double sigma, Matrix &Q)
	{
		Matrix diag = Q.PrimeDiag();
		for (size_t i = 0; i < Q.nRows(); i++)
			diag(i, 0) = sigma*sqrt(diag(i, 0));
		return diag;
	}
	Matrix LinAlgAux::CalcDisp(double sigma, Matrix &Q)
	{
		Matrix diag = Q.PrimeDiag();
		double sigma2 = sigma*sigma;

		for (size_t i = 0; i < Q.nRows(); i++)
			diag(i, 0) = sigma2*diag(i, 0);
		return diag;
	}
	Matrix LinAlgAux::CalcRMS(double sigma, Matrix &Q, double &Prms, double &Vrms)
	{
		Matrix RMS = Q.PrimeDiag();
		int L = Q.nRows();
		for (size_t i = 0; i < L; i++)
			RMS(i, 0) = sigma*sqrt(RMS(i, 0));

		if (L > 5)
		{
			Prms = sqrt(RMS(0, 0)*RMS(0, 0) + RMS(1, 0)*RMS(1, 0) + RMS(2, 0)*RMS(2, 0));
			Vrms = sqrt(RMS(3, 0)*RMS(3, 0) + RMS(4, 0)*RMS(4, 0) + RMS(5, 0)*RMS(5, 0));
		}
		return RMS;
	}
}