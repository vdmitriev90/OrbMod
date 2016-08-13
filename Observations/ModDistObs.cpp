#include "stdafx.h"
#include "ModDistObs.h"
using namespace Algebra;
#define DEF__1 1
namespace OrbMod
{
	ModDistObs::ModDistObs() 
	{
	}
	ModDistObs::ModDistObs(const ModDistObs& otr):Obs(otr)
	{
		this->dist = otr.dist;
		this->res = otr.res;
	}
	ModDistObs::~ModDistObs()
	{
	}
	Matrix ModDistObs::dOdX(1, 6);
	string ModDistObs::getType()
	{
		return "Model distance";
	}
	bool ModDistObs::tryParce(std::string s)
	{
		char str[]{ ' ', '\t' };

		vector<string> v = Misc::splitStr(s, str, 2);

		if (v.size() < 2) return false;

		try
		{
			this->t = stod(v[0]);
			this->dist = stod(v[1]);

			auto it = Observatory::str2Obsy["500"];
			//if (it == Observatory::str2Obsy.end())
			//	return false;
			this->observ = it;
			//string s1 = this->observ->ID;
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	void ModDistObs::setParEq(Matrix &A, vector<double> &OmC, Matrix &sv, Matrix &dxdx0, double  tau)
	{
		double pos[3], lt, ra, dec, d, posE[3] = { 3000,3000,4800 }, rotate[3][3];
		triple r = triple(sv(0, 0), sv(1, 0), sv(2, 0));

		spkgps_c(399, this->t, "J2000", Global::IDC, pos, &lt);
		//pxform_c("IAU_EARTH","J2000",this->t,rotate);

		//mtxv_c(rotate, posE, posE);

		triple re(pos);
		triple dr = r - re;
		dr.toSph(ra, dec, d);

		for (int i = 0; i < 3; i++) dOdX(0, i) = dr[i] / d;
		res = this->dist - d;

		//str_dbg = dxdx0.toString("\t", "%e", 10);
		char buff[200];
		//triple r1 = r;
		//tform::trpos("J2000", "ECLIPJ2000", 0, r, r1);
		//sprintf(buff, "%20.7f %12.10f %12.10f %12.10f %f", this->t, r1[0]/AU, r1[1] / AU, r1[2] / AU, res);
		sprintf(buff, "%20.7f %f", this->t, res);
		str_dbg = buff;
		//str_dbg += (r/AU).toString("\t", "%20.7f");
		//str_dbg += "\n";
		Matrix dOdX0 = dOdX*dxdx0;

		if (ObsSet::isLogResid) writeRes();

		A.addRows(dOdX0);
		OmC.push_back(res);
	}
	void ModDistObs::writeRes()
	{
		char buff[200], c_time[35];
		//timout_c(this->t, Global::pictur_tdb, 70, c_time);

		//sprintf(buff, "%20.7f %f", this->t, res);
		//ObsSet::Instance().f_res << c_time << " " << buff<< "\t" << str_dbg <<endl;
		Control::Inst.Obs_->f_res << str_dbg << endl;
	}
	ModDistObs* ModDistObs::clone() const
	{
		return new ModDistObs(*this);
	}
}