#include "stdafx.h"
#include "Obs.h"
namespace OrbMod
{
	Obs::Obs()
	{
		isOutl = false;
	};
	Obs::~Obs()
	{

	};
	int Obs::compare(const Obs * a, const Obs * b) { return (a->t < a->t); };
	triple  Obs::getObsPos() const
	{
		triple R1 = StVec::getPos(399, t, "J2000", Global::IDC);
		triple dr1 = observ.X;
		tform::trpos("ITRF93", "J2000", t, dr1, dr1);
		R1 += dr1;
		return R1;
	}
}