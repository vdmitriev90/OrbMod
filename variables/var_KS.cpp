#include"stdafx.h"

using namespace std;
namespace OrbMod
{
	var_KS::var_KS()
	{
		N = Niter = 10;
	}

	void var_KS::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		X.resize(N);
		double *SV_;
		SV.ToOneDimArr(SV_);
		KS sv = KS(SV_);
		sv.Y0(Force::getMu(), t0, X);
		//Global::step /= sv.r();
		tout = t0;
		delete[] SV_;
	}
	//
	void var_KS::GetX(vector<double> &X, Matrix &SV, double t0, Matrix &dXdX0)
	{
		SV = Matrix(6, 1);
		KS sv = KS(X);
		triple Pos = sv.X();
		triple V = sv.V();
		//Global::step *= sv.r();
		for (size_t i = 0; i < 3; i++)
		{
			SV(i, 0) = Pos[i];
			SV(i + 3, 0) = V[i];
		}
	}
	//
	void var_KS::force(const double Ti, const vector<double> &X, vector<double> & F)
	{
		KS sv = KS(X);
		double h = X[8];
		double t = X[9];

		Force f(t, sv.X(), sv.V());
		double r = sv.r();

		triple acc = f.force_pert();

		Matrix ksp(acc);
		Matrix B = sv.B();
		ksp = B*ksp;
		Matrix dPds = 2.0 * h*sv.Q + r*ksp;
		double dhds = 0.25*((sv.P).Transpose()*ksp)(0, 0);
		double dtds = r;
		//
		for (size_t i = 0; i < 4; i++)
		{
			F[i] = 0.25*sv.P(i, 0);
			F[i + 4] = dPds(i, 0);
		}
		//
		F[8] = dhds;
		F[9] = dtds;
		Global::N_rp++;
	}
	//
	bool var_KS::Inter(double s0, double H, vector<double> &X, vector<double> &Y)
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
				calcSV(H, t0, tout, X, Y);
				KS svout = KS(Y);
				triple pos = svout.X();
				triple vel = svout.V();

				Integration::Instance.write(tout, pos, vel, 0, 0);
				tout += Global::Discr;
			}
		}
		if (b)
		{
			calcSV(H, t0, te, X, Y);
			X = Y;
			KS svout = KS(Y);
			if (Global::Discr != 0)
				Integration::Instance.write(te, svout.X(), svout.V(), 0, 0);
			return true;
		}

		return false;
	}
	//
	void var_KS::endOfStep(double s0, double H, vector<double> &X, vector<double> &Y)
	{
		double t_s = X[9];
		double p = 0;
		for (int j = K - 1; j >= 0; j--)
			p = B[j][9] + p;

		double tf = t_s + H*(F0[9] + p);
		//
		if (abs(tf - t_s) > abs(te - t_s))
			calcSV(H, t_s, te, X, Y);
		else
			ivar::endOfStep(s0, H, X, Y);
	}
	/// <summary>
	/// Интерполяция вектора состояния и изохронных производных на произвольный момент ФИЗИЧЕСКОГО времени tout
	///Interpolation of the state vector and ransition Matrix on a moment of physical time tout
	/// </summary>
	/// <param name="S">текущая величина шага в единицах фиктивного времени</param>
	/// <param name="S">Step value in units of the fictitious time</param>
	/// <param name="t0">Момент ФИЗИЧЕСКОГО времени, соответствующий началу шага интегрирования</param>
	/// <param name="t0">The moment of physical time, corresponding to the beginning of the integration step</param>	
	/// <param name="tout">Момент ФИЗИЧЕСКОГО времени, должна быть выполнена интерполяция</param>
	/// <param name="tout">The moment of physical time, interpolation should to be performed on </param>
	/// <param name="X">Вектор состояния и изохронные производные на начало шага интегрирования</param>
	/// <param name="X">Variables on the beginning of the integration step </param>
	/// <param name="Y">Искомый вектор состояния на  tout</param>
	/// <param name="Y">Derived  variables on the beginning of the moment tout</param>
	/// <returns>void</returns>
	void var_KS::calcSV(double S, double t0, double tout, vector<double> &X, vector<double> &Y)
	{
		double r0 = (X[0] * X[0] + X[1] * X[1] + X[2] * X[2] + X[3] * X[3]);
		double ds = (tout - t0) / r0;
		double t = 0;
		int i = 0;
		static int iter = 0;
		iter++;

		double conv = DBL_MAX;
		do
		{
			stepDs(ds, S, X, Y);
			r0 = Y[0] * Y[0] + Y[1] * Y[1] + Y[2] * Y[2] + Y[3] * Y[3];
			t = Y[9];
			ds += (tout - t) / r0;
			i++;
			conv = abs(tout - t);

		} while ((conv > DBL_EPSILON && i < 15));

	};
}
