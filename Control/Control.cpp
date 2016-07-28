#include"stdafx.h"
using namespace std;
using namespace Algebra;

namespace OrbMod
{

	 void Control ::Process()
	{
		//Erase the file with accelerations
		FILE*facc = fopen("acc.out", "w");
		fclose(facc);

		Force::setMu();

		Global::N_rp = 0;
		Global::start = clock();
		//OrbFit::fo.open("Orbfit.out");
		Integration::Instance.SwitchVar(Global::Var);
		Global::SV_start = Global::SV;

		if (Global::mode == Mode::bw_fw_test)
			FODE_test();
		else if (Global::mode == Mode::Propagation)
		{
			if (Global::Var == Variables::SODE_XV)
				Integration::Instance.SODE();
			else
				FODE();
		}
		else if (Global::mode == Mode::Adjust)
			ParameterEstimation();
		else if (Global::mode == Mode::Debug)
			debugAction4();
		//OrbFit::fo.close();
	}
	 void Control::ParameterEstimation()
	 {
		 ObsSet::Instance().f_res.open("residuals.out");
		 OrbFit::fo.open("Orbfit.out");
		 double sigma;

		 switch (Global::fitMode)
		 {
		 case FitMode::LS:
			 batchFitting::instance.Adjust(Global::SV, Global::t0, sigma, Global::Q);
			 break;
		 case FitMode::batch_LS_filer:
			 seqLS::inst.Adjust(Global::SV, Global::t0, sigma, Global::Q);
			 break;
		 case FitMode::pure_Kalman:
			 pureKalman_XV::instance.Adjust(Global::SV, Global::t0, sigma, Global::Q);
			 break;
		 case FitMode::hybrid_Kalman:
			 hibridKalman_XV::instance1.Adjust(Global::SV, Global::t0, sigma, Global::Q);
			 break;
		 default:
			 break;
		 }
		 ObsSet::Instance().f_res.close();
		 OrbFit::fo.close();
	 }
	 void Control::FODE()
	 {
		 const int  NOR = Global::NOR;
		 double to = Global::t0;
		 double te = Global::te;

		 //max number of iterations
		 int NI = Global::Niter;
		 //Output parameters
		 int NS = 0;
		 int NBS = 0;
		 vector<double> X;

		 Matrix dXdX0;

		 Integration::Instance.setPar(X, Global::SV, to);
		 Integration::Instance.FODE(X, to, te, Global::step, NOR, NI, NS, NBS);
		 Integration::Instance.GetX(X, Global::SV, te, dXdX0);

	 };
	 void Control::FODE_test()
	 {
		 FILE *ft = fopen("Test.out", "w");
		 //FILE *fx = fopen("X.out", "w");
		 double dtd = Global::te - Global::t0;

		 fprintf(ft, "dt, days %f\n", dtd / 86400);

		 int Ntest = abs(log10(Global::eps));
		 int istart = -6;

		 for (int i = istart; i <= Ntest; i++)
		 {
			 const int  NOR = Global::NOR;
			 double to = Global::t0;
			 double te = Global::te;
			 double step = Global::step;

			 //double err = Global::eps;
			 Global::eps = pow(10, -i);

			 //max number of iterations
			 int NI = Global::Niter;
			 //Output parameters
			 int NS = 0;
			 int NBS = 0;
			 vector<double> X;
			 Matrix SV = Global::SV;
			 Matrix SVfinal;

			 Matrix dXdX0;

			 Global::N_rp = 0;

			 Integration::Instance.setPar(X, SV, to);
			 Integration::Instance.FODE(X, to, te, step, NOR, NI, NS, NBS);

			 Integration::Instance.FODE(X, te, to, step, NOR, NI, NS, NBS);
			 Integration::Instance.GetX(X, SVfinal, te, dXdX0);

#pragma region Output

			 fprintf(ft, "%e\t", Global::eps);
			 double dr = 0;
		
			 Matrix dX = SV - SVfinal;
			 //fprintf(ft, dX.toString("\t","%21.12e",30).c_str());
			 for (size_t i = 0; i < 3; i++) dr += SQR(dX(i, 0));

			 //fprintf(ft, " IZO\t");
			 double maxIZO = 0;
			 for (int i = 0; i < dXdX0.nRows(); i++)
				 for (int j = 0; j < dXdX0.nCols(); j++)
				 {
					 double val = dXdX0(i, j);
					 //fprintf(ft, "%21.12e\t", val);
					 if (i == j) val -= 1.0;
					 maxIZO = (maxIZO>abs(val)) ? maxIZO : abs(val);
				 }
		
			 fprintf(ft, "%d\t%21.12e\t%21.12e\n", Global::N_rp, sqrt(dr), maxIZO);
#pragma endregion

		 }
		 fclose(ft);
		 //fclose(fx);
	 };
}