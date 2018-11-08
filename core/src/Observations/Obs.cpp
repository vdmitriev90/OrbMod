#include "Obs.h"
#include "tform.h"
#include "state.h"
#include "Global.h"

using namespace Algebra;
using namespace std;

namespace OrbMod
{
	Obs::Obs()
	{
		isOutl = false;
	};
	Obs::Obs(const Obs& otr)
	{
		this->t = otr.t;
		this->dlt = otr.dlt;
		this->observ = Observatory(otr.observ);
		this->str_dbg = otr.str_dbg;
	}
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