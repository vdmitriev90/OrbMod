#pragma once
#include "Filter_XV.h"
namespace OrbMod
{
	class batchFilter_XV :
		public Filter_XV
	{
	public:
		batchFilter_XV();
		~batchFilter_XV();
		int FitBatch(Algebra::Matrix &SV, double &t0, double &te, double &sigma, Algebra::Matrix &Q) override;
	};

}