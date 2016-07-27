#pragma once

#include "OrbFit\Abstract\OrbFit.h"
namespace OrbMod
{
	class seqLS :
		public OrbFit
	{
	public:
		seqLS();
		seqLS(Variables var);
		~seqLS();
		void switchVar(Variables var);
		static seqLS inst;

		virtual void  Adjust(Matrix &SV, double t0, double &sigma, Matrix &Q) override;
	protected:
		OrbFit *fit;
	};
}