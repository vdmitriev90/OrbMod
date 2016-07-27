#pragma once
namespace OrbMod
{
	class AstroObs : public Obs
	{
	public:
		AstroObs();
		~AstroObs();

		virtual	bool tryParce(std::string s);
		virtual void setParEq(Matrix &A, vector<double> &OmC, Matrix &x, Matrix &dxdx0, double  tau) override;
		//void AbbCorr(int K, double dt0, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Yo) override;
		virtual string getType() override;
		virtual void writeRes() override;
		virtual bool isOutlier() override;

		double ra;
		float dra;

		double dec;
		float ddec;

		float res_ra;
		float res_del;
		static Matrix dOdX;
		virtual void abCorr(double pos[]);

	private:

	};
}
