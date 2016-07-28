#pragma once
#include "OrbFit\Abstract\OrbFit.h"
using namespace Algebra;

namespace OrbMod
{
	class hibridKalman_XV :
		public pureKalman_XV
	{
	public:
		hibridKalman_XV();
		~hibridKalman_XV();
		static hibridKalman_XV instance1;
		void  SwitchVar(Variables V);

		virtual void  InitFilter(Matrix &SV, double t0, double &sigma, Matrix &P)override;
	protected:
		OrbFit *fit;
	};
}