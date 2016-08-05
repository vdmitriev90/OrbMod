#pragma once
namespace OrbMod
{
	class ModAstroObs : public Obs
	{
	public:

		ModAstroObs();
		ModAstroObs(const ModAstroObs& otr);
		~ModAstroObs();

		double ra;
		double dec;

		float res_ra;
		float res_del;

		static Matrix dOdX;
		bool tryParce(std::string s) override;
		void setParEq(Matrix &A, vector<double> &OmC, Matrix &x, Matrix &dxdx0, double  tau) override;
		//void AbbCorr(int K, double dt0, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Yo) override;
		string getType() override;
		void writeRes() override;
		virtual ModAstroObs* clone() const override;
	};
}
