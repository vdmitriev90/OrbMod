#pragma once

namespace OrbMod
{
	class Derivatives
	{
	public:
		Derivatives();
		~Derivatives();

		//State to orbital elements partials, by (Montenbruc & Gill, 2001) 
		static Matrix dSVdOscEl_Mont(double SV[6], double mu);
		//State to orbital elements partials, by (Urmaev, 1981) 
		static Matrix dSVdOscEl_Urm(double SV[6], double mu);
		//Cartesian to spherical partials
		static Matrix dNEUdDAzEl(triple DAzEl);
		//Cartesian to Geodetic partials
		static Matrix dXYZdBLH(triple DAzEl);
	private:

	};
}

