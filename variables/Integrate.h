#pragma once
using namespace std;
namespace OrbMod
{

	typedef  vector<double> vd;
	typedef  vector<vector<double>> vvd;

	class ivar {
	public:
		ivar();
		virtual ~ivar();
		int K, N, Niter;
		double tout, te;
		double tizo, dtr;

		virtual void setPar(vector<double> &X, Matrix &mSV, double t0) = 0;
		virtual void GetX(vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0) = 0;
		virtual void force(const double Ti, const vector<double> &X, vector<double> &dXds) = 0;
		virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo, vector<double> &F0, vector<double> &P, vector<vector<double>> &B) = 0;
		void stepDs(double ds, double S, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Y);
		virtual void FODE(vector<double> &X, double to, double &te, double &step, int NOR, int NI, int &NS, int &NBS);
		//virtual void substep(double s, )
		virtual void endOfStep(double t0, double H, vector<double> &X, vector<double> &Y, vector<double> &F0, vector<double> &P, vector<vector<double>> &B);
	};
}