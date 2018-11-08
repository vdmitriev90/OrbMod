#include "state.h"
#include"constant.h"
#include"Global.h"
#include"macroses.h"

#include"SpiceUsr.h"

#include<exception>
using namespace Algebra;
using namespace std;
using namespace consts;

namespace OrbMod
{
	StVec::StVec()
	{
	}
	//
	StVec::StVec(Matrix &SV, double mu)
	{
		if (SV.nRows() < 6) 
			throw invalid_argument("StVec: state vector  must be specified by 6 parameters ");
		for (int i = 0; i < 6; i++) state[i] = SV(i, 0);
		if (mu <= 0) throw invalid_argument("StVec: mu must be positive");
		this->mu = mu;
	}
	//
	StVec::StVec(Matrix &SV)
	{
		if (SV.nRows() < 6) 
			throw invalid_argument("StVec: state vector  must be specified by 6 parameters ");
		for (int i = 0; i < 6; i++) state[i] = SV(i, 0);
		this->mu = ID2GM(Global::IDC);
	}
	//
	void StVec::setFromOscEl(Matrix elts, double mu)
	{
	}
	//
	Matrix StVec::getOscEl(bool IsConvert2deg)
	{
		Matrix el(6, 1);
		double r2d = IsConvert2deg ? rad : 1.0;
		double elts[8];
		oscelt_c(state, 0, mu, elts);
		el(0, 0) = elts[0] / (1 - elts[1]);
		el(1, 0) = elts[1];
		for (int i = 2; i < 6; i++)
		{
			el(i, 0) = elts[i] * r2d;
		}
		return el;
	}
	//
	Matrix StVec::getOscEl(bool IsConvert2deg, bool isAU)
	{
		Matrix el(6, 1);
		double r2d = IsConvert2deg ? rad : 1.0;
		double toAU = isAU ? AU : 1.0;

		double elts[8];
		oscelt_c(state, 0, mu, elts);
		el(0, 0) = elts[0] / (1 - elts[1])/ toAU;
		el(1, 0) = elts[1];

		for (int i = 2; i < 6; i++)
		{
			el(i, 0) = elts[i] * r2d;
		}
		return el;
	}
	double StVec::getMMotion()
	{
		if (mu <= 0) throw invalid_argument("StVec: mu must be positive");
		double elts[8];
		oscelt_c(state, 0, mu, elts);
		double sma = elts[0] / (1.0 - elts[1]);
		return sqrt(mu / CUB(sma));
	}
	double StVec::getMMotion(double mu_)
	{
		if (mu_ <= 0) throw invalid_argument("StVec: mu must be positive");
		double elts[8];
		oscelt_c(state, 0, mu_, elts);
		double sma = elts[0] / (1.0 - elts[1]);
		return sqrt(mu_ / CUB(sma));
	}
	//
	double StVec::getPeriod()
	{
		return twopi / getMMotion();
	}
	//
	double StVec::getPeriod(double mu_)
	{
		return twopi / getMMotion(mu_);
	}
	//
	triple StVec::X()
	{
		return triple(state[0], state[1], state[2]);
	}
	//
	triple StVec::V()
	{
		return triple(state[3], state[4], state[5]);
	}
	//
	Matrix StVec::toMatrix()
	{
		return Matrix(state, 6, 1);
	}
	//
	triple  StVec::getPos(int tar, double et, char*ref, int obs)
	{
		double lt, pos[3];
		spkgps_c(tar, et, ref, obs, pos, &lt);
		return triple(pos[0], pos[1], pos[2]);
	}
	//
	Matrix StVec::getState(int tar, double et, char*ref, int obs)
	{
		double lt, sv[6];
		spkgeo_c(tar, et, ref, obs, sv, &lt);
		return Matrix(sv, 6, 1);
	}
	//
	StVec::~StVec()
	{
	}
}
