#pragma once
#include "OrbFit.h"


namespace OrbMod
{
	class pureKalman_XV : public OrbFit
	{
	public:
		static pureKalman_XV instance;

		pureKalman_XV();
		~pureKalman_XV();

		//void  SwitchVar(Variables V);
		virtual void  Adjust(Algebra::Matrix &SV, double t0, double &sigma, Algebra::Matrix &Q) override;
		virtual void  InitFilter(Algebra::Matrix &SV, double t0, double &sigma, Algebra::Matrix &P);

	protected:
		OrbFit *fit;
	private:
		//uint getLastObs(double t, double dt);

	};
}

