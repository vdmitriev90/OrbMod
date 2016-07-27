#pragma once
#include"stdafx.h"
using namespace Algebra;

namespace OrbMod
{
	class OrbFit {
	public:
		OrbFit() {};
		OrbFit(ivar *var) { inst = var; };
		virtual ~OrbFit() {};

		static ofstream fo;
		//numbers of iteration 
		static int maxIter;
		static int maxIterPerBatch;
		//converjence epsilon
		static double epsIter;

		//outlier rejection
		static bool isRejOuts;
		static float OutlsThresh;
		static bool isMemOuts;
		//position and velocity RMS
		static double PosRMS, VelRMS, Qnoise;
		Matrix OrbFit::ProcessNoise(double sigSq);
		static double calcLTCorr(int observer, triple pos, double tdb);
		vector<Obs*>::iterator it_0;

		virtual void Adjust(Matrix &SV, double t0, double &sigma, Matrix &Q) {};
		virtual int FitBatch(Matrix &SV, double &t0, double &te, double &sigma, Matrix &Q);
		int Nbatch;

		Matrix  getA() const { return A; }
		Matrix getb() const { return Matrix(OmC); }
		Matrix getFi() const { return Fi; }

	protected:
		ivar  *inst;
		Matrix Fi;
		//SLAY Eqs;
		Matrix A;
		vector<double> OmC;
		Matrix xi;
		double tau0;

		int Solve(Matrix A, Matrix b, Matrix &x, double &sigma, Matrix &Q);

		bool setParEq(Matrix &sv, Matrix &dxdx0, double  tau, double &tnext);
		virtual void StateLTCorr(double dt, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Y) {};
		void PropagateToTe(const Matrix &SV1, double t0);

	private:
		bool FinalizeIter(bool &isFirst);

	};
}





