#pragma once
#include "Matrix.h"
#include "triple.h"

namespace OrbMod
{
	class StVec
	{
	private:
		double state[6];
		double mu;

	public:

		StVec();
		StVec(Algebra::Matrix &SV);
		StVec(Algebra::Matrix &SV, double mu);
		void setFromOscEl(Algebra::Matrix elts, double mu);
		Algebra::Matrix getOscEl(bool IsConvert2deg);
		//
		Algebra::Matrix getOscEl(bool IsConvert2deg, bool isAU);
		//
		double getMMotion();
		double getMMotion(double mu_);
		//
		double getPeriod();
		double getPeriod(double mu_);
		Algebra::triple X();
		Algebra::triple V();
		Algebra::Matrix toMatrix();
		static Algebra::triple getPos(int target, double et, char*FRAME, int observer);
		static Algebra::Matrix getState(int target, double et, char*FRAME, int observer);

		~StVec();
	};

}