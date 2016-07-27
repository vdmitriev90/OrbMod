#pragma once

namespace OrbMod
{
	class Derivatives
	{
	public:
		Derivatives();
		~Derivatives();
		static Matrix dSVdOscEl_Mont(double SV[6], double mu);
		static Matrix dSVdOscEl_Urm(double SV[6], double mu);
		//производные от вектора прямоугольных координат по сферическим
		static Matrix dNEUdDAzEl(triple DAzEl);
		static Matrix dXYZdBLH(triple DAzEl);
	private:

	};
}

