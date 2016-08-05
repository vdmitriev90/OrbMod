#include "stdafx.h"
#include "OrbFit_SB.h"
using namespace std;
namespace OrbMod
{
	void OrbFit_SB::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		X.resize(N);
		SB sv = SB(SV, Force::getMu(), t0);
		sv.copyToVect(X);
		Matrix dYdY0(11, 11);
		dYdY0.Identy();
		dYdY0.copyToVec(11, X);

		//SB to cartesian partials on t0
		dY0dy0 = sv.dYdy(Force::getMu());

		Control::Obs_.reset();
		tout = (*Control::Obs_.it)->t;

		A.Clear();
		OmC.clear();
	}

	bool OrbFit_SB::Inter(SpiceDouble s0, double H, vector<double> &X, vector<double> &Y)
	{
		//moment of physical time at the beginning of step (diff. eq. #10 in SB variables)
		double t0 = X[10];

		double p = 0;
		for (int j = K - 1; j >= 0; j--)
			p = B[j][10] + p;
		//moment of physical time corresponding to the end of step
		double tf = t0 + H*(F0[10] + p);

		//step size in seconds
		double stepT = tf - t0;

		//забыл смысл этого присваивания
		Y = X;
		while (abs(tout - t0) < abs(stepT))
		{
			// Solution at the time tout
			calcSV(H, t0, tout, X, Y);
			SB svout = SB(Y);
			getdXdX0(Y, Fi);

			bool b = setParEq(svout.SV3d(), Fi, 0, tout);
			// If-function  "setParEq" return true - achieved last measurement => 
			// => stop integration
			if (b) return true;
		}
		return false;
	};
}
