#include "stdafx.h"
#include "hibridKalman_XV.h"
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
		uint ite = Control::Obs_.it_end;
		Control::Obs_.it_end = Control::Obs_.it + Global::MinObsinBatch;
		batchFitting prefit;
		Matrix Q;
		prefit.Adjust(SV, t0, sigma, Q);

		Control::Obs_.it_end = ite;
		Matrix disp = LinAlgAux::CalcRMS(sigma, Q);
		P = LinAlgAux::initCov(disp);
	}
}