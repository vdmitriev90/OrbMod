#include"var.h"
#include"SB.h"
#include"ForceIzo.h"
#include"Global.h"
using namespace Algebra;
using namespace std;
namespace OrbMod
{
	var_SB_izo::var_SB_izo()
	{
		N = 132; Niter = 11;
	}
	void var_SB_izo::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		X.resize(N);
		SB sv = SB(SV, Force::getMu(), t0);
		sv.copyToVect(X);
		Matrix dYdY0(11, 11);
		dYdY0.Identy();
		dYdY0.copyToVec(11, X);

		dY0dy0 = sv.dYdy(Force::getMu());
		tout = t0;
	}
	void var_SB_izo::GetX(const vector<double> &X, Matrix &SV, double t0, Matrix &dXdX0)
	{
		SV = Matrix(6, 1);
		dXdX0 = Matrix(11, 11);
		SB sv = SB(X);
		triple Pos = sv.q;
		triple V = sv.v();
		for (size_t i = 0; i < 3; i++)
		{
			SV(i, 0) = Pos[i];
			SV(i + 3, 0) = V[i];
		}
		dXdX0.setFromVec(11, X);
	}
	void var_SB_izo::force(const double Ti, const vector<double> &X, vector<double> & F)
	{
		SB sv = SB(X);

		double r = sv.q.getAbs();
		double r2 = r*r;
		triple v3d = sv.p / r;

		//acceleration and acceleration partials
		ForceIzo f_(sv.t, sv.q, v3d);
		triple f = f_.force_pert();
		Matrix ddFdy = f_.get_ddFdsv();

		Matrix F3d(f);
		Matrix  Q(sv.q), P(sv.p), A(sv.a);

		//Vector 2 Matrix
		Matrix dYdY0(11, 11), dqdY0(3, 11), dpdY0(3, 11), dadY0(3, 11), dhdY0(1, 11);

		dYdY0.setFromVec(11, X);
		dqdY0.setFromVec(11, X);
		dpdY0.setFromVec(44, X);
		dadY0.setFromVec(77, X);
		dhdY0.setFromVec(110, X);

		Matrix E3(3, 3);
		E3.Identy();

		Matrix dydY = sv.dydY();
		Matrix dFdY0 = ddFdy*dydY*dYdY0;

		//Equations 0-10
#pragma region Equations 0-10

		triple dpds = (2.0*sv.h)*sv.q - sv.a + r2*f;
		double dhds = sv.p*f;
		double qtf = sv.q*f;
		double qtp = sv.q*sv.p;
		triple dads = (2.0*dhds)*sv.q - (qtf)*sv.p - qtp*f;

		for (int i = 0; i < 3; i++)
		{
			F[i] = sv.p[i];
			F[i + 3] = dpds[i];
			F[i + 6] = dads[i];
		}
		F[9] = dhds;
		F[10] = r;
#pragma endregion

		Matrix fqt = triple::xxt(f, sv.q);
		Matrix q_pt = triple::xxt(sv.q, sv.p);

		Matrix D = sv.h*E3 + fqt;
		D *= 2.0;
		Matrix D1 = (2.0*dhds)*E3 - triple::xxt(sv.p, f) - triple::xxt(f, sv.p);
		Matrix D2 = 2.0*triple::xxt(sv.q, f) - qtf*E3 - fqt;
		Matrix D3 = 2.0*q_pt - q_pt.Transpose() - qtp*E3;

		//Equations 11-43
		//Matrix ddqdY0 = dpdY0;

		//Equations 44-76
		Matrix ddpdY0 = D*dqdY0 + 2.0*Q*dhdY0 - dadY0 + r2*dFdY0;

		//Equations 77-109
		Matrix ddadY0 = D1*dqdY0 + D2*dpdY0 + D3*dFdY0;

		//Equations 110-120
		Matrix ddhdY0 = F3d.Transpose()*dpdY0 + P.Transpose()*dFdY0;

		//Equations 120-131
		Matrix ddtdY0 = (Q.Transpose()*dqdY0) / r;

		dpdY0.copyToVec(11, F);
		ddpdY0.copyToVec(44, F);
		ddadY0.copyToVec(77, F);
		ddhdY0.copyToVec(110, F);
		ddtdY0.copyToVec(120, F);

		Global::N_rp++;
	}
	void var_SB_izo::getdXdX0(const vector<double> &X, Matrix &Fi)
	{
		SB sv = SB(X);

		double r = sv.q.getAbs();
		Matrix dydY = sv.dydY();

		Matrix dYdY0(Niter, Niter);
		dYdY0.setFromVec(Niter, X);
		Matrix dtdY0(1, Niter);
		dtdY0.setFromVec(121, X);

		vector<double> F(N);

		force(0, X, F);
		Matrix G(Niter, 1);
		G.setFromVec(0, F);

		//according to equation 14  in (Shefer V.A., 2005)
		Fi = dydY*(dYdY0 - (1 / r)*G *dtdY0)*dY0dy0;

	};
}