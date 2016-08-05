#include "stdafx.h"
#include "pureKalman_XV.h"
namespace OrbMod
{
	//
	pureKalman_XV pureKalman_XV::instance;

	//
	pureKalman_XV::pureKalman_XV()
	{
		this->fit = new Filter_XV();
	}
	//
	pureKalman_XV::~pureKalman_XV()
	{
		delete fit;
	}

	//Process noise
	void pureKalman_XV::InitFilter(Matrix &SV, double t0, double &sigma, Matrix &P)
	{

		sigma = Control::Obs_.sigma;
		P = LinAlgAux::initCov(PosRMS*PosRMS, VelRMS*VelRMS);
	}
	//
	//void pureKalman_XV::SwitchVar(Variables V)
	//{
	//	delete fit;
	//	switch (V)
	//	{
	//	case Variables::IZO_3D: this->fit = new Filter_XV();
	//		break;
	//	case Variables::IZO_KS: this->fit = new OrbFit_KS();
	//		break;
	//	case Variables::IZO_SB: this->fit = new OrbFit_SB();
	//		break;
	//	default:
	//		return;
	//	}
	//};
	void pureKalman_XV::Adjust(Matrix &SV, double t0, double &sigma, Matrix &P)
	{
		double te;
		Matrix  K, E(6, 6), A, b, dx;
		E.Identy();

		//Process noise
		Matrix Q = ProcessNoise(Qnoise);

		Global::SV_start = SV;

		InitFilter(SV, t0, sigma, P);
		Control::Obs_.reset();

		fit->Nbatch = 1;

		while (Control::Obs_.it != Control::Obs_.it_end + 1)
		{
			te = (*(Control::Obs_.it))->t;

			fo << "Batch " << fit->Nbatch;
			int  failed = fit->FitBatch(SV, t0, te, sigma, P);
			if (failed) return;

			Matrix b = fit->getb();
			Matrix H = fit->getA();
			Matrix Fi = fit->getFi();
			int n = b.nRows();

			if (n != 0)
			{
				Matrix _P = Fi*P*Fi.Transpose();
				Matrix Ht = H.Transpose();

				Matrix R(n, n);
				R.Identy();
				R *= (sigma*sigma);

				Matrix K = _P*Ht*(H*_P*Ht + R).Inverse();
				P = (E - K*H)*_P;
				P += Q;
				dx = K*b;
				SV = SV + dx;
			}
			t0 = te;
			fo << setprecision(8);
			fo << "\tdX:\t" << StVec(dx).X().getAbs() << " P " << P.PrimeDiag().MaxMod() << "\tK\t " << K.MaxMod() << "\tn\t" << n << endl;
		}
		fo << "SV\t" << (SV).toString("\t", "%21.16f", 35) << "\tNbatch\t" << fit->Nbatch << endl;
		fo << "P\n" << (P).toString("\t", "%20.12e", 25, true) << endl;

		//PropagateToTe(SV, te);
		Matrix dxdx0, SVe;
		SVe = SV;
		Integration::Instance.Integrate(SV, te, Global::t0, dxdx0);
		Integration::Instance.Integrate(SVe, te, Global::te, dxdx0);

		fo << "\ndSV:\t" << (SV - Global::SV_start).toString("\t", "%18.12e", 18) << "Nrp = " << Global::N_rp << endl;
		fo << setprecision(9);
		fo << "\nT_e\t" << Global::te << "\tSVe\t" << SVe.toString("\t", "%18.12e", 18) << endl;
	}
	//
	Obsiter pureKalman_XV::getLastObs(double t, double dt)
	{
		double t1 = t + dt;
		Obsiter it1 = Control::Obs_.FindTime(t1);

		while ((it1 - Control::Obs_.it) <= Global::MinObsinBatch)
			it1++;

		int d = Control::Obs_.it_end - it1;
		Obsiter iout = (d <= Global::MinObsinBatch) ? Control::Obs_.it_end : it1;
		return iout;
	}
}