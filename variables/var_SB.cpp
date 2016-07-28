#include"stdafx.h"

using namespace std;
namespace OrbMod
{
	var_SB::var_SB()
	{
		N = Niter = 11;
	}

	void var_SB::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		X.resize(N);
		SB sv = SB(SV, Force::getMu(), t0);
		Global::step /= sv.r();
		sv.copyToVect(X);
		tout = t0;
	}
	void var_SB::GetX(vector<double> &X, Matrix &SV, double t0, Matrix &dXdX0)
	{
		SV = Matrix(6, 1);
		SB sv = SB(X);
		triple Pos = sv.q;
		triple V = sv.v();
		for (size_t i = 0; i < 3; i++)
		{
			SV(i, 0) = Pos[i];
			SV(i + 3, 0) = V[i];
		}
	}
	void var_SB::force(const double Ti, const vector<double> &X, vector<double> & F)
	{
		SB sv = SB(X);

		double r = sv.q.getAbs();
		double r2 = r*r;
		triple V = sv.p / r;

		Force f_(sv.t, sv.q, V);
		triple f = f_.force_pert();

		triple dpds = (2.0*sv.h)*sv.q - sv.a + r2*f;
		double dhds = sv.p*f;
		triple dads = (2.0*dhds)*sv.q - (sv.q*f)*sv.p - (sv.q*sv.p)*f;
		for (int i = 0; i < 3; i++)
		{
			F[i] = sv.p[i];
			F[i + 3] = dpds[i];
			F[i + 6] = dads[i];
		}
		F[9] = dhds;
		F[10] = r;
		Global::N_rp++;
	}
	//
	bool var_SB::Inter(SpiceDouble s0, double H, vector<double> &X, vector<double> &Y)
	{
		double t0 = X[10];

		double p = 0;
		for (int j = K - 1; j >= 0; j--)
			p = B[j][10] + p;

		double tf = t0 + H*(F0[10] + p);
		bool b = false;
		//
		if (abs(tf - t0) > abs(te - t0))
		{
			tf = te;
			b = true;
		}

		double stepT = tf - t0;

		Y = X;
		// results logging
		if (Global::Discr != 0)
		{
			while (abs(tout - t0) < abs(stepT))
			{
				calcSV(H, t0, tout, X, Y);
				SB svout = SB(Y);
				Integration::Instance.write(tout, svout.q, svout.v(), 0, 0);
				tout += Global::Discr;
			}
		}
		//last step
		if (b)
		{
			calcSV(H, t0, te, X, Y);
			X = Y;
			SB svout = SB(Y);
			if (Global::Discr != 0)
				Integration::Instance.write(te, svout.q, svout.v(), 0, 0);
			return true;
		}
		return false;
	}
	//
	void var_SB::endOfStep(double s0, double H, vector<double> &X, vector<double> &Y)
	{
		double t_s = X[10];
		double p = 0;
		for (int j = K - 1; j >= 0; j--)
			p = B[j][10] + p;

		double tf = t_s + H*(F0[9] + p);
		//
		if (abs(tf - t_s) > abs(te - t_s))
			calcSV(H, t_s, te, X, Y);
		else
			ivar::endOfStep(s0, H, X, Y);
	}
	//
	void var_SB::calcSV(double S, double t0, double tout, vector<double> &X, vector<double> &Y)
	{
		double r0 = sqrt(X[0] * X[0] + X[1] * X[1] + X[2] * X[2]);
		double ds = (tout - t0) / r0;
		double t = t0;
		int i = 0;
		while (abs(tout - t) > 1e-15 && i < 15)
		{
			stepDs(ds, S, X, Y);
			r0 = sqrt(Y[0] * Y[0] + Y[1] * Y[1] + Y[2] * Y[2]);
			t = Y[10];
			ds += (tout - t) / r0;
			i++;
		}
	}
}
