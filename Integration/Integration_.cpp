#include"stdafx.h"
#include"Integration_.h"
namespace OrbMod
{
	Integration Integration::Instance;
	void Integration::SwitchVar(Variables V)
	{
		delete var;
		switch (V)
		{
		case Variables::FODE_2D: this->var = new var_2D();
			break;
		case Variables::FODE_3D: this->var = new var_3D();
			break;
		case Variables::IZO_3D:	this->var = new var_3D_izo();
			break;
		case Variables::FODE_KS: this->var = new var_KS();
			break;
		case Variables::IZO_KS: this->var = new var_KS_izo();
			break;
		case Variables::FODE_SB: this->var = new var_SB();
			break;
		case Variables::IZO_SB: this->var = new var_SB_izo();
			break;
		case Variables::FinDiff: this->var = new OrbFit_FinDiff();
			break;

		default:
			return;
		}

		this->N = var->N;
		this->Niter = var->Niter;
	};

	void Integration::setPar(vector<double> &X, Matrix &mSV, double t0)
	{
		var->setPar(X, mSV, t0);
		if (Global::Discr != 0) streamsOpen();
	}
	void Integration::GetX(vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0)
	{
		if (Global::Discr != 0) streamsClose();
		var->GetX(X, mSV, t0, dXdX0);
	}
	bool Integration::Inter(double t0, double H, vector<double> &X, vector<double> &Yo)
	{
		return var->Inter(t0, H, X, Yo);
	}
	void Integration::force(const double Ti, const vector<double> &X, vector<double> &dXds)
	{
		var->force(Ti, X, dXds);
	}
	int Integration::FODE(vector<double> &X, double to, double &te, double &step, int NOR, int NI, int &NS, int &NBS)
	{
		return var->FODE(X, to, te, step, NOR, NI, NS, NBS);
	}
	//
	void Integration::Integrate(Matrix &SV, double t0, double te, Matrix &dXdX0)
	{
		//Output parameters
		int NS = 0;
		int NBS = 0;
		vector<double> X;
		Integration::Instance.SwitchVar(Global::Var);
		Integration::Instance.setPar(X, SV, t0);
		Integration::Instance.FODE(X, t0, te, Global::step, Global::NOR, Global::Niter, NS, NBS);
		Integration::Instance.GetX(X, SV, te, dXdX0);
	}
	//
	void Integration::Integrate(Matrix &SV, double t0, double te, Matrix &dXdX0, Variables var)
	{
		//Output parameters
		int NS = 0;
		int NBS = 0;
		vector<double> X;
		Integration::Instance.SwitchVar(var);
		Integration::Instance.setPar(X, SV, t0);
		Integration::Instance.FODE(X, t0, te, Global::step, Global::NOR, Global::Niter, NS, NBS);
		Integration::Instance.GetX(X, SV, te, dXdX0);
	}
	//void Integration::Integrate(Matrix &SV, double t0, double te, Matrix &dXdX0, Matrix &dxdx0)
	//{
	//	//Output parameters
	//	int NS = 0;
	//	int NBS = 0;
	//	vector<double> X;
	//	Integration::Instance.SwitchVar(Global::Var);
	//	Integration::Instance.setPar(X, SV, t0);
	//	Integration::Instance.FODE(X, t0, te, Global::step, Global::NOR, Global::Niter, NS, NBS);
	//	Integration::Instance.GetX(X, SV, te, dXdX0);
	//	//Integration::
	//}
}
