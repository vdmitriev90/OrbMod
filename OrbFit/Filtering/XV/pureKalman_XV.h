#pragma once
#include "OrbFit\Abstract\OrbFit.h"
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
		Obsiter getLastObs(double t, double dt);

	};
}