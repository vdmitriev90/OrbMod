#include "hibridKalman_XV.h"
#include "batchFitting.h"
#include "Filter_XV.h"
#include "Control.h"
#include "Global.h"
#include "LinAlgAux.h"

using namespace Algebra;
using namespace std;

namespace OrbMod
{
	hibridKalman_XV hibridKalman_XV::instance1;

	hibridKalman_XV::hibridKalman_XV()
	{
		this->fit = new Filter_XV();
	}
	//
	hibridKalman_XV::~hibridKalman_XV()
	{
		delete fit;
	}
	//
	void hibridKalman_XV::InitFilter(Matrix &SV, double t0, double &sigma, Matrix &P)
	{
		Control::Obs_.reset();
		unsigned ite = Control::Obs_.it_end;
		Control::Obs_.it_end = Control::Obs_.it + Global::MinObsinBatch;
		batchFitting prefit;
		Matrix Q;
		prefit.Adjust(SV, t0, sigma, Q);

		Control::Obs_.it_end = ite;
		Matrix disp = LinAlgAux::CalcRMS(sigma, Q);
		P = LinAlgAux::initCov(disp);
	}
}