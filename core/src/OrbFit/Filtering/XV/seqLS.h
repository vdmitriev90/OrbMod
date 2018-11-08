#pragma once
#include "OrbFit.h"
#include "constant.h"

namespace OrbMod
{
	class seqLS :
		public OrbFit
	{
	public:
		seqLS();
		seqLS(consts::Variables var);
		~seqLS();
		void switchVar(consts::Variables var);
		static seqLS inst;

		virtual void  Adjust(Algebra::Matrix &SV, double t0, double &sigma, Algebra::Matrix &Q) override;
	protected:
		OrbFit *fit;
	};
}