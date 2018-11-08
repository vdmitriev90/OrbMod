#pragma once
#include "pureKalman_XV.h"

namespace OrbMod
{
	class hibridKalman_XV :
		public pureKalman_XV
	{
	public:
		hibridKalman_XV();
		~hibridKalman_XV();
		static hibridKalman_XV instance1;
		//void  SwitchVar(Variables V);

		virtual void  InitFilter(Algebra::Matrix &SV, double t0, double &sigma, Algebra::Matrix &P) override;
	protected:
		OrbFit *fit;
	};
}