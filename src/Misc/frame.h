//-------|преобразование координат|---------------
#pragma once

#include "SpiceUsr.h"
using namespace std;
namespace OrbMod
{
	//coordinate transformation to planet-fixed system
	triple trpos(SpiceDouble et, long int, long int, triple xin);
	void trpos(SpiceDouble et, long int, long int, SpiceDouble xin[3], SpiceDouble xout[3]);
	//coordinate transformation to planet-fixed system
	void trsv(SpiceDouble et, long int, long int, triple xin, triple vin, triple &xout, triple &vout);
	void trsv(SpiceDouble et, long int, long int, SpiceDouble xin[6], SpiceDouble xout[6]);
	//преобразование к невращающейс€ планетофиксированной — 
	void trsv_NR(SpiceDouble et, long int from, long int to, SpiceDouble Xin[6], SpiceDouble Xout[6]);
	//преобразование вектора состо€ни€ в планеоцентрическую квазиинерциальную систему координат
	void trsv_pl(SpiceDouble et, long int from, long int to, SpiceDouble Xin[6], SpiceDouble Xout[6]);
}