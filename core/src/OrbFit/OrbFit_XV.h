#pragma once
#include"stdafx.h"
namespace OrbMod
{
	class OrbFit_XV : public OrbFit, public var_3D_izo
	{
	public:
		OrbFit_XV() :OrbFit(this) {};
		OrbFit_XV(ivar * var) :OrbFit(var) {};

		virtual void setPar(vector<double> &X, Matrix &SV, double t0) override;
		virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo) override;
		virtual void endOfStep(double t0, double H, vector<double> &X, vector<double> &Y) override;
		virtual void StateLTCorr(double dt, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Y);
	};
}
