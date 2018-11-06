#include"stdafx.h"
#include"seqLS.h"
namespace OrbMod
{
	//
	seqLS::seqLS()
	{
		this->fit = new batchFilter_XV();
	}
	//
	seqLS::seqLS(Variables var)
	{
		if (var == Variables::IZO_3D)
			this->fit = new batchFilter_XV();
		if (var == Variables::IZO_KS)
			this->fit = new batchFilter_KS();
	}
	//
	void seqLS::switchVar(Variables var)
	{
		if (var == Variables::IZO_3D)
			this->fit = new batchFilter_XV();
		if (var == Variables::IZO_KS)
			this->fit = new batchFilter_KS();
	}
	//
	seqLS::~seqLS()
	{
		delete fit;
	}
	//
	seqLS seqLS::inst;
	//
	void seqLS::Adjust(Matrix &SV, double t0, double &sigma, Matrix &P)
	{
		switchVar(Global::Var);
		Control::Obs_.reset();
		double t1 = t0, te;
		fit->Nbatch = 1;
		int s_o = Global::MinObsinBatch;
		uint ite = Control::Obs_.it_end;
		P = LinAlgAux::initCov(PosRMS*PosRMS, VelRMS*VelRMS);
		//
		while (Control::Obs_.it != ite +1)
		{
			int ost = ite - Control::Obs_.it;
			int offst = (ost < s_o) ? ost : s_o;
			Control::Obs_.it_end = Control::Obs_.it + offst;

			te = (Control::Obs_.last()).t;

			int failed = fit->FitBatch(SV, t1, te, sigma, P);
			if (failed) return;
			t1 = te;
		}
		//
		fo << "Nrp = " << Global::N_rp << endl;
		// PropagateToTe(SV, te);
		Matrix dxdx0, SVe;
		SVe = SV;
		Integration::Instance.Integrate(SV, te, Global::t0, dxdx0);
		Integration::Instance.Integrate(SVe, te, Global::te, dxdx0);
		fo << "\ndSV:\t" << (SV - Global::SV_start).toString("\t", "%18.12e", 18) << endl;
		fo << setprecision(9);
		fo << "\nT_e\t" << Global::te << "\tSVe\t" << SVe.toString("\t", "%18.12e", 18) << endl;
	}
}