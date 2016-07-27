#pragma once
#include "stdafx.h"
using namespace Algebra;

namespace OrbMod
{
	class StVec
	{
	private:
		double state[6];
		double mu;

	public:

		StVec();
		StVec(Matrix &SV);
		StVec(Matrix &SV, double mu);
		void setFromOscEl(Matrix elts, double mu);
		Matrix getOscEl(bool IsConvert2deg);
		triple X();
		triple V();
		Matrix toMatrix();
		static triple getPos(int target, double et, char*FRAME, int observer);
		static Matrix getState(int target, double et, char*FRAME, int observer);

		~StVec();
	};

}