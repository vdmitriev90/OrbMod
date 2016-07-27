#include"stdafx.h"
#include"OrbFit.h"
using namespace std;
using namespace Algebra;


namespace OrbMod
{
	//
	ofstream		OrbFit::fo;
	//numbers of iteration 
	int				OrbFit::maxIter = 1;
	int				OrbFit::maxIterPerBatch = 1;
	//converjence epsilon
	double			OrbFit::epsIter = 1e-7;

	//outlier rejection
	bool			OrbFit::isRejOuts = false;
	float			OrbFit::OutlsThresh = 3.0;
	bool			OrbFit::isMemOuts = false;

	//position and velocity RMS
	double			OrbFit::PosRMS;
	double			OrbFit::VelRMS;
	//process noise
	double			OrbFit::Qnoise = 1;
	//
	Matrix OrbFit::ProcessNoise(double sigSq)
	{
		Matrix Q(6, 6);
		Q.Identy();
		for (size_t i = 0; i < 3; i++)
		{
			Q(i, i) *= sigSq;
			Q(i + 3, i + 3) *= (sigSq / 1000);
		}

		return Q;
	}
	double OrbFit::calcLTCorr(int observer, triple pos, double tdb)
	{
		double lt, sv[3];
		spkgps_c(observer, tdb, "J2000", Global::IDC, sv, &lt);
		triple pr;
		for (int i = 0; i < 3; i++) pr[i] = pos[i] - sv[i];
		double tau = pr.getAbs() / SoL;
		return tau;
	}
	//
	int OrbFit::Solve(Matrix A, Matrix b, Matrix &x, double &sigma, Matrix &Q)
	{
		int M = A.nCols();
		int N = A.nRows();
		if (N < 6 || M < 6)
		{
			fo << "Number of observations isn't enough for parameter estimation. Processing stopped. N=" << N << " M=" << M << endl;
			return 0;
		}

		if (!LinAlgAux::LSSolve(A, b, x, sigma, Q))
		{
			fo << "Failed to produce parameters estimation. Processing is stopped." << endl;
			return 0;
		}

		Matrix RMS = LinAlgAux::CalcRMS(sigma, Q);
		return 1;
	}
	//
	void OrbFit::PropagateToTe(const Matrix &SV1, double t0)
	{
		Matrix dxdx0;
		double te_ = Global::te;
		Matrix SV2 = SV1;
		Integration::Instance.Integrate(SV2, t0, te_, dxdx0);
		string t_out;
		Misc::et2cal(te_, t_out);
		OrbFit::fo << "\nT_e\t" << t_out << "\tSV\t" << SV2.toString("\t", "%18.12e", 18) << endl;
	}
	//
	bool OrbFit::setParEq(Matrix &sv, Matrix &dxdx0, double  tau, double &tnext)
	{
		string obsid = (*ObsSet::Instance().it)->observ.ID;
		//если обсерватория отмечена для использования
		if (ObsSet::Instance().isUseObs[obsid])
			//вызов процедуры-конструктора параметрических уравнений (матрица А и вектор О-С)
			(*ObsSet::Instance().it)->setParEq(A, OmC, sv, dxdx0, tau);

		ObsSet::Instance().it++;
		int b = 0;
		if (ObsSet::Instance().it == ObsSet::Instance().it_end + 1)
			b = 1;
		if (ObsSet::Instance().it != ObsSet::Instance().obs.end())
			tnext = (*ObsSet::Instance().it)->t;

		return b;
	}
	//
	int OrbFit::FitBatch(Matrix &SV, double &t0, double &te, double &sigma, Matrix &Q)
	{
		//Output parameters
		int NS = 0;
		int NBS = 0;
		vector<double> X;
		double pe, ve;
		Matrix x;
		int iter = 1;
		ObsSet::Instance().isConverg = false;
		bool isFirst = true;

		while (iter <= maxIter)
		{
			string s_iter = "iter " + to_string(iter) + "\t";
			ObsSet::Instance().f_res << s_iter << endl;
			ObsSet::Instance().Nouts = 0;

			inst->setPar(X, SV, t0);
			inst->FODE(X, t0, te, Global::step, Global::NOR, Global::Niter, NS, NBS);
			//
			if (!Solve(A, Matrix(OmC), x, sigma, Q)) return 1;
			SV += x;

			Matrix RMS = LinAlgAux::CalcRMS(sigma, Q, pe, ve);
			fo << iter << "--\n" << "dx " << x.toString("\t", "%f", 25) << endl;
			fo << "N_rp " << Global::N_rp << "\tN obs " << OmC.size() << " sigma " << sigma*ObsSet::fct << " pRMS " << pe << " vRMS " << ve << endl;
			//
			ObsSet::Instance().sigma = sigma;

			ObsSet::Instance().isConverg = x.MaxMod() < epsIter*SV.MaxMod();
			if (!isFirst) 	ObsSet::Instance().isConverg = true;
			//
			if (FinalizeIter(isFirst)) break;
			iter++;
		}

		Nbatch++;
		return 0;
	}
	//false == continue;
	//true == break;
	bool OrbFit::FinalizeIter(bool &isFirst)
	{
		static int Nouts_pre = 0;
		if (ObsSet::Instance().isConverg)
		{
			if (!isRejOuts)
				return true;
			else
				if (isFirst)
				{
					isFirst = false;
					return false;
				}
				else
				{
					if (ObsSet::Instance().Nouts == Nouts_pre) return true;
					else
					{
						Nouts_pre = ObsSet::Instance().Nouts;
						return false;
					}
				}
		}
		else
		{
			return false;
		}
	}
}
