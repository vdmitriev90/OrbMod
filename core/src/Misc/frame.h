#pragma once
#include "triple.h"
using namespace std;
namespace OrbMod
{
	//coordinate transformation to planet-fixed system
	Algebra::triple trpos(double et, long int, long int, Algebra::triple xin);
	
    void trpos(double et, long int, long int, double xin[3], double xout[3]);
	
    //coordinate transformation to planet-fixed system
	void trsv(double et, long int, long int, Algebra::triple xin, Algebra::triple vin, Algebra::triple &xout, Algebra::triple &vout);
	
    void trsv(double et, long int, long int, double xin[6], double xout[6]);
	
    //преобразование к невращающейся планетофиксированной СК
	void trsv_NR(double et, long int from, long int to, double Xin[6], double Xout[6]);
	
    //преобразование вектора состояния в планеоцентрическую квазиинерциальную систему координат
	void trsv_pl(double et, long int from, long int to, double Xin[6], double Xout[6]);
}