#include "stdafx.h"
#include "PreObrit.h"

using namespace Algebra;

namespace OrbMod
{
	//
	PreObrit::PreObrit()
	{
	}
	//
	PreObrit::~PreObrit()
	{
	}
	//	elts       are conic osculating elements describing the orbit of a
	//	body around a primary.The elements are, in order :
	//
	//	RP      Perifocal distance.
	//	ECC     Eccentricity.
	//	INC     Inclination.
	//	LNODE   Longitude of the ascending node.
	//	ARGP    Argument of periapse.
	//	M0      Mean anomaly at epoch.
	//	T0      Epoch.
	//	MU      Gravitational parameter.
	//
	//	Units are km, rad, rad / sec, km**3 / sec**2.

	int  PreObrit::Pos2SV(double mu, triple r1, triple r2, double t1, double t2, double *elts)
	{
		double d1 = r1.getAbs();
		double d2 = r2.getAbs();
		double dt = t2 - t1;
		double dt2 = dt*dt;
		double d1d2 = d1*d2;

		triple e1 = r1 / d1;
		triple e2 = r2 / d2;

		triple r0 = r2 - (r2*e1)*e1;
		triple e0 = r0.norm();
		triple W = e1&e0;
		double cosB = e1*e2;
		double sinB = sqrt(1.0 - cosB*cosB);

		double OM = Om(W);
		double inc = Inc(W);
		double U1 = U(e1, W);
		double U2 = U(e2, W);
		double du = acos(cosB);

		double c2 = 2.0*d1d2*(1.0 - cosB);
		double c = sqrt(c2);
		double d = 22.0*mu*dt2 / (c2*(6.0*c + 9.0*(d1 + d2)));

		double S = d;
		double dS;
		while (true)
		{
			double S_ = d / (1.0 + S);
			dS = abs(S_ - S);
			if (dS < 1e-12)
			{
				S = S_;
				break;
			}
			S = S_;
		}

		double nu = 1.0 + (10.0 / 11.0)*S;
		double P = nu*nu*SQR(d1d2*sinB) / (mu*dt2);
		double V1 = TrueA(P, d1, d2, sinB, cosB);
		double V2 = V1 + du;
		double ecc = (d2 - d1) / (d1*cos(V1) - d2*cos(V2));
		double w = U1 - V1;

		double use2 = (1.0 - ecc*ecc);

		double sma = P / use2;
		double M1 = Kepler::True2Mean(V1, ecc);
		double n = sqrt(mu) / (sma*sqrt(sma));
		double tau = t1 - M1 / n;
		double t0 = (t1 + t2) / 2.0;

		double M0 = n*(t0 - tau);
		elts[0] = sma*(1 - ecc);
		elts[1] = ecc;
		elts[2] = inc;
		elts[3] = OM;
		elts[4] = w;
		elts[5] = M0;
		elts[6] = t0;
		elts[7] = mu;

		return 0;
	}//
	double PreObrit::U(triple &e, triple &W)
	{
		double Y = -(e[0] * W[0] + e[1] * W[1]) / W[2];
		double X = (e[1] * W[0] - e[0] * W[1]);
		return atan(Y / X);
	}
	//
	double PreObrit::Inc(triple &W)
	{
		return atan(sqrt(W[0] * W[0] + W[1] * W[1]) / W[2]);
	}
	//
	double PreObrit::Om(triple &W)
	{
		double y = W[0];
		double x = -W[1];
		return	atan2(y, x);
	}
	//
	double PreObrit::TrueA(double P, double d1, double d2, double sB, double cB)
	{
		double D1 = (P - d1) / d1;
		double D2 = (P - d2) / d2;

		double Y = D1*cB - D2;
		double X = D1*sB;

		return atan2(Y, X);
	}
	//
	int  PreObrit::calcPreSV(const AstroObs &o1, const AstroObs &o2, const AstroObs &o3, double &tdb_0, Matrix &SV)
	{
		triple pos[3];
		double lt;
		Angles2Pos(o1, o2, o3, pos, lt);


		double t0 = o1.t, t1 = o2.t, t2 = o3.t;

		return 0;
	}

