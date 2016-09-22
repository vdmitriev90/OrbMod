#pragma once
#include"stdafx.h"
#include "OrbFit\Abstract\OrbFit.h"

namespace OrbMod
{
	class seqLS_KS :
		public OrbFit
	{
	public:
		seqLS_KS();
		~seqLS_KS();
		static seqLS_KS inst;

		virtual void  Adjust(Matrix &SV, double t0, double &sigma, Matrix &Q) override;
	protected:
		OrbFit *fit;
	};
}