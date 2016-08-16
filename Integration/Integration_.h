#pragma once
#include"stdafx.h"

#include"Parameters\constant.h"
using namespace Consts;

namespace OrbMod
{
	class Integration : public ivar
	{
	public:
		//
		static  Integration Instance;

		virtual void setPar(vector<double> &X, Matrix &mSV, double t0) override;
		virtual void GetX(vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0) override;
		virtual void force(const double Ti, const vector<double> &X, vector<double> &dXds) override;
		virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo)override;
		virtual int FODE(vector<double> &X, double to, double &te, double &step, int NOR, int NI, int &NS, int &NBS) override;
		void		 Integrate(Matrix &SV, double t0, double te, Matrix &dXdX0);
		void	 	 Integrate(Matrix &SV, double t0, double te, Matrix &dXdX0, Variables var);
		void SODE();

		void write(double t0, triple X, triple V);
		void write_3_BodyFix_sv(FILE*f, char* UTC, double t, triple X, triple V);
		void SwitchVar(Variables V);

		//

		Integration() :var(new var_3D()) {}
		//
		virtual ~Integration() {
			delete var;
		}
	private:
		ivar *var;
		void streamsOpen();
		void streamsClose();
		FILE * fosv, *foel, *foSvEcl, *foelEcl, *fosvR, /**foelR, *fosvp, *foelp,*/ *foBL, *foNEU,  *fvisi, *fo3bg, *fodbg;
	};
}

