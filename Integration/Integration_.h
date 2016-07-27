#pragma once
#include"stdafx.h"
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
		virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo, vector<double> &F0, vector<double> &P, vector< vector<double>> &B)override;
		virtual void FODE(vector<double> &X, double to, double &te, double &step, int NOR, int NI, int &NS, int &NBS) override;
		void		 Integrate(Matrix &SV, double t0, double te, Matrix &dXdX0);
		void	 	 Integrate(Matrix &SV, double t0, double te, Matrix &dXdX0, Variables var);
		void SODE();

		void write(double t0, triple X, triple V, double TimeNode, double NodeA);
		void write_3_BodyFix_sv(FILE*f, char* UTC, double t, double Ti, triple X, triple V);
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
		FILE * fosv, *foel, *foSvEcl, *foelEcl, *fosvR, *foelR, *fosvp, *foelp, *foBL, *foNEU, *foAZR, *fvisi, *fo3bg, *fodbg;
	};
}
