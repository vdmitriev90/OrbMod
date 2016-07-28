#pragma once
#include "stdafx.h"
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

		void  SwitchVar(Variables V);
		virtual void  Adjust(Matrix &SV, double t0, double &sigma, Matrix &Q) override;
		static batchFitting instance;
	};
}
