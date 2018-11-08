#pragma once
#include"var.h"
#include"OrbFit.h"

namespace OrbMod
{
	class OrbFit_XV : public OrbFit, public var_3D_izo
	{
	public:
		OrbFit_XV() :OrbFit(this) {};
		OrbFit_XV(ivar * var) :OrbFit(var) {};

		virtual void setPar(std::vector<double> &X, Algebra::Matrix &SV, double t0) override;
		virtual bool Inter(double t0, double H, std::vector<double> &X, std::vector<double> &Yo) override;
		virtual void endOfStep(double t0, double H, std::vector<double> &X, std::vector<double> &Y) override;
		virtual void StateLTCorr(double dt, double H, std::vector<double> &X, std::vector< std::vector<double>> &B, std::vector<double> &F0, std::vector<double> &P, std::vector<double> &Y);
	};
}
