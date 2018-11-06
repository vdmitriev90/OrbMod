#include"stdafx.h"

using namespace std;
namespace OrbMod
{
	//
	var_3D_izo::var_3D_izo()
	{
		N = 42; Niter = 6;
	}
	//
	void var_3D_izo::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		X.resize(N);
		for (int i = 0; i < 6; i++)
			X[i] = SV(i, 0);

		Matrix M(6, 6);
		M.Identy();
		M.copyToVec(6, X);

		tout = t0;
	}
	//
	void var_3D_izo::GetX(const vector<double> &X, Matrix &SV, double t0, Matrix &dXdX0)
	{
		dXdX0 = Matrix(6, 6);
		SV = Matrix(6, 1);
		for (size_t i = 0; i < 6; i++)
			SV(i, 0) = X[i];
		dXdX0.setFromVec(6, X);
	}
	//
	void var_3D_izo::force(const double Ti, const vector<double> &X, vector<double> & F)
	{
		ForceIzo f(Ti, triple(X[0], X[1], X[2]), triple(X[3], X[4], X[5]));
		triple acc = f.force_cb() + f.force_pert();

		//first - order derivatives of the state vector
		for (size_t i = 0; i < 3; i++)
		{
			F[i] = X[i + 3];
			F[i + 3] = acc[i];
		}
		Matrix dXdX0(6, 6);
		dXdX0.setFromVec(6, X);

		Matrix dFdX(6, 6);
		Matrix dFcbdx = f.get_dFcbdx();
		Matrix ddFdsv = f.get_ddFdsv();

		dFdX(0, 3) = dFdX(1, 4) = dFdX(2, 5) = 1.0;

		for (size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 3; j++)
			{
				dFdX(i + 3, j) = dFcbdx(i, j) + ddFdsv(i, j);
				dFdX(i + 3, j + 3) = ddFdsv(i, j + 3);
			}
		//OrbFit::fo<<"dXdX0\n"<< dXdX0.toString("\t", "%e",20, 1)<<endl;
		//OrbFit::fo << "dFdX\n" << dFdX.toString("\t", "%e", 20, 1) << endl;
		//Force::dFdX(i + 3, j) = Force::dFcbdx(i, j) + Force::dF3bdx(i, j);
		Matrix dFidt = dFdX*dXdX0;

		//first - order derivatives of transition matrix
		dFidt.copyToVec(6, F);
		//(dFdX*dXdX0).copyToVec(6, F);
		//Force::dXdX0dt.copyToVec(6, F);

		Global::N_rp++;
	}
}
