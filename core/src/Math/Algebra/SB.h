#pragma once
#include"stdafx.h"
namespace Algebra
{
	using namespace std;
	// Sperling-Burdet transformation and  variables
	class SB
	{
	private:
		//initializer
		void Init(triple &X, triple &V, double &mu, double &t0);

	public:
		SB();

		SB(double  SV0[6], double mu, double t0);
		SB(const vector<double> &X);
		SB(Matrix &X, double mu, double t0);
		~SB();
		//
		triple p, q, a;
		double h, t;

		void copyToVect(vector<double>& X);
		triple v();
		double r();
		Matrix SV3d();
		Matrix dydY();
		Matrix dYdy(double mu);
	};

}