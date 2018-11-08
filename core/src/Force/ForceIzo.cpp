#include "ForceIzo.h"
#include "Global.h"
#include "macroses.h"
#include "constant.h"

#include "SpiceUsr.h"

using namespace Algebra;
using namespace consts;
//
namespace OrbMod
{
	ForceIzo::ForceIzo() {};
	//
    ForceIzo::ForceIzo(const double &t, const  Algebra::triple &X, const Algebra::triple &V)
        :Force(t, X, V)
    {
        init_izo();
    }
	//
	ForceIzo::~ForceIzo()
	{
	};
	//
	//Initialization of transition matrix in cartesian coordinates
	void ForceIzo::init_izo()
	{
		dfdv = Matrix(3, 3);
		ddFdy = Matrix(3, 6);
		dFcbdx = Matrix(3, 3);
		dFnmdx = Matrix(3, 3);
		dF3bdx = Matrix(3, 3);
	}
	//
	void ForceIzo::merge_izo()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				ddFdy(i, j) = dF3bdx(i, j) + dFnmdx(i, j);
				ddFdy(i, j + 3) = dfdv(i, j);
			}
	}
	//
	triple ForceIzo::planet(int IDP, double mu)
	{
		double poss[3];
		double lt1;
		triple rp, Delta;

		spkgps_c(IDP, time, "J2000", Global::IDC, poss, &lt1);

		triple Xp(poss);
		Delta = Xp - X;
		double d = Delta.getAbs();
		double D3 = CUB(d);
		double r = Xp.getAbs();
		triple accp = Delta*mu / D3 - Xp*mu / CUB(r);

		//3-bodies partials 
		double E[3][3], M2[3][3];
		E[0][0] = E[1][1] = E[2][2] = 1.0 / D3;

		double D5 = D3*d*d;
		double k1 = 3.0 / D5;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				if (i == j) E[i][j] = 1.0 / D3;
				else E[i][j] = .0;
				M2[i][j] = k1 * Delta[i] * Delta[j];
			}
		//
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				dF3bdx(i, j) = dF3bdx(i, j) + mu*(M2[i][j] - E[i][j]);
		return accp;
	}
	triple ForceIzo::planet(int IDP) {
		double mu = ID2GM(IDP);
		return planet(IDP, mu);
	}
	//
	triple ForceIzo::force_cb()
	{
		double r = X.getAbs();
		double r2 = r*r;
		double r3 = r2*r;
		double r5 = r2*r3;
		double M = Force::mu / r5;

		//acceleration 
		triple a = (X)*(-mu) / (r3);

		//partial derivatives 
		dFcbdx(0, 0) = 3 * X[0] * X[0] - r2;	dFcbdx(0, 1) = 3 * X[0] * X[1];			dFcbdx(0, 2) = 3 * X[0] * X[2];
		dFcbdx(1, 0) = 3 * X[0] * X[1];			dFcbdx(1, 1) = 3 * X[1] * X[1] - r2;	dFcbdx(1, 2) = 3 * X[1] * X[2];
		dFcbdx(2, 0) = 3 * X[0] * X[2];			dFcbdx(2, 1) = 3 * X[2] * X[1];		    dFcbdx(2, 2) = 3 * X[2] * X[2] - r2;

		dFcbdx = M*dFcbdx;

		return a;
	}
	//
	Matrix ForceIzo::get_ddFdsv()
	{
		merge_izo();
		return ddFdy;
	}
	//
	Matrix ForceIzo::get_dFcbdx()
	{
		return dFcbdx;
	}
}