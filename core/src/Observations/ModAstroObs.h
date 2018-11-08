#pragma once
#include"Obs.h"
#include"Matrix.h"

namespace OrbMod
{
	class ModAstroObs : public Obs
	{
	public:
		static Algebra::Matrix dOdX;

        ModAstroObs();
        ModAstroObs(const ModAstroObs& otr);
        ~ModAstroObs();

		bool tryParce(std::string s) override;

		void setParEq(Algebra::Matrix &A, std::vector<double> &OmC, Algebra::Matrix &x, Algebra::Matrix &dxdx0, double  tau) override;

		//void AbbCorr(int K, double dt0, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Yo) override;
        
        std::string getType() override;
		
        void writeRes() override;
		
        virtual ModAstroObs* clone() const override;

        double ra;
        double dec;

        float res_ra;
        float res_del;
	};
}
