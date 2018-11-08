#pragma once
#include"triple.h"

namespace OrbMod
{
	class SRP {
	private:
		Algebra::triple r;
		static double rPl, Mass, Area, Albedo, SRPconst;

	public:
		SRP(void);
		~SRP(void);


		//сеты
		void setpos(Algebra::triple R) { r = R; };
		static void setMass(double M) { Mass = M; };
		static void setArea(double S) { Area = S; };
		static void setAlbedo(double A) { Albedo = A; };
		static void setRadii(int ID);
		static void setSRPconst();

		//геты
		double getRadii() { return rPl; };
		double getSRPconst() { return SRPconst; };
		Algebra::triple getAcceleration(double et);

	};
}