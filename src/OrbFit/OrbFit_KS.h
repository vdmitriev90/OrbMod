#pragma once
#include"stdafx.h"
namespace OrbMod
{
	class OrbFit_KS : public OrbFit, public var_KS_izo
	{
	public:
		OrbFit_KS(ivar * var) :OrbFit(var) {};
		OrbFit_KS() :OrbFit(this) {};
		virtual void setPar(vector<double> &X, Matrix &SV, double t0) override;
		virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo) override;
		virtual void endOfStep(double t0, double H, vector<double> &X, vector<double> &Y) override;
		virtual void StateLTCorr(double dt0, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Yo)override;
	};
}