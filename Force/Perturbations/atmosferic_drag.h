#pragma once
#include "SpiceUsr.h"
#include "Math\Algebra\Linear_Algebra\triple.h"

using namespace Algebra;

namespace OrbMod
{
	class atm {
	private:
		triple r, v;
		static double Catm, H, ro_0, Massa, Peri, Area;
		static vector<double> AtmModel_H;
		static vector<double> AtmModel_Dens;

	public:

		atm(void);
		~atm(void);

		//сеты
		void setPos(triple R) { r = R; };
		void setVel(triple V) { v = V; };

		static void setCatm(double C) { Catm = C; };
		static void setH(double A) { H = A; };
		static void setRo_0(double R0) { ro_0 = R0; };
		static void setPeri(double P) { Peri = P; };
		static void setArea(double S) { Area = S; };
		static void setMassa(double M) { Massa = M; };
		static void setEarthAtmModel(char* str);
		//геты
		triple getAcc(double time);




	};
}