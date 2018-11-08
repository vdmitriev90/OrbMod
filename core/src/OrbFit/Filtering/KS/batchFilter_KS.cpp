
#include"batchFilter_KS.h"
#include"Control.h"
#include"LinAlgAux.h"
#include"Integration_.h"

using namespace Algebra;
using namespace std;

namespace OrbMod
{
	batchFilter_KS::batchFilter_KS() :OrbFit_KS(this)
	{
	}
	//
	batchFilter_KS::~batchFilter_KS()
	{
	}
	//
	void batchFilter_KS::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		var_KS_izo::setPar(X, SV, t0);
		Fi = Matrix(6, 6);
		xi = Matrix(6, 1);

		// Light-time correction
		tau0 = calcLTCorr(399, triple(SV(0, 0), SV(1, 0), SV(2, 0)), t0);

		//ObsSet::Instance().it = it_0;
		tout = Control::Obs_.curr().t;

		A.Clear();
		OmC.clear();
	}
	//
	void batchFilter_KS::GetX(const vector<double> &X, Matrix &SV, double t0, Matrix &dXdX0)
	{
		var_KS_izo::GetX(X, SV, t0, dXdX0);
	}
	//
	int batchFilter_KS::FitBatch(Matrix &SV, double &t0, double &te, double &sigma, Matrix &P)
	{
		//Output parameters
		int NS = 0;
		int NBS = 0;
		vector<double> X;
		double pe, ve;
		Matrix b, K, D, dx, x, E(6, 6), Q, sv, dxdx0, Pi = P;
		int iter = 1;
		unsigned it_0 = Control::Obs_.it;
		//Process noise
		Matrix Qpn = ProcessNoise(Qnoise);

		while (iter <= maxIterPerBatch)
		{
			Control::Obs_.it = it_0;
			string s_iter = "iter " + to_string(iter) + "\t";
			Control::Obs_.f_res << s_iter << endl;
			//fo << s_iter;
			inst->setPar(X, SV, t0);

			inst->Gauss_FODE(X, t0, te, stepKS, Global::NOR, Global::Niter, NS, NBS);
			
			Global::IsAutoStep = false;
			Matrix A = getA();
			Matrix b = getb();
            size_t n = b.Size();

			if (!Solve(A, b, x, sigma, Q)) return 1;

			Matrix At = A.Transpose();

			Matrix R(n, n);
			R.Identy();
			sigma = Control::Obs_.sigma;
			R *= (sigma*sigma);

			//if (Nbatch == 1)
			//{
			//	Pi = Q;
			//	dx = Pi*At*b;
			//}
			//else
			{
				K = Pi*At*(A*Pi*At + R).Inverse();
				D = E - K*A;
				Pi = D*Pi + Qpn;
				dx = K*b;
			}
			//fo << "\nP\n" << (P).toString("\t", "%20.12e", 25, true) << endl;
			SV += dx;

			Matrix RMS = LinAlgAux::CalcRMS(sigma, Q, pe, ve);
			fo << "dx\t" << dx.MaxMod()/*.toString("\t", "%f", 25)*/ << "N pr\t" << Global::N_rp << " " << b.Size() << " Q " << Pi.Trace() << " sigma " << sigma << " pRMS " << pe << " vRMS " << ve << " stepKS " << stepKS << endl;
			//fo << "Fi\n" << Fi.toString("\t", "%e", 20, 1)<<endl;

			if (x.MaxMod() < epsIter*SV.MaxMod()) break;
			iter++;
		}
		//
		P = Pi;
		//state and covariance propagation
		P = Fi*P*Fi.Transpose();

		unsigned npr_store = Global::N_rp;
		Global::step = stepKS;
		Integration::Instance.Integrate(SV, t0, te, dxdx0);
		Global::N_rp = npr_store;

		Nbatch++;
		return 0;
	}
}