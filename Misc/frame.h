//-------|преобразование координат|---------------
#pragma once

#include "SpiceUsr.h"
using namespace std;
namespace OrbMod
{
	//преобразование координат в планетофиксированную систему координат	
	triple trpos(SpiceDouble et, long int, long int, triple xin);
	void trpos(SpiceDouble et, long int, long int, SpiceDouble xin[3], SpiceDouble xout[3]);
	//преобразование вектора состояния в планетофиксированную систему координат
	void trsv(SpiceDouble et, long int, long int, triple xin, triple vin, triple &xout, triple &vout);
	void trsv(SpiceDouble et, long int, long int, SpiceDouble xin[6], SpiceDouble xout[6]);
	//преобразование к невращающейся планетофиксированной СК
	void trsv_NR(SpiceDouble et, long int from, long int to, SpiceDouble Xin[6], SpiceDouble Xout[6]);
	//преобразование вектора состояния в планеоцентрическую квазиинерциальную систему координат
	void trsv_pl(SpiceDouble et, long int from, long int to, SpiceDouble Xin[6], SpiceDouble Xout[6]);
}