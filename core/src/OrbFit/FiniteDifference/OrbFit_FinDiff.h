#pragma once
#include "OrbFit.h"

namespace OrbMod
{
	class OrbFit_FinDiff :
		public var_3D, public  OrbFit
	{
	public:
		OrbFit_FinDiff();
		~OrbFit_FinDiff();
		void setPar(std::vector<double> &X, Algebra::Matrix &SV, double t0) override;
		bool Inter(double t0, double H, double &tout, std::vector<double> &X, std::vector<double> &Yo, std::vector<double> &F0, std::vector<double> &P, std::vector< std::vector<double>> &B);

		int I = 0;
		virtual void Adjust(Algebra::Matrix &SV, double t0, double &sigma, Algebra::Matrix &Q) override;
		std::vector<std::vector<std::vector<double>>> Xvar;
		void FunK(std::vector<double> &X, double to, double te, double &step, int NOR, int NI, int &NS, int &NBS);
	};
}

