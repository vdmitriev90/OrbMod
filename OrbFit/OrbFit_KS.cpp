#include "stdafx.h"
#include "OrbFit_KS.h"
using namespace std;
//
namespace OrbMod
{
	void OrbFit_KS::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		var_KS_izo::setPar(X, SV, t0);

		Control::Inst.Obs_->reset();
		tout = (*Control::Inst.Obs_->it)->t;

		//Light-time in physical space
		tau0 = calcLTCorr(399, triple(SV(0, 0), SV(1, 0), SV(2, 0)), t0);

		A.Clear();
		OmC.clear();
	}
	//
	bool OrbFit_KS::Inter(double s0, double H, vector<double> &X, vector<double> &Y)
	{
		//moment of physical time at the beginning of step (diff. eq. #9 in KS variables)
		double t0 = X[9];

		double p = 0;
		for (int j = K - 1; j >= 0; j--)
			p = B[j][9] + p;
		//moment of physical time corresponding to the end of step
		double tf = t0 + H*(F0[9] + p);

		//step size in seconds
		double stepT = tf - t0;
		//interpolation interval in physical time excluding  Light-time  
		double dt = tout - t0;

		while (abs(dt - tau0) < abs(stepT))
		{
			if (Global::ObsT == TypeOfObs::Astro || Global::ObsT == TypeOfObs::mAstro2)
				StateLTCorr(t0, H, X, B, F0, P, Y);
			else
				calcSV(H, t0, tout, X, Y);

			// Solution at the time tout
			KS svout = KS(Y);
			getdXdX0(Y, Fi);
			//call of procedure-constructor of parametric equations (matrix A and vector A to C)
			bool b_ = setParEq(svout.SV3d(), Fi, 0, tout);
			// If-function  "setParEq" return true - achieved last measurement => 
			// => stop integration
			if (b_) return true;
			dt = tout - t0;
		}
		return false;
	}
	//
	void OrbFit_KS::StateLTCorr(double t0, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Yo)
	{
		double lt, pos[3], tau = tau0;

		spkgps_c(399, tout, "J2000", Global::IDC, pos, &lt);
		triple pE(pos);
		triple Plt;
		//KS svlt = KS(X);
		//Plt = svlt.X();

		while (1)
		{
			calcSV(H, t0, tout - tau, X, Yo);
			KS svlt = KS(Yo);
			Plt = svlt.X();

			//ATLTRACE("%f %f %f\n", Plt[0], Plt[1], Plt[2]);
			triple pr;
			for (int i = 0; i < 3; i++) pr[i] = Plt[i] - pos[i];
			double tau1 = pr.getAbs() / SoL;

			if (abs(tau - tau1) < 1e-7) break;
			tau = tau1;
		}
		//fo << (tout-t0) << " " << tau << " " << H << " " << endl;
	}
	//
	void OrbFit_KS::endOfStep(double t0, double H, vector<double> &X, vector<double> &Y)
	{
		double t = X[9];
		for (int k = 0; k < N; k++)
			P[k] = 0.0;

		for (int j = K - 1; j >= 0; j--)
			for (int k = 0; k < N; k++)
				P[k] = B[j][k] + P[k];

		for (int k = 0; k < N; k++)
			X[k] = X[k] + H*(F0[k] + P[k]);

		double tf = X[9];

		KS svlt = KS(X);

		//Light - time in physical space
		tau0 = calcLTCorr(399, svlt.X(), t);

	}

	//void OrbFit_KS::GetX(vector<double> &X, Matrix &SV, double t0, Matrix &dXdX0)
	//{
	//	SV = Matrix(6, 1);
	//	dXdX0 = Matrix(Niter, Niter);
	//	KS sv = KS(X);
	//	triple Pos = sv.X();
	//	triple V = sv.V();
	//	for (size_t i = 0; i < 3; i++)
	//	{
	//		SV(i, 0) = Pos[i];
	//		SV(i + 3, 0) = V[i];
	//	}
	//	dXdX0.setFromVec(10, X);
	//	//OrbFit::fo.close();
	//}
}