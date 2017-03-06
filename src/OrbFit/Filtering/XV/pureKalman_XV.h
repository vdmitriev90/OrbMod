#pragma once
#include "OrbFit\Abstract\OrbFit.h"
using namespace Algebra;

namespace OrbMod
{
	class pureKalman_XV : public OrbFit
	{
	public:
		static pureKalman_XV instance;

		pureKalman_XV();
		~pureKalman_XV();

		//void  SwitchVar(Variables V);
		virtual void  Adjust(Matrix &SV, double t0, double &sigma, Matrix &Q) override;
		virtual void  InitFilter(Matrix &SV, double t0, double &sigma, Matrix &P);

	protected:
		OrbFit *fit;
	private:
		//uint getLastObs(double t, double dt);

	};
}
