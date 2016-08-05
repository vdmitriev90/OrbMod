#pragma once
namespace OrbMod
{
	class AstroObs : public Obs
	{
	public:
		AstroObs();
		AstroObs(const AstroObs& otr);
		~AstroObs();

		static Matrix dOdX;

		//fields
		double ra;
		float dra;

		double dec;
		float ddec;

		double res_ra;
		double res_del;

		//methods
		virtual	bool tryParce(std::string s);
		virtual void setParEq(Matrix &A, vector<double> &OmC, Matrix &x, Matrix &dxdx0, double  tau) override;
		//void AbbCorr(int K, double dt0, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Yo) override;
		virtual string getType() override;
		virtual void writeRes() override;
		virtual bool isOutlier() override;
		virtual void abCorr(double pos[]);
		virtual AstroObs* clone() const override;

	};
}
