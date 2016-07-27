#include "stdafx.h"
#include "OrbFit_XV.h"
#define DEF__2  0
//using namespace alglib;

//TypeOfObs OrbFit::ObsType;
//
//Matrix OrbFit_3D::Fi = Matrix(6, 6);
//Matrix OrbFit_3D::x = Matrix(6, 1);
//
namespace OrbMod
{
	void OrbFit_XV::setPar(vector<double> &X, Matrix &SV, double t0)
	{

		Fi = Matrix(6, 6);
		xi = Matrix(6, 1);
		var_3D_izo::setPar(X, SV, t0);
		Fi.setFromVec(6, X);
		//OrbFit::fo << "--\n" << Fi.toString("\t", "%e", 20, 1) << endl;

		//прогноз световременной коррекции на конец следующего шага
		tau0 = calcLTCorr(399, triple(X[0], X[2], X[3]), t0);

		ObsSet::Instance().reset();
		tout = (*ObsSet::Instance().it)->t;

		A.Clear();
		OmC.clear();
	}
	//
	bool OrbFit_XV::Inter(double t0, double H, vector<double> &X, vector<double> &Yo, vector<double> &F0, vector<double> &P, vector< vector<double>> &B)
	{
		double dt = tout - t0;

		while (abs(dt - tau0) < abs(H))
		{
			if (Global::ObsT == TypeOfObs::Astro || Global::ObsT == TypeOfObs::mAstro2)
				StateLTCorr(t0, H, X, B, F0, P, Yo);
			else
				stepDs(dt, H, X, B, F0, P, Yo);

			xi.setFromVec(0, Yo);
			Fi.setFromVec(6, Yo);

			//вызов процедуры-конструктора параметрических уравнений (м-ца А и вектор О-С)
			bool b = setParEq(xi, Fi, 0, tout);
			if (b)return true;
			dt = tout - t0;
		}
		return false;
	};
	//
	void OrbFit_XV::StateLTCorr(double t0, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Yo)
	{
		double lt, pos[3], dt = 0, tau = tau0;
		spkgps_c(399, tout, "J2000", Global::IDC, pos, &lt);
		triple pE(pos);
		double dt0 = tout - t0;
		while (1)
		{
			dt = dt0 - tau;
			stepDs(dt, H, X, B, F0, P, Yo);

			triple Pos(Yo[0], Yo[1], Yo[2]);
			double d = (Pos - pE).getAbs();
			double tau1 = d / SoL;

			if (abs(tau - tau1) < 1e-7) break;
			tau = tau1;
		}
		dt = dt0 - tau;
		stepDs(dt, H, X, B, F0, P, Yo);
	}
	void OrbFit_XV::endOfStep(double t0, double H, vector<double> &X, vector<double> &Y, vector<double> &F0, vector<double> &P, vector< vector<double>> &B)
	{
		for (int k = 0; k < N; k++)
			P[k] = 0.0;

		for (int j = K - 1; j >= 0; j--)
			for (int k = 0; k < N; k++)
				P[k] = B[j][k] + P[k];

		for (int k = 0; k < N; k++)
			X[k] = X[k] + H*(F0[k] + P[k]);

		//прогноз световременной коррекции на конец следующего шага
		tau0 = calcLTCorr(399, triple(X[0], X[2], X[3]), t0 + H);
	}
}
