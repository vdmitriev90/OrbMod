#define _CRT_SECURE_NO_WARNINGS
#include "ModAstroObs.h"
#include "Misc.h"
#include "Global.h"
#include "Control.h"
#include "ObsSet.h"
#include "constant.h"

#include "SpiceUsr.h"

using namespace Algebra;
using namespace consts;
using namespace std;

namespace OrbMod
{
	//
	ModAstroObs::ModAstroObs()
	{
	}
	ModAstroObs::ModAstroObs(const ModAstroObs& otr) :Observations(otr)
	{
		this->ra = otr.ra;
		this->dec = otr.dec;

		this->res_ra = otr.res_ra;
		this->res_del = otr.res_del;
	}
	//
	ModAstroObs::~ModAstroObs()
	{
	}
	//
	Matrix ModAstroObs::dOdX(2, 6);
	//
	string ModAstroObs::getType()
	{
		return "Model astro";
	}
	bool ModAstroObs::tryParce(std::string s)
	{
		vector<string> v = Misc::splitStr(s, ' ');
		if (v.size() < 3) return false;
		try
		{
			this->t = stod(v[0]);
			this->ra = stod(v[1]);
			this->dec = stod(v[2]);

			auto it = Observatory::str2Obsy.find("500");
			if (it == Observatory::str2Obsy.end())
				return false;
			this->observ = it->second;
		}
		catch (...)
		{
			return false;
		}

		return true;
	}
	//
	void ModAstroObs::updateEquations(Matrix &A, vector<double> &OmC, Matrix &sv, Matrix &dxdx0, double  tau)
	{
		double pos[6], lt, ra_c, dec_c, d, posE[3] = { 3000, 3000, 4800 }, rotate[3][3];
		triple r = triple(sv(0, 0), sv(1, 0), sv(2, 0));

		spkgps_c(399, this->t, "J2000", Global::IDC, pos, &lt);
		pxform_c("IAU_EARTH", "J2000", this->t, rotate);

		mtxv_c(rotate, posE, posE);

		triple re(pos);
		triple dr = r - re;
		dr.toSph(ra_c, dec_c, d);

		double cra2 = cos(ra_c), cdec2 = cos(dec_c);
		double sra = sin(ra_c), sdec = sin(dec_c);
		dOdX(0, 0) = -sra / (d);
		dOdX(0, 1) = cra2 / (d);
		dOdX(1, 0) = -cra2*sdec / d;
		dOdX(1, 1) = -sra*sdec / d;
		dOdX(1, 2) = cdec2 / d;

		res_ra = this->ra - ra_c;
		res_del = this->dec - dec_c;

		Matrix dOdX0 = dOdX*dxdx0;
		if (ObsSet::isLogResid) writeResiduals();

		A.addRows(dOdX0);
		OmC.push_back(res_ra*cos(dec_c));
		OmC.push_back(res_del);
	}
	//
	void ModAstroObs::writeResiduals()
	{
		char buff[200], c_time[35];
		timout_c(this->t, Global::pictur_tdb, 70, c_time);
		sprintf(buff, "%20.7f %f %f\n", this->t, res_ra*rad2asec, res_ra*rad2asec);
		Control::Obs_.f_res << c_time << " " << buff;
	}
	//
    obs_ptr ModAstroObs::clone() const
	{
		return make_shared<ModAstroObs>(*this);
	}
}