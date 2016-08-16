#include"stdafx.h"
#include"var.h"

using namespace std;
namespace OrbMod
{
	var_2D::var_2D()
	{
		N = Niter = 4;
	}

	var_3D::var_3D()
	{
		N = Niter = 6;
	}

	void var_2D::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		X.resize(N);
		for (int i = 0; i < N; i++)
		{
			X[i] = SV(i, 0);
			X[i + 2] = SV(i + 3, 0);
		}

		tout = t0;
	}
	void var_2D::GetX(vector<double> &X, Matrix &SV, double t0, Matrix &dXdX0)
	{
		SV = Matrix(6, 1);
		for (int i = 0; i < 2; i++)
		{
			SV(i, 0) = X[i];
			SV(i + 3, 0) = X[i + 2];
		}

		SV(3, 0) = 0; SV(5, 0) = 0;
	}
	void var_2D::force(const double Ti, const vector<double> &X, vector<double> & F)
	{
		double r = sqrt(X[0] * X[0] + X[1] * X[1]);
		double r3 = r*r*r;
		double mu = Force::getMu();
		F[0] = X[2];
		F[1] = X[3];
		F[2] = -mu*X[0] / r3;
		F[3] = -mu*X[1] / r3;
		Global::N_rp++;
	}
	//
	bool var_2D::Inter(double t0, double H, vector<double> &X, vector<double> &Yo)
	{
		if (Global::Discr != 0)
			while (abs(tout - t0) <= abs(H))
			{
				stepDs(tout - t0, H, X, Yo);

				Integration::Instance.write(t0, triple(X[0], X[1], 0), triple(X[2], X[3], 0));
				tout += Global::Discr;
			}
		return false;
	}
	void var_3D::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		X.resize(N);
		for (int i = 0; i < N; i++)
			X[i] = SV(i, 0);
		tout = t0;
	}
	void var_3D::GetX(vector<double> &X, Matrix &SV, double t0, Matrix &dXdX0)
	{
		SV = Matrix(6, 1);
		for (int i = 0; i < 6; i++)
			SV(i, 0) = X[i];
	}

	void var_3D::force(const double Ti, const vector<double> &X, vector<double> & F)
	{
		Force f(Ti, triple(X[0], X[1], X[2]), triple(X[3], X[4], X[5]));
		triple acc = f.force_cb() + f.force_pert();

		for (size_t i = 0; i < 3; i++)
		{
			F[i] = X[i + 3];
			F[i + 3] = acc[i];
		}
		Global::N_rp++;
	}
	//
	bool var_3D::Inter(double t0, double H, vector<double> &X, vector<double> &Yo)
	{
		if (Global::Discr != 0)
			while (abs(tout - t0) <= abs(H))
			{
				stepDs(tout - t0, H, X, Yo);
				Integration::Instance.write(tout, triple(Yo[0], Yo[1], Yo[2]), triple(Yo[3], Yo[4], Yo[5]));

				tout += Global::Discr;
			}
		return false;
	}
}