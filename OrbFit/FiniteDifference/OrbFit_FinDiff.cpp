#include "stdafx.h"
#include "OrbFit_FinDiff.h"

namespace OrbMod
{
	OrbFit_FinDiff::OrbFit_FinDiff()
	{
	}


	OrbFit_FinDiff::~OrbFit_FinDiff()
	{
	}
	void OrbFit_FinDiff::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		X.resize(N);
		for (int i = 0; i < 6; i++)
			X[i] = SV(i, 0);
		xi = Matrix(6, 1);
		Fi = Matrix(6, 6);

		ObsSet::Instance().reset();
		tout = (*ObsSet::Instance().it)->t;
	}
	void OrbFit_FinDiff::Adjust(Matrix &SV, double t0, double &sigma, Matrix &Q)
	{
		const int  NOR = Global::NOR;
		double to = Global::t0;
		double te = Global::te;
		double step = Global::step;

		//максимальное число итераций
		int NI = Global::Niter;
		//Output parameters
		int NS = 0;
		int NBS = 0;
		vector<double> X;

		int iter = 0;
		while (iter < maxIter)
		{
			setPar(X, SV, to);
			FunK(X, to, te, step, NOR, NI, NS, NBS);
			Matrix x;
			Solve(A, Matrix(OmC), x, sigma, Q);
			SV += x;
			if (x.MaxMod() < Global::eps*SV.MaxMod()) break;
			iter++;
		}
		fo << SV.toString(";", "%21.16f", 35);

	}
	void OrbFit_FinDiff::FunK(vector<double> &X, double to, double te, double &step, int NOR, int NI, int &NS, int &NBS)
	{
		Xvar.clear();
		Xvar.resize(13);
		vector<double> var(6), X0(X), Xi(X);
		I = 0;
		for (int i = 0; i < 6; i++) var[i] = X[i] * 0.01;

		A.Clear();
		OmC.clear();
		//первое интегрирование без вариаций
		FODE(Xi, to, te, step, NOR, NI, NS, NBS);

		//+
		for (I = 1; I < 7; I++)
		{
			Xi = X0;
			Xi[I - 1] += var[I - 1];
			ObsSet::Instance().reset();
			tout = (*ObsSet::Instance().it)->t;
			FODE(Xi, to, te, step, NOR, NI, NS, NBS);
		}
		//-
		for (I = 7; I < 13; I++)
		{
			Xi = X0;
			Xi[I - 7] -= var[I - 7];
			ObsSet::Instance().reset();
			tout = (*ObsSet::Instance().it)->t;
			FODE(Xi, to, te, step, NOR, NI, NS, NBS);
		}
		Matrix Am;
		for (int i = 0; i < OmC.size() / 2; i++)
		{
			Matrix M(6, 6);
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 6; k++)
				{
					double p = (Xvar[j + 1][i][k] - Xvar[0][i][k]) / var[j];
					double m = (Xvar[0][i][k] - Xvar[j + 7][i][k]) / var[j];
					M(k, j) = (p + m) / 2.0;
					//M(j, k) = p;
				}
			Matrix temp = A.subMatrix(2 * i, 2, 0, 6);
			//	OrbFit::fo << M.toString("\t", "%19.12e", 25, 0) << endl;
			temp = temp*M;
			Am.addRows(temp);
		}
		this->A = Am;
	}
	bool OrbFit_FinDiff::Inter(double t0, double H, double &tout, vector<double> &X, vector<double> &Yo, vector<double> &F0, vector<double> &P, vector< vector<double>> &B)
	{
		double dt = tout - t0;
		while (abs(dt) < abs(H))
		{
			stepDs(dt, H, X, Yo);
			xi.setFromVec(0, Yo);
			if (I == 0)
			{
				Fi.Identy();
				//вызов процедуры-конструктора параметрических уравнений (м-ца А и вектор О-С)
				bool b = setParEq(xi, Fi, 0, tout);
				if (b)
				{
					Xvar[I].push_back(Yo);
					return true;
				}
			}
			else
			{
				ObsSet::Instance().it++;
				if (ObsSet::Instance().it == ObsSet::Instance().obs.end())
				{
					Xvar[I].push_back(Yo);
					return true;
				}
				tout = (*ObsSet::Instance().it)->t;
			}

			Xvar[I].push_back(Yo);
			dt = tout - t0;
		}
		return false;
	};
}