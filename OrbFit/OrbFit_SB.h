#pragma once
#include"stdafx.h"
namespace OrbMod
{
	class OrbFit_SB : public OrbFit, public var_SB_izo
	{
	public:
		virtual void setPar(vector<double> &X, Matrix &SV, double t0) override;
		virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo, vector<double> &F0, vector<double> &P, vector< vector<double>> &B) override;

		virtual void StateLTCorr(double dt0, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Yo) {};
	};
}
