#define _CRT_SECURE_NO_WARNINGS
#include "AstroObs.h"
#include "Global.h"
#include "Misc.h"
#include "constant.h"
#include "tform.h"
#include "OrbFit.h"
#include "Control.h"

#include "SpiceUsr.h"

//#include<atltrace.h>
using namespace Algebra;
using namespace consts;
using namespace std;

namespace OrbMod
{
	AstroObs::AstroObs()
	{
		ra = 0;
		dra = 0;
		dec = 0;
		ddec = 0;
		res_ra = 0;
		res_del = 0;
	}

	AstroObs::AstroObs(const AstroObs& otr) :Obs(otr)
	{
		this->ra = otr.ra;
		this->dra = otr.dra;

		this->dec = otr.dec;
		this->ddec = otr.ddec;

		this->res_ra = otr.res_ra;
		this->res_del = otr.res_del;

	}
	AstroObs::~AstroObs()
	{
	}
	Matrix AstroObs::dOdX(2, 6);
	//example
	//     J96R13O* C1996 09 08.38795 23 47 38.69 -00 50 48.2                 27851691
	string AstroObs::getType()
	{
		return "Astrometric";
	}
	bool AstroObs::tryParce(std::string s)
	{
		if (s.length() < 80) return false;
		if (s[14] == 'S' || s[14] == 's' || s[14] == 'R' || s[14] == 'r') return false;
		double et, ra, dec;
		string obs_id;
		try
		{
			string ID = s.substr(0, 11);
			string utc = s.substr(15, 17);
			string s_RA = s.substr(32, 12);
			string s_dec = s.substr(44, 13);
			obs_id = s.substr(77, 3);

			string utc_data = utc.substr(0, 10);
			string utc_time = utc.substr(10, 7);
			double dday = stod(utc_time) * 86400;

			utc2et_c(utc_data.c_str(), &et);
			et += dday;
			char dtout[70];
			timout_c(et, Global::pictur_tdb, 70, dtout);

			if (!Misc::str2deg(s_RA, ' ', ra)) return false;
			if (!Misc::str2deg(s_dec, ' ', dec)) return false;
		}
		catch (...)
		{
			return false;
		}
		//
		this->t = et;
		this->ra = ra*deg2rad * 15;
		this->dec = dec*deg2rad;
		//
		auto it = Observatory::str2Obsy.find(obs_id);
		if (it == Observatory::str2Obsy.end())
			return false;
		this->observ = it->second;

		return true;
	}
	//
	void AstroObs::setParEq(Matrix &A, vector<double> &OmC, Matrix &sv, Matrix &dxdx0, double  tau)
	{
		double pos[6], lt, ra_c, dec_c, d;
		triple r = triple(sv(0, 0), sv(1, 0), sv(2, 0));

		spkgeo_c(399, this->t, "J2000", Global::IDC, pos, &lt);
		triple re(pos);

		str_dbg = dxdx0.toString("\t", "%e", 10);
		triple dr = r - re;

		//parallax correction
		triple par;
		tform::trpos(Global::EarthFrame, "J2000", this->t, observ.X, par);
		dr -= par;

		//aberration correction
		//abCorr(pos);

		//calculated RA and DEC
		dr.toSph(ra_c, dec_c, d);

		double cra2 = cos(ra_c), cdec2 = cos(dec_c);
		double sra = sin(ra_c), sdec = sin(dec_c);

		//Derivatives of the RA respect to state vector
		dOdX(0, 0) = -sra / (d);
		dOdX(0, 1) = cra2 / (d);

		//Derivatives of the DEC respect to state vector
		dOdX(1, 0) = -cra2*sdec / d;
		dOdX(1, 1) = -sra*sdec / d;
		dOdX(1, 2) = cdec2 / d;

		//O-C
		res_ra = (this->ra + this->dra) - ra_c;
		res_ra *= cos(dec_c);
		res_del = (this->dec + this->ddec) - dec_c;

		//отбраковка аутлаеров
		if (OrbFit::isMemOuts && isOutl)
			return;
		isOutl = isOutlier();
		if (isOutl)
		{
			Control::Obs_.Nouts++;
			return;
		}
		//d(RA,DEC)/d(x,y,z,vx,vy,vz)
		Matrix dOdX0 = dOdX*dxdx0;
		//logging residuals
		if (ObsSet::isLogResid) writeRes();

		A.addRows(dOdX0);
		OmC.push_back(res_ra);
		OmC.push_back(res_del);
	};
	//
	void AstroObs::abCorr(double pos[])
	{
		double  _ra, _dec, _r;
		triple vfix;
		double w = 7.2921151467e-5;

		vfix[0] = -w*observ.X[1];
		vfix[1] = w*observ.X[0];
		vfix[2] = 0;
		triple vin;
		tform::trpos(Global::EarthFrame, "J2000", this->t, vfix, vin);
		triple ve(pos[3], pos[4], pos[5]);

		triple Vfull = ve + vin;

		//s = s'-Vfull/(SoL) (5.82) в Жаров Сферическая астрономия
		triple s;
		s.fromSph(this->ra, this->dec, 1.0);
		s = s + Vfull / SoL;
		s.toSph(_ra, _dec, _r);

		this->dra = _ra - this->ra;
		this->ddec = _dec - this->dec;
	}
	//
	bool AstroObs::isOutlier()
	{
		if (OrbFit::isRejOuts && Control::Obs_.isConverg)
		{
			double d = sqrt(res_ra*res_ra + res_del*res_del);
			double d_cr = OrbFit::OutlsThresh*Control::Obs_.sigma;

			return (d > d_cr);
		}
		else
			return false;
	}
	//
	void AstroObs::writeRes()
	{
		char buff[250], c_time[70];
		timout_c(this->t, Global::pictur_tdb, 70, c_time);
		sprintf(buff, "%20.13e %s %f %f\n", this->t, this->observ.ID.c_str(),  res_ra*rad2asec, res_del*rad2asec);
		Control::Obs_.f_res << c_time << "\t" << buff;
	}
	//
	AstroObs* AstroObs::clone() const
	{
		return new AstroObs(*this);
	}
}