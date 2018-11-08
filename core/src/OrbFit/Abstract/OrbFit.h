#pragma once
#include"var.h"
#include"Obs.h"
#include<fstream>

namespace OrbMod
{
	class OrbFit {
	public:
		OrbFit() {};
		OrbFit(ivar *var) { inst = var; };
		virtual ~OrbFit() {};

		static std::ofstream fo;
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
		Algebra::Matrix OrbFit::ProcessNoise(double sigSq);
		static double calcLTCorr(int observer, Algebra::triple pos, double tdb);
		std::vector<Obs*>::iterator it_0;

		virtual void Adjust(Algebra::Matrix &SV, double t0, double &sigma, Algebra::Matrix &Q) {};
		virtual int FitBatch(Algebra::Matrix &SV, double &t0, double &te, double &sigma, Algebra::Matrix &Q);
		int Nbatch;

		Algebra::Matrix getA() const { return A; }
		Algebra::Matrix getb() const { return Algebra::Matrix(OmC); }
		Algebra::Matrix getFi() const { return Fi; }

	protected:
		ivar  *inst;
		Algebra::Matrix Fi;
		//SLAY Eqs;
		Algebra::Matrix A;
		std::vector<double> OmC;
		Algebra::Matrix xi;
		double tau0;

		int Solve(Algebra::Matrix A, Algebra::Matrix b, Algebra::Matrix &x, double &sigma, Algebra::Matrix &Q);

		bool setParEq(Algebra::Matrix &sv, Algebra::Matrix &dxdx0, double  tau, double &tnext);

		virtual void StateLTCorr(double dt, 
            double H,
            std::vector<double> &X,
            std::vector< std::vector<double>> &B,
            std::vector<double> &F0, 
            std::vector<double> &P,
            std::vector<double> &Y)
        {};
		void PropagateToTe(const Algebra::Matrix &SV1, double t0);

	private:
		bool FinalizeIter(bool &isFirst);

	};
}






