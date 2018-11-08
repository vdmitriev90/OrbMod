#pragma once
#include"Matrix.h"

typedef  std::vector<double> vd;
typedef  std::vector<std::vector<double>> vvd;

namespace OrbMod
{
	class ivar {


	public:
		ivar();
		virtual ~ivar();
		int K, N, Niter;
		double tout, te;
		double tizo, dtr;

		virtual void setPar(std::vector<double> &X, Algebra::Matrix &mSV, double t0) = 0;
		virtual void GetX(const std::vector<double> &X, Algebra::Matrix &mSV, double t0, Algebra::Matrix &dXdX0) = 0;
		virtual void force(const double Ti, const std::vector<double> &X, std::vector<double> &dXds) = 0;
		virtual bool Inter(double t0, double H, std::vector<double> &X, std::vector<double> &Yo) = 0;
		void stepDs(double ds, double S, std::vector<double> &X, std::vector<double> &Y);

		virtual int Gauss_FODE(std::vector<double> &X, double to, double &te, double &step, int NOR, int NI, int &NS, int &NBS);
		//virtual void substep(double s, )
		virtual void endOfStep(double t0, double H, std::vector<double> &X, std::vector<double> &Y);
	private:
		FILE *fodbg;
		std::vector<std::vector<double>> BL;
		const double EPS = 1e-15;
		const double SGM = 3.16;
		bool vs, ls;
		double	H, err;
		std::vector<double> XK;
		int ivar::Init(double &H_, double &dir, double &R, double &to, std::vector<double> X, std::vector<double> Y, double &B_);
	protected:

		std::vector<std::vector<double>>  B;
		std::vector<double> F0, F, P;

	};
}