#pragma once
#include "OrbFit_KS.h"
#include "Global.h"

namespace OrbMod
{
	class batchFilter_KS : public OrbFit_KS
	{
	public:
		batchFilter_KS();
		~batchFilter_KS();
	
		virtual void setPar(std::vector<double> &X, Algebra::Matrix &SV, double t0) override;
		int  FitBatch(Algebra::Matrix &SV, double &t0, double &te, double &sigma, Algebra::Matrix &Q);
		virtual void GetX(const std::vector<double> &X, Algebra::Matrix &mSV, double t0, Algebra::Matrix &dXdX0) override;
	private:
		double stepKS = Global::step;
	};
}