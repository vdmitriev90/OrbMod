#pragma once
#include "OrbFit_XV.h"
namespace OrbMod
{
	class Filter_XV : public OrbFit_XV
	{
	public:
		Filter_XV(ivar * var);
		Filter_XV();
		~Filter_XV();

		virtual void setPar(std::vector<double> &X, Algebra::Matrix &SV, double t0) override;
		//virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo, vector<double> &F0, vector<double> &P, vector< vector<double>> &B) override;
		virtual int  FitBatch(Algebra::Matrix &SV, double &t0, double &te, double &sigma, Algebra::Matrix &Q) override;
		virtual void GetX(const std::vector<double> &X, Algebra::Matrix &mSV, double t0, Algebra::Matrix &dXdX0) override;
	};
}

