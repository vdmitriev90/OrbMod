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

		//произодные от  вектора сотояния в KS переменных по ветору сотояния в прямоугольных координатах на t0
		dY0dy0 = sv.dYdy(Force::getMu());

		ObsSet::Instance().reset();
		tout = (*ObsSet::Instance().it)->t;

		A.Clear();
		OmC.clear();
	}

	bool OrbFit_SB::Inter(SpiceDouble s0, double H, vector<double> &X, vector<double> &Y)
	{
		//момент физичкского времени на начало шага (дифф. ур-е №9 в KS переменных)
		double t0 = X[10];

		double p = 0;
		for (int j = K - 1; j >= 0; j--)
			p = B[j][10] + p;
		//момент физического времени соответствующий концу шага
		double tf = t0 + H*(F0[10] + p);

		//величина шага в секундах
		double stepT = tf - t0;

		//забыл смысл этого присваивания
		Y = X;
		while (abs(tout - t0) < abs(stepT))
		{
			//получение решения на момент tout 
			calcSV(H, t0, tout, X, Y);
			SB svout = SB(Y);
			getdXdX0(Y, Fi);

			bool b = setParEq(svout.SV3d(), Fi, 0, tout);
			//если ф-я возвращает true  - достигнуто последнее измерение =>
			//=> прекращаем интегрирование
			if (b) return true;
		}
		return false;
	};
}
