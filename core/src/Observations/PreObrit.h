#pragma once
#include "stdafx.h"
namespace OrbMod
{
	class PreObrit
	{
	public:
		PreObrit();
		~PreObrit();
		static int  Pos2SV(double mu, triple r1, triple r2, double t1, double t2, double *elts);
		static int  calcPreSV(const AstroObs &o1, const AstroObs &o2, const AstroObs &o3, double &tdb_0, Matrix &SV);
		static int  Angles2Pos(const AstroObs &o1, const AstroObs &o2, const AstroObs &o3, triple *rout, double &lt);
		//tests
		static int test();
	private:
		static double U(triple &e, triple &W);
		static double Om(triple & W);
		static double Inc(triple &W);
		static double TrueA(double P, double r1, double r2, double sB, double cB);


	};
}

