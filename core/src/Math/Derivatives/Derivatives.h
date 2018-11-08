#pragma once
#include"Matrix.h"
#include"triple.h"

namespace OrbMod
{
	class Derivatives
	{
	public:
		Derivatives();
		~Derivatives();

		//State to orbital elements partials, by (Montenbruc & Gill, 2001) 
		static Algebra::Matrix dSVdOscEl_Mont(double SV[6], double mu);
		//State to orbital elements partials, by (Urmaev, 1981) 
		static Algebra::Matrix dSVdOscEl_Urm(double SV[6], double mu);
		//Cartesian to spherical partials
		static Algebra::Matrix dNEUdDAzEl(Algebra::triple DAzEl);
		//Cartesian to Geodetic partials
		static Algebra::Matrix dXYZdBLH(Algebra::triple DAzEl);
	private:

	};
}

