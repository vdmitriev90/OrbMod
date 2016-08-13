#include "stdafx.h"
#include "ModAstroObs2.h"

using namespace Algebra;
namespace OrbMod
{
	//
	ModAstroObs2::ModAstroObs2()
	{
	}
	//
	ModAstroObs2::ModAstroObs2(const ModAstroObs2& otr) :AstroObs(otr)
	{
		this->pos = otr.pos;
		this->posres = otr.posres;
	}
	//
	ModAstroObs2::~ModAstroObs2()
	{

	}
	//
	string ModAstroObs2::getType()
	{
		return "Model astro 2";
	}
	//JDTDB    Epoch Julian Date, Barycentric Dynamical Time
	//X      x - component of position vector(km)
	//Y      y - component of position vector(km)
	//Z      z - component of position vector(km)
	//VX     x - component of velocity vector(km / sec)
	//VY     y - component of velocity vector(km / sec)
	//VZ     z - component of velocity vector(km / sec)
	//LT     One - way down - leg Newtonian light - time(sec)
	//RG     Range; distance from coordinate center(km)
	//RR     Range - rate; radial velocity wrt coord.center(km / sec)

	//JDCT ,  tatetime (TDB) , X, Y, Z, VX, VY, VZ, LT, RG, RR,
	//2457329.500000000, A.D. 2015-Nov-03 00:00:00.0000,  5.793690310008615E+06,  3.908884367409393E+06,  1.484445847804569E+06, -8.341397797282077E-01, -1.296657719221081E+00, -9.892090532267428E-01,  2.383286956072746E+01,  7.144914546803865E+06, -1.591294037842224E+00,

	bool ModAstroObs2::tryParce(std::string s)
	{
		vector<string> v = Misc::splitStr(s, ',');
		if (v.size() < 8) return false;
		auto it = Observatory::str2Obsy.find("261");
		if (it == Observatory::str2Obsy.end())
			return false;
		this->observ = it->second;
		try
		{
			string tdb = v[1].substr(5, v[1].size() - 5);
			tdb += " TDB";
			const char *tdb_ch = tdb.c_str();
			str2et_c(tdb_ch, &this->t);
			double r = 0;
			pos[0] = stod(v[2]);
			pos[1] = stod(v[3]);
			pos[2] = stod(v[4]);
			pos.toSph(this->ra, this->dec, r);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	//
	void ModAstroObs2::setParEq(Matrix &A, vector<double> &OmC, Matrix &sv, Matrix &dxdx0, double  tau)
	{
		double pos[6], lt, ra_c, dec_c, d;
		triple r = triple(sv(0, 0), sv(1, 0), sv(2, 0));

		spkgeo_c(399, this->t, "J2000", Global::IDC, pos, &lt);

		triple re(pos);

		triple dr = r - re;
		//parallax correction
		triple par;
		tform::trpos("ITRF93", "J2000", this->t, observ.X, par);
		dr -= par;
		//aberration correction
		//abCorr(pos);

		posres = dr - this->pos;
		dr.toSph(ra_c, dec_c, d);

		double cra2 = cos(ra_c), cdec2 = cos(dec_c);
		double sra = sin(ra_c), sdec = sin(dec_c);

		dOdX(0, 0) = -sra / (d);
		dOdX(0, 1) = cra2 / (d);
		dOdX(1, 0) = -cra2*sdec / d;
		dOdX(1, 1) = -sra*sdec / d;
		dOdX(1, 2) = cdec2 / d;

		res_ra = (this->ra + this->dra) - ra_c;
		res_del = (this->dec + this->ddec) - dec_c;

		Matrix dOdX0 = dOdX*dxdx0;
		if (ObsSet::isLogResid) writeRes();

		A.addRows(dOdX0);
		OmC.push_back(res_ra*cos(dec_c));
		OmC.push_back(res_del);

	}
	void ModAstroObs2::writeRes()
	{
		char buff[200], c_time[35];
		timout_c(this->t, Global::pictur_tdb, 70, c_time);
		sprintf(buff, "%20.7f %f %f  %f %f %f\n", this->t, res_ra*rad2asec, res_del*rad2asec, posres[0], posres[1], posres[2]);
		Control::Inst.Obs_->f_res << c_time << " " << buff;
	}
	ModAstroObs2* ModAstroObs2::clone() const
	{
		return new ModAstroObs2(*this);
	}
}