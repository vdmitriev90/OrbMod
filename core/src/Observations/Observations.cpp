#include "Observations.h"
#include "tform.h"
#include "state.h"
#include "Global.h"

using namespace Algebra;
using namespace std;

namespace OrbMod
{
	Observations::Observations()
	{
		isOutl = false;
	}

	Observations::Observations(const Observations& otr)
	{
		this->t = otr.t;
		this->dlt = otr.dlt;
		this->observ = Observatory(otr.observ);
		this->str_dbg = otr.str_dbg;
	}
	Observations::~Observations()
	{ }

    int Observations::compare(const obs_ptr& a, const obs_ptr & b) 
    {
        return (a->t < a->t); 
    }

	triple  Observations::getObsPos() const
	{
		triple R1 = StVec::getPos(399, t, "J2000", Global::IDC);
		triple dr1 = observ.X;
		tform::trpos("ITRF93", "J2000", t, dr1, dr1);
		R1 += dr1;
		return R1;
	}
}