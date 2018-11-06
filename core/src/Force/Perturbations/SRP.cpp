#include"stdafx.h"
#include"SRP.h"
namespace OrbMod
{
	SRP::SRP(void)
	{
	}

	SRP::~SRP(void)
	{
	}
	double SRP::Albedo;
	double SRP::Area;
	double SRP::Mass;
	double SRP::rPl;
	double SRP::SRPconst;

	void SRP::setSRPconst() {
		SRPconst = (1.0 + Albedo)*Ksrp*Area / (Mass * 1000);
	}

	void SRP::setRadii(int IDC) {
		char id[20];
		SpiceInt dim;
		double values[3];

		_itoa(IDC, id, 10);
		bodvrd_c(id, "RADII", 3, &dim, values);
		rPl = (values[0] + values[1] + values[2]) / 3.0;
		//rPl=(values[2]+AB)/2.0;
	}

	triple SRP::getAcceleration(double et) {
		double state[3];
		double lt;

		spkgps_c(10, et, "J2000", Global::IDC, state, &lt);
		triple posSun(state);
		//printf("%d\n",Global::IDC);
		double Sun_mag = posSun.getAbs();
		double R_mag = r.getAbs();
		double cosphi = (r*posSun) / (R_mag*Sun_mag);

		triple delta = posSun - r;
		double d = delta.getAbs();
		double beta = R_mag - Sun_mag*cosphi;
		beta /= delta.getAbs();
		beta = acos(beta);

		double epsE = asin(rPl / R_mag);
		double epsS = asin(Rsun / Sun_mag);

		double s;
		if (beta >= epsE + epsS) s = 1.0;
		else if (beta <= epsE - epsS) s = 0.0;
		else {
			s = (beta - epsE + epsS) / 2. / epsS;
		}

		double k = AU / d;
		double coeff = -s * SRPconst*k*k / d;
		triple res = delta*coeff;
		//printf("SRP %e\n",res.getAbs());
		return res;
	}
}