#pragma once
#include"stdafx.h"
namespace OrbMod
{
	class OrbFit_SB : public OrbFit, public var_SB_izo
	{
	public:
		virtual void setPar(vector<double> &X, Matrix &SV, double t0) override;
		virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo) override;

		virtual void StateLTCorr(double dt0, double H, vector<double> &X, vector<double> &Yo) {};
	};
}
