#include "stdafx.h"
#include "var_KS_izo2.h"

namespace OrbMod
{
	var_KS_izo2::var_KS_izo2()
	{
	}


	var_KS_izo2::~var_KS_izo2()
	{
	}
	//
	void var_KS_izo2::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		var_KS_izo::setPar(X, SV, t0);
		Fi.clear();
		SVi.clear();
	}
	//
	bool var_KS_izo2::Inter(double s0, double H, vector<double> &X, vector<double> &Y, vector<double> &F0, vector<double> &P, vector< vector<double>> &B)
	{
		double t0 = X[9];

		double p = 0;
		for (int j = K - 1; j >= 0; j--)
			p = B[j][9] + p;

		double tf = t0 + H*(F0[9] + p);
		bool b = false;
		//
		if (abs(tf - t0) >= abs(te - t0))
		{
			tf = te;
			b = true;
		}

		double stepT = tf - t0;
		Y = X;
		if (Global::Discr != 0)
		{
			while (abs(tout - t0) < abs(stepT))
			{
				calcSV(H, t0, tout, X, B, F0, P, Y);
				KS svout = KS(Y);

				Matrix svi = svout.SV3d();
				SVi.push_back(svi);

				Matrix fi;
				this->getdXdX0(Y, fi);
				Fi.push_back(fi);

				tout += Global::Discr;
			}
		}
		//
		if (b)
		{
			calcSV(H, t0, te, X, B, F0, P, Y);
			X = Y;
			KS svout = KS(Y);
			return true;
		}

		return false;
	}
}