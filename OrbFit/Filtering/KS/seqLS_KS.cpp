#include "stdafx.h"
#include "seqLS_KS.h"
namespace OrbMod
{
	seqLS_KS::seqLS_KS()
	{
		this->fit = new batchFilter_KS();
	}

	seqLS_KS::~seqLS_KS()
	{
		delete fit;
	}
	//
	void seqLS_KS::Adjust(Matrix &SV, double t0, double &sigma, Matrix &P)
	{
		Control::Inst.Obs_->reset();
		double t1 = t0, te;
		fit->Nbatch = 1;
		int s_o = Global::MinObsinBatch;
		Obsiter ite = Control::Inst.Obs_->it_end;

		while (Control::Inst.Obs_->it != ite + 1)
		{
			int ost = ite - Control::Inst.Obs_->it;
			int offst = (ost < s_o) ? ost : s_o;
			Control::Inst.Obs_->it_end = Control::Inst.Obs_->it + offst;

			te = (*Control::Inst.Obs_->it_end)->t;

			int IsFitSucces = fit->FitBatch(SV, t1, te, sigma, P);
			t1 = te;
		}
		Matrix dxdx0;
		Integration::Instance.Integrate(SV, te, Global::t0, dxdx0);
		fo << "\ndSV:\t" << (SV - Global::SV_start).toString("\t", "%18.12e", 18) << "Nrp = " << Global::N_rp << endl;
	}
}