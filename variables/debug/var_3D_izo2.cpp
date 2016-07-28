#include "stdafx.h"
#include "var_3D_izo2.h"
namespace OrbMod
{
	var_3D_izo2::var_3D_izo2()
	{
	}

	var_3D_izo2::~var_3D_izo2()
	{
	}
	void var_3D_izo2::setPar(vector<double> &X, Matrix &SV, double t0)
	{
		var_3D_izo::setPar(X, SV, t0);
		Fi.clear();
		SVi.clear();
	}
	//
	bool var_3D_izo2::Inter(double t0, double H, vector<double> &X, vector<double> &Yo)
	{
		if (Global::Discr != 0)
			while (abs(tout - t0) <= abs(H))
			{
				stepDs(tout - t0, H, X, Yo);
				Matrix fi(6, 6), svi(6, 1);
				svi.setFromVec(0, Yo);
				SVi.push_back(svi);

				fi.setFromVec(6, Yo);
				Fi.push_back(fi);

				tout += Global::Discr;
			}
		return false;
	}
}