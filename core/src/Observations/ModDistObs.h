#pragma once
#include "AstroObs.h"
#include"Matrix.h"
#include"triple.h"

namespace OrbMod
{
	class ModDistObs : public Obs
	{
	public:
		ModDistObs();
		ModDistObs(const ModDistObs& otr);
		~ModDistObs();
		double dist;
		double res;
		static Algebra::Matrix dOdX;

		virtual bool tryParce(std::string s);
		virtual void updateEquations(Algebra::Matrix &A, std::vector<double> &OmC, Algebra::Matrix &x, Algebra::Matrix &dxdx0, double  tau) override;
		//void AbbCorr(int K, double dt0, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Yo) override;

		virtual std::string getType() override;
		virtual void writeResiduals() override;
		virtual ModDistObs* clone() const override;
	};
}

