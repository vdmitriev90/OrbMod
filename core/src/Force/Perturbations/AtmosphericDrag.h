#pragma once
#include "triple.h"

namespace OrbMod
{
	class AtmosphericDrag {
	private:
		Algebra::triple r, v;
		static double Catm, H, ro_0, Massa, Peri, Area;
		static std::vector<double> AtmModel_H;
		static std::vector<double> AtmModel_Dens;

	public:

		AtmosphericDrag(void);
		~AtmosphericDrag(void);

		//сеты
		void setPos(Algebra::triple R) { r = R; };
		void setVel(Algebra::triple V) { v = V; };

		static void setCatm(double C) { Catm = C; };
		static void setH(double A) { H = A; };
		static void setRo_0(double R0) { ro_0 = R0; };
		static void setPeri(double P) { Peri = P; };
		static void setArea(double S) { Area = S; };
		static void setMassa(double M) { Massa = M; };
		static void setEarthAtmModel(char* str);
		//геты
		Algebra::triple getAcc(double time);




	};
}