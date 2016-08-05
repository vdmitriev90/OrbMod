#include "stdafx.h"
#include "Filter_XV.h"
namespace OrbMod
{
	//
	Filter_XV::Filter_XV(ivar * var) :OrbFit_XV(var) {};
	Filter_XV::Filter_XV() :OrbFit_XV(this)
	{
	}
	//
	Filter_XV::~Filter_XV()
	{
	}
	//
	void Filter_XV::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		var_3D_izo::setPar(X, SV, t0);
		Fi = Matrix(6, 6);
		xi = Matrix(6, 1);
		// Light-time correction
		tau0 = calcLTCorr(399, triple(X[0], X[1], X[2]), t0);

		//ObsSet::Instance().it = it_0;
		tout = (*Control::Obs_.it)->t;

		A.Clear();
		OmC.clear();
	}
	//
	void Filter_XV::GetX(vector<double> &X, Matrix &SV, double t0, Matrix &dXdX0)
	{
		var_3D_izo::GetX(X, SV, t0, dXdX0);
	}
	//
	int  Filter_XV::FitBatch(Matrix &SV, double &t0, double &te, double &sigma, Matrix &Q)
	{
		//Output parameters
		int NS = 0;
		int NBS = 0;
		vector<double> X;

		Matrix dxdx0;
		//ObsSet::Instance().f_res << Nbatch << "\t";
		inst->setPar(X, SV, t0);
		inst->FODE(X, t0, te, Global::step, Global::NOR, Global::Niter, NS, NBS);
		inst->GetX(X, SV, t0, dxdx0);

		Nbatch++;
		return 0;
	}
}
//

