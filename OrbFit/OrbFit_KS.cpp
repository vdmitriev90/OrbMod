#include "stdafx.h"
#include "OrbFit_KS.h"
using namespace std;
//
namespace OrbMod
{
	void OrbFit_KS::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		var_KS_izo::setPar(X, SV, t0);

		ObsSet::Instance().reset();
		tout = (*ObsSet::Instance().it)->t;

		//световой промежуток в физическом времени
		tau0 = calcLTCorr(399, triple(SV(0, 0), SV(1, 0), SV(2, 0)), t0);

		A.Clear();
		OmC.clear();
	}
	//
	bool OrbFit_KS::Inter(double s0, double H, vector<double> &X, vector<double> &Y)
	{
		//момент физичкского времени на начало шага (дифф. ур-е №9 в KS переменных)
		double t0 = X[9];

		double p = 0;
		for (int j = K - 1; j >= 0; j--)
			p = B[j][9] + p;
		//момент физического времени соответствующий концу шага
		double tf = t0 + H*(F0[9] + p);

		//величина шага в секундах
		double stepT = tf - t0;
		//интервал интерполяции в физическом времени без учета световременой коррекции
		double dt = tout - t0;

		while (abs(dt - tau0) < abs(stepT))
		{
			if (Global::ObsT == TypeOfObs::Astro || Global::ObsT == TypeOfObs::mAstro2)
				StateLTCorr(t0, H, X, B, F0, P, Y);
			else
				calcSV(H, t0, tout, X, Y);

			//получение решения на момент tout
			KS svout = KS(Y);
			getdXdX0(Y, Fi);

			bool b_ = setParEq(svout.SV3d(), Fi, 0, tout);
			//если ф-я возвращает true  - достигнуто последнее измерение =>
			//=> прекращаем интегрирование
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

		//световой промежуток в физическом времени
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