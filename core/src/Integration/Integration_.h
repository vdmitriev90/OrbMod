#pragma once
#include"var.h"
#include"triple.h"
#include"constant.h"

#include<vector>
#include<fstream>

namespace OrbMod
{
	class Integration : public ivar
	{
	public:
		//
		static  Integration Instance;

		virtual void setPar(std::vector<double> &X, Matrix &mSV, double t0) override;
		virtual void GetX(const std::vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0) override;
		virtual void force(const double Ti, const std::vector<double> &X, std::vector<double> &dXds) override;
		virtual bool Inter(double t0, double H, std::vector<double> &X, std::vector<double> &Yo)override;
		virtual int Gauss_FODE(std::vector<double> &X, double to, double &te, double &step, int NOR, int NI, int &NS, int &NBS) override;
		void Integrate(Matrix &SV, double t0, double te, Matrix &dXdX0);
		void Integrate(Matrix &SV, double t0, double te, Matrix &dXdX0, consts::Variables var);
		void SODE();

		void write(double t0, Algebra::triple X, Algebra::triple V);
		void write_3_BodyFix_sv(FILE*f, char* UTC, double t, Algebra::triple X, Algebra::triple V);
		void SwitchVar(consts::Variables V);

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

