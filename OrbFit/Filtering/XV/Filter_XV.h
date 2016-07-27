#pragma once
#include "OrbFit\OrbFit_XV.h"
namespace OrbMod
{

	class Filter_XV : public OrbFit_XV
	{
	public:
		Filter_XV(ivar * var);
		Filter_XV();
		~Filter_XV();

		virtual void setPar(vector<double> &X, Matrix &SV, double t0) override;
		//virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo, vector<double> &F0, vector<double> &P, vector< vector<double>> &B) override;
		virtual int  FitBatch(Matrix &SV, double &t0, double &te, double &sigma, Matrix &Q) override;
		virtual void GetX(vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0) override;
	};
}
