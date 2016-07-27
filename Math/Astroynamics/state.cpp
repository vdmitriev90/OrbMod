#include "stdafx.h"
#include "state.h"
namespace OrbMod
{
	StVec::StVec()
	{
	}
	//
	StVec::StVec(Matrix &SV, double mu)
	{
		if (SV.nRows() < 6) throw ("");
		for (int i = 0; i < 6; i++) state[i] = SV(i, 0);
		this->mu = mu;
	}
	//
	StVec::StVec(Matrix &SV)
	{
		if (SV.nRows() < 6) throw ("");
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
