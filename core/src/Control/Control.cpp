#include"stdafx.h"
using namespace std;
using namespace Algebra;

namespace OrbMod
{
	//Control::Control()
	//{
	//	Obs_ = new ObsSet();
	//}
	ObsSet &Control::inst()
	{
		static ObsSet inrer;
		return inrer;
	}
	//Control::~Control()
	//{
	//	delete Obs_;
	//}
	ObsSet Control::Obs_;
	bool Control:: loadObseravations(string path, TypeOfObs OType)
	{
		return Obs_.LoadObs(path, OType);
	}
	//
	 void Control ::LogReport(std::string path)
	{
		
	}
	 bool Control ::loadKernels(std::string path)
	{
		try
		{
			furnsh_c("metak.tm");
			return true;
		}
		catch (...)
		{
			return false;
		}

	}
	 bool Control ::loadObservatories(std::string path)
	{
		if (Observatory::LoadObsrs(path))
			return true;
		else
			return false;
	}
	//
	 bool Control::loadConfig(std::string path)
	 {
		 return config::LoadCFG(path);
	 }
	 bool Control::parseTime(string s_t,TimeFormat TForm, double t )
	 {
		 if (!Misc::parceTime(s_t, TForm, t))return false;
		 else return true;	 
	 }
	 bool Control::setTime()
	 {
		 if (!Misc::parceTime(config::s_t0, Global::Tscale, Global::t0))return false;
		 if (!Misc::parceTime(config::s_te, Global::Tscale, Global::te))return false;
		 return true;

	 }
	//
	 void Control::Process(std::string path)
	 {
		 config::LoadCFG(path);
		 InitProcess();

		 StartProcess();
		 FinalizeProcess();
	 }
	 bool Control::InitProcess()
	 {
		 if (!setTime())return false;
		 Force::AccFileOpen();
		// Force::setMu(Global::mu);
		 if(Global::b_Cunn)
		 Global::GravField_CB.LoadGravityModel(Global::GravField_CB.FileModel.c_str());
		 if (Global::b_add5_cun_on)
		 Global::GravField_add5.LoadGravityModel(Global::GravField_add5.FileModel.c_str());
		 
		 return true;
	 }
	 void Control::FinalizeProcess()
	 {
		 Force::AccFileClose();
	 }
	//
	 void Control ::StartProcess()
	{
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
	 //
	 void Control::ParameterEstimation()
	 {
		 Obs_.f_res.open("residuals.out");
		 OrbFit::fo.open("Orbfit.out");
		 loadObseravations(Obs_.path, Global::ObsT);

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
		 Obs_.f_res.close();
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
		 Integration::Instance.Gauss_FODE(X, to, te, Global::step, NOR, NI, NS, NBS);
		 Integration::Instance.GetX(X, Global::SV, te, dXdX0);

	 };

	 void Control::FODE_test()
	 {
		 FILE *ft = fopen("Test.out", "w");
		 //FILE *fx = fopen("X.out", "w");
		 double dtd = Global::te - Global::t0;

		 fprintf(ft, "dt, days %f\n", dtd / 86400);

		 int Ntest = abs(log10(Global::eps));
		 int istart = -3;

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
			 Integration::Instance.Gauss_FODE(X, to, te, step, NOR, NI, NS, NBS);

			 Integration::Instance.Gauss_FODE(X, te, to, step, NOR, NI, NS, NBS);
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