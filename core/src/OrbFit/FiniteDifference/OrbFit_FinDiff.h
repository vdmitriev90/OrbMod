#pragma once
#include "variables\var.h"

namespace OrbMod
{
	class OrbFit_FinDiff :
		public var_3D, public  OrbFit
	{
	public:
		OrbFit_FinDiff();
		~OrbFit_FinDiff();
		void setPar(vector<double> &X, Matrix &SV, double t0) override;
		bool Inter(double t0, double H, double &tout, vector<double> &X, vector<double> &Yo, vector<double> &F0, vector<double> &P, vector< vector<double>> &B);

		int I = 0;
		virtual void Adjust(Matrix &SV, double t0, double &sigma, Matrix &Q) override;
		vector<vector<vector<double>>> Xvar;
		void FunK(vector<double> &X, double to, double te, double &step, int NOR, int NI, int &NS, int &NBS);
	};
}