	//
	int  PreObrit::Angles2Pos(const AstroObs &o1, const AstroObs &o2, const AstroObs &o3, triple *rout, double &lt)
	{
		double t0 = o1.t, t1 = o2.t, t2 = o3.t;
		triple R[3], r[3];
		R[0] = o1.getObsPos();
		R[1] = o2.getObsPos();
		R[2] = o3.getObsPos();

		triple e[3];
		e[0].fromSph(o1.ra, o1.dec, 1.0);
		e[1].fromSph(o2.ra, o2.dec, 1.0);
		e[2].fromSph(o3.ra, o3.dec, 1.0);

		triple d[3];
		d[0] = e[1] & e[2];
		d[1] = e[2] & e[0];
		d[2] = e[0] & e[1];

		double D[3][3];
		for (size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 3; j++)
				D[i][j] = d[i] * R[j];

		double n1 = (t2 - t1) / (t2 - t0);
		double n3 = (t1 - t0) / (t2 - t0);

		double ro[3];
		double upD = 1.0 / (e[0] * d[0]);

		double n1_, n3_;
		triple r_[3];
		int count = 0;
		while (true)
		{
			ro[0] = -(upD / n1)*(n1*D[0][0] - D[0][1] + n3*D[0][2]);
			ro[1] = upD*(n1*D[1][0] - D[1][1] + n3*D[1][2]);
			ro[2] = -(upD / n3)*(n1*D[2][0] - D[2][1] + n3*D[2][2]);

			for (size_t i = 0; i < 3; i++)
				r[i] = R[i] + ro[i] * e[i];

			double	S1 = (r[1] & r[2]).getAbs();
			double	S2 = (r[0] & r[2]).getAbs();
			double	S3 = (r[0] & r[1]).getAbs();

			n1_ = S1 / S2;
			n3_ = S3 / S2;
			double dn1 = n1_ - n1;
			double dn3 = n3_ - n3;
			count++;
			for (size_t i = 0; i < 3; i++)
				OrbFit::fo << "iter\t" << count << "\t" << (r[i]).toString("\t", "%e") << "\t" << ro[i] << "\t" << dn1 << "\t" << dn3 << endl;

			if (abs(dn1) < 1e-14&& abs(dn3) < 1e-14) break;
			for (size_t i = 0; i < 3; i++)
				r_[i] = r[i];
			n1 = n1_;
			n3 = n3_;
			if (count > 15) break;
		}
		lt = (ro[0] + ro[2]) / (2.0* SoL);

		for (size_t i = 0; i < 3; i++)
			rout[i] = r[i];

		return 0;
	}
	//
	int PreObrit::test()
	{
		double mu = BODY10_GM;
		double t0 = 0, dt = 1 * 86400;
		double buf;
		AstroObs os[3];
		triple pE[3], epo[3];

		double oscel[8], st[6];
		oscel[0] = 2 * AU;
		oscel[1] = 0.;
		oscel[2] = 0;
		oscel[3] = 2;
		oscel[4] = 3;
		oscel[5] = 4;
		oscel[6] = 0.0;
		oscel[7] = mu;
		conics_c(oscel, 0, st);
		Matrix sv(st, 6, 1);

		StVec r[3];
		for (size_t i = 0; i < 3; i++)
		{
			double ti = t0 + dt*i;

			Matrix svi;
			Kepler::PropSV(mu, sv, t0, ti, svi);

			r[i] = StVec(svi, mu);
			Matrix elts = r[i].getOscEl(false);
			OrbFit::fo << "PreObrit::test::elts\t" << elts.toString() << endl;
			pE[i] = StVec::getPos(399, ti, "J2000", 10);

			epo[i] = r[i].X() - pE[i];

			OrbFit::fo << "PreObrit::test::svi\t" << r[i].X().toString() << "\t" << epo[i].getAbs() << endl;
			os[i].t = ti;
			epo[i].toSph(os[i].ra, os[i].dec, buf);
			os[i].observ = Observatory::str2Obsy["500"];
		}

		Matrix oscel1 = r[0].getOscEl(0);
		triple r_[3];

		Angles2Pos(os[0], os[1], os[2], r_, buf);
		for (size_t i = 0; i < 3; i++)
			OrbFit::fo << (r[i].X() - r_[i]).getAbs() << endl;

		double elts[8];
		Pos2SV(mu, r[0].X(), r[2].X(), os[0].t, os[2].t, elts);
		for (size_t i = 0; i < 7; i++)
			OrbFit::fo << elts[i] << "\t";
		OrbFit::fo << endl;

		return 0;
	}
}
//OrbFit::fo << "PreObrit::test::elts\t" << elts.toString() << endl;