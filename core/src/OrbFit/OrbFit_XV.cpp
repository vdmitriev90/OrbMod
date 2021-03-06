#include "OrbFit_XV.h"
#include"LinAlgAux.h"
#include"Integration_.h"
#include"Control.h"
#include"Global.h"
#include"constant.h"

#include"SpiceUsr.h"

using namespace Algebra;
using namespace consts;
using namespace std;

#define DEF__2  0
namespace OrbMod
{
	//using namespace alglib;

	//TypeOfObs OrbFit::ObsType;
	//
	//Matrix OrbFit_3D::Fi = Matrix(6, 6);
	//Matrix OrbFit_3D::x = Matrix(6, 1);
	//
	void OrbFit_XV::setPar(vector<double> &X, Matrix &SV, double t0)
	{

		Fi = Matrix(6, 6);
		xi = Matrix(6, 1);
		var_3D_izo::setPar(X, SV, t0);
		Fi.setFromVec(6, X);
		//OrbFit::fo << "--\n" << Fi.toString("\t", "%e", 20, 1) << endl;

		//Prediction of Light-time correction on the end of the next step
		tau0 = calcLTCorr(399, triple(X[0], X[2], X[3]), t0);

		Control::Obs_.reset();
		tout = (Control::Obs_.curr()).t;

		A.Clear();
		OmC.clear();
	}
	//
	bool OrbFit_XV::Inter(double t0, double H, vector<double> &X, vector<double> &Yo)
	{
		double dt = tout - t0;

		while (abs(dt - tau0) < abs(H))
		{
			if (Global::ObsT == TypeOfObs::Astro || Global::ObsT == TypeOfObs::mAstro2)
				StateLTCorr(t0, H, X, B, F0, P, Yo);
			else
				stepDs(dt, H, X, Yo);

			xi.setFromVec(0, Yo);
			Fi.setFromVec(6, Yo);

			//call of procedure-constructor of parametric equations (matrix A and vector A to C)
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
			stepDs(dt, H, X, Yo);

			triple Pos(Yo[0], Yo[1], Yo[2]);
			double d = (Pos - pE).getAbs();
			double tau1 = d / SoL;

			if (abs(tau - tau1) < 1e-7) break;
			tau = tau1;
		}
		dt = dt0 - tau;
		stepDs(dt, H, X, Yo);
	}
	void OrbFit_XV::endOfStep(double t0, double H, vector<double> &X, vector<double> &Y)
	{
		for (int k = 0; k < N; k++)
			P[k] = 0.0;

		for (int j = K - 1; j >= 0; j--)
			for (int k = 0; k < N; k++)
				P[k] = B[j][k] + P[k];

		for (int k = 0; k < N; k++)
			X[k] = X[k] + H*(F0[k] + P[k]);

		//Prediction of Light-time correction on the end of the next step
		//OrbFit::fo << setprecision(6);
		//OrbFit::fo <<" "<< t0 + H<<" "<<X[0] << " " << X[1] << " " << X[2] << " " << triple(X[0], X[2], X[3]).getAbs() << " ";
		tau0 = calcLTCorr(399, triple(X[0], X[2], X[3]), t0 + H);
	}
}