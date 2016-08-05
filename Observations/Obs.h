#pragma once
#include"stdafx.h"

using namespace Algebra;
namespace OrbMod
{
	class Obs
	{
	public:
		Obs();
		Obs(const Obs& other);
		virtual ~Obs();
		double t, dlt;
		Observatory observ;
		string  str_dbg;
		static  int compare(const Obs * a, const Obs * b);
		triple getObsPos() const;
		virtual bool tryParce(std::string s) = 0;
		virtual void setParEq(Matrix &A, vector<double> &OmC, Matrix &x, Matrix &dxdx0, double  tau) = 0;
		virtual string getType() = 0;
		virtual Obs * clone() const = 0;

	protected:
		bool isOutl;
		virtual void writeRes() = 0;
		virtual bool isOutlier() { return false; };
		//virtual void AbbCorr(int K, double dt0, double H, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Yo) = 0;
	};
}
//
