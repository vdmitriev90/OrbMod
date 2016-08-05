#include"stdafx.h"
using namespace std;
namespace OrbMod
{
	//
	var_KS_izo::var_KS_izo()
	{
		N = 110; Niter = 10;
	}
	//
	void var_KS_izo::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		X.resize(N);
		double *SV_;
		SV.ToOneDimArr(SV_);
		KS sv = KS(SV_);

		sv.Y0(Force::getMu(), t0, X);
		tout = t0;
		Matrix dYdY0(10, 10);
		dYdY0.Identy();
		dYdY0.copyToVec(10, X);
		//KS to cartesian partials on t0
		dY0dy0 = sv.dYdy(Force::getMu());
		delete[] SV_;
	}
	//
	void var_KS_izo::GetX(vector<double> &X, Matrix &SV, double t0, Matrix &dXdX0)
	{
		SV = Matrix(6, 1);
		dXdX0 = Matrix(Niter, Niter);
		KS sv = KS(X);
		triple Pos = sv.X();
		triple V = sv.V();
		for (size_t i = 0; i < 3; i++)
		{
			SV(i, 0) = Pos[i];
			SV(i + 3, 0) = V[i];
		}
		dXdX0.setFromVec(10, X);
	}
	//
	void var_KS_izo::force(const double Ti, const vector<double> &X, vector<double> & F)
	{
		KS sv = KS(X);
		double h = X[8];
		double t = X[9];
		triple Xd3 = sv.X();
		triple V3d = sv.V();

		ForceIzo f(t, Xd3, V3d);
		triple acc = f.force_pert();
		Matrix ddFdy = f.get_ddFdsv();

		double r = sv.r();

		Matrix P = sv.P;
		Matrix Q = sv.Q;
		Matrix Pt = P.Transpose();
		Matrix Qt = Q.Transpose();
		Matrix B = sv.B();
		Matrix F3d(acc);

		//vector to matrix 10x10
		Matrix dYdY0(10, 10), E4(4, 4), dQdY0(4, 10), dPdY0(4, 10), dhdY0(1, 10), dtdY0(1, 10);
		dYdY0.setFromVec(10, X);
		dQdY0.setFromVec(10, X);
		dPdY0.setFromVec(50, X);
		dhdY0.setFromVec(90, X);
		dtdY0.setFromVec(100, X);

		//OrbFit::fo << "dYdY0\n" << dYdY0.toString("\t", "%e", 20, 1) << endl;

		Matrix BF = B*F3d;
		Matrix dydY = sv.dydY();
		Matrix dFdY0 = ddFdy*dydY*dYdY0;
		//Lambda
		Matrix L = sv.Lam(acc);
		//D
		E4.Identy();
		Matrix D = (2.0 * h)*E4 + 2.0*BF*Qt + r*L;

#pragma region Equations 0-9

		Matrix dPds = (2.0 * h)*Q + r*BF;
		double dhds = 0.25*(Pt*BF)(0, 0);
		double dtds = r;
		//
		for (size_t i = 0; i < 4; i++)
		{
			F[i] = 0.25*P(i, 0);
			F[i + 4] = dPds(i, 0);
		}
		F[8] = dhds;
		F[9] = dtds;
#pragma endregion

		// Equations 10-49
		Matrix ddQdY0 = 0.25*dPdY0;

		//Equations 50-89
		Matrix ddPdY0 = D*dQdY0 + 2 * Q*dhdY0 + r*B*dFdY0;

		//Equations 90-99
		Matrix ddhdY0 = Pt*L*dQdY0 + BF.Transpose()*dPdY0 + Pt*B*dFdY0;
		ddhdY0 *= 0.25;

		//Equations 100-109
		Matrix ddtdY0 = 2.0* Qt*dQdY0;

		ddQdY0.copyToVec(10, F);
		ddPdY0.copyToVec(50, F);
		ddhdY0.copyToVec(90, F);
		ddtdY0.copyToVec(100, F);

		Global::N_rp++;
	}
	//
	void var_KS_izo::getdXdX0(const vector<double> &X, Matrix &Fi)
	{
		KS sv = KS(X);

		double r = sv.r();
		Matrix dydY = sv.dydY();

		Matrix dYdY0(Niter, Niter);
		dYdY0.setFromVec(Niter, X);
		Matrix dtdY0(1, Niter);
		dtdY0.setFromVec(100, X);

		vector<double> F(N);

		force(0, X, F);
		Matrix G(Niter, 1);
		G.setFromVec(0, F);

		//according to equation 14  in (Shefer V.A., 2005)
		Fi = dydY*(dYdY0 - (1 / r)*G*dtdY0)*dY0dy0;

	}
}