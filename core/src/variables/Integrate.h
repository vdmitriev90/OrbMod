#pragma once
using namespace std;
using namespace Algebra;

typedef  vector<double> vd;
typedef  vector<vector<double>> vvd;
namespace OrbMod
{
	class ivar {


	public:
		ivar();
		virtual ~ivar();
		int K, N, Niter;
		double tout, te;
		double tizo, dtr;

		virtual void setPar(vector<double> &X, Matrix &mSV, double t0) = 0;
		virtual void GetX(const vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0) = 0;
		virtual void force(const double Ti, const vector<double> &X, vector<double> &dXds) = 0;
		virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo) = 0;
		void stepDs(double ds, double S, vector<double> &X, vector<double> &Y);

		virtual int Gauss_FODE(vector<double> &X, double to, double &te, double &step, int NOR, int NI, int &NS, int &NBS);
		//virtual void substep(double s, )
		virtual void endOfStep(double t0, double H, vector<double> &X, vector<double> &Y);
	private:
		FILE *fodbg;
		vector<vector<double>> BL;
		const double EPS = 1e-15;
		const double SGM = 3.16;
		bool vs, ls;
		double	H, err;
		vector<double> XK;
		int ivar::Init(double &H_, double &dir, double &R, double &to, vector<double> X, vector<double> Y, double &B_);
	protected:

		vector<vector<double>>  B;
		vector<double> F0, F, P;

	};
}