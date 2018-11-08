#pragma once
#include"Observations.h"
namespace OrbMod
{
	class AstroObs : public Observations
	{
	public:
		AstroObs();
		AstroObs(const AstroObs& otr);
		~AstroObs();

		static Algebra::Matrix dOdX;

		//fields
		double ra;
		double dra;

		double dec;
		double ddec;

		double res_ra;
		double res_del;

		//methods
		virtual	bool tryParce(std::string s);
		virtual void updateEquations(Algebra::Matrix &A, std::vector<double> &OmC, Algebra::Matrix &x, Algebra::Matrix &dxdx0, double  tau) override;
		//void AbbCorr(int K, double dt0, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Yo) override;
		virtual std::string getType() override;
		virtual void writeResiduals() override;
		virtual bool isOutlier() override;
		virtual void abCorr(double pos[]);
		virtual obs_ptr clone() const override;

	};
}
