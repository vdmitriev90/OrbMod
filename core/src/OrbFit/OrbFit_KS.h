#pragma once
#include"OrbFit.h"

namespace OrbMod
{
	class OrbFit_KS : public OrbFit, public var_KS_izo
	{
	public:
		OrbFit_KS(ivar * var) :OrbFit(var) {};
		OrbFit_KS() :OrbFit(this) {};
		virtual void setPar(std::vector<double> &X, Algebra::Matrix &SV, double t0) override;
		virtual bool Inter(double t0, double H, std::vector<double> &X, std::vector<double> &Yo) override;
		virtual void endOfStep(double t0, double H, std::vector<double> &X, std::vector<double> &Y) override;
		virtual void StateLTCorr(double dt0, double H, std::vector<double> &X, std::vector< std::vector<double>> &B, std::vector<double> &F0, std::vector<double> &P, std::vector<double> &Yo)override;
	};
}