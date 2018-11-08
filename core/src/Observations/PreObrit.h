#pragma once
#include "triple.h"
#include "Matrix.h"
#include "AstroObs.h"
namespace OrbMod
{
	class PreObrit
	{
	public:
		PreObrit();
		~PreObrit();
		static int  Pos2SV(double mu, Algebra::triple r1, Algebra::triple r2, double t1, double t2, double *elts);
		static int  calcPreSV(const AstroObs &o1, const AstroObs &o2, const AstroObs &o3, double &tdb_0, Algebra::Matrix &SV);
		static int  Angles2Pos(const AstroObs &o1, const AstroObs &o2, const AstroObs &o3, Algebra::triple *rout, double &lt);
		//tests
		static int test();
	private:
		static double U(Algebra::triple &e, Algebra::triple &W);
		static double Om(Algebra::triple & W);
		static double Inc(Algebra::triple &W);
		static double TrueA(double P, double r1, double r2, double sB, double cB);


	};
}

