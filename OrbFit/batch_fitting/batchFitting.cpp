#include "stdafx.h"
namespace OrbMod
{
	batchFitting::batchFitting()
	{
		this->fit = new OrbFit_XV();
	}

	batchFitting::~batchFitting()
	{
		delete fit;
	}
	batchFitting batchFitting::instance;

	void batchFitting::SwitchVar(Variables V)
	{
		delete fit;
		switch (V)
		{
		case Variables::IZO_3D: this->fit = new OrbFit_XV();
			break;
		case Variables::IZO_KS: this->fit = new OrbFit_KS();
			break;
		case Variables::IZO_SB: this->fit = new OrbFit_SB();
			break;
		case Variables::FinDiff: this->fit = new OrbFit_FinDiff();
			break;
		default:
			return;
		}
	};
	//
	void batchFitting::Adjust(Matrix &SV, double t0, double &sigma, Matrix &Q)
	{
		SwitchVar(Global::Var);
		if (Global::Var == Variables::FinDiff)
		{
			double sigma;
			fit->Adjust(SV, Global::t0, sigma, Global::Q);
		}
		else
		{
			fit->Nbatch = 1;
			fo << SV.toString("\t", "%21.16f", 35) << endl;

			double te = (Control::Obs_).last().t;

			fit->FitBatch(SV, t0, te, sigma, Q);
			double pe, ve;
			Matrix RMS = LinAlgAux::CalcRMS(sigma, Q, pe, ve);

			//PropagateToTe(Matrix(SV), Global::t0);
			Matrix dxdx0, SVe;
			SVe = SV;

			Integration::Instance.Integrate(SVe, Global::t0, Global::te, dxdx0);
			fo << setprecision(9);
			fo << "dSV\t" << (SV - Global::SV_start).toString("\t", "%18.12e", 35) << endl;
			fo << "\nT_e\t" << Global::te << "\tSVe\t" << SVe.toString("\t", "%18.12e", 18) << endl;
			fo << setprecision(3);
			fo << "SV\t" << SV.toString("\t", "%19.12f", 20) << "\tNumobs\t" << fit->getb().Size() << "\tsigma\t" << sigma << " pRMS " << pe << " vRMS " << ve << endl;
			fo << "Nrp = " << Global::N_rp << endl;
			fo << "RMS\t" << RMS.toString("\t", "%12.6e", 20) << endl;
			fo << "P prime diag\n" << (Q.PrimeDiag().Transpose()).toString("\t", "%e", 25, true) << endl;
			fo << "Q\n" << Q.toString("\t", "%18.10e", 20, true) << endl;
			fo << "Fi\n" << dxdx0.toString("\t", "%18.10e", 20, true) << endl;
			Q = dxdx0*Q*dxdx0.Transpose();
			RMS = LinAlgAux::CalcRMS(sigma, Q, pe, ve);
			fo << "RMS(te)\n" << RMS.toString("\t", "%18.12e", 18) << endl;
			//
			for (int i = 0; i < 6; i++)
				config::SV[i] = SV(i, 0);

		}
	}
}