#pragma once
#include "OrbFit\OrbFit_KS.h"

namespace OrbMod
{
	class Orbfit_KS;
	class batchFilter_KS : public OrbFit_KS
	{
	public:
		batchFilter_KS();
		~batchFilter_KS();

		virtual void setPar(vector<double> &X, Matrix &SV, double t0) override;
		int  FitBatch(Matrix &SV, double &t0, double &te, double &sigma, Matrix &Q);
		virtual void GetX(vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0) override;
	};
}