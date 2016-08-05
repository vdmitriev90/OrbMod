#pragma once
using namespace Algebra;
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
		static Matrix dOdX;

		virtual bool tryParce(std::string s);
		virtual void setParEq(Matrix &A, vector<double> &OmC, Matrix &x, Matrix &dxdx0, double  tau) override;
		//void AbbCorr(int K, double dt0, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Yo) override;

		virtual string getType() override;
		virtual void writeRes() override;
		virtual ModDistObs* clone() const override;
	};
}

