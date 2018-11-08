#pragma once
#include "OrbFit.h"
#include"constant.h"

namespace OrbMod
{
	//
	class batchFitting : public OrbFit
	{

	protected:
		OrbFit *fit;

	public:
		batchFitting();
		~batchFitting();

		void  SwitchVar(consts::Variables V);
		virtual void  Adjust(Algebra::Matrix &SV, double t0, double &sigma, Algebra::Matrix &Q) override;
		static batchFitting instance;
	};
}
