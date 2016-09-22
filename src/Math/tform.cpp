#include "stdafx.h"
#include "tform.h"
namespace OrbMod
{
	//
	void tform::trpos(char * from, char * to, double t, triple& in, triple& out)
	{
		double posi[3], poso[3], rotate[3][3];
		for (int i = 0; i < 3; i++) posi[i] = in[i];
		pxform_c(from, to, t, rotate);
		mxv_c(rotate, posi, poso);
		out = triple(poso);
	}
	//
	void tform::trsvs(char * from, char * to, double t, Matrix &SV)
	{
		double posi[6], poso[6], rotate[6][6];
		for (int i = 0; i < 6; i++) posi[i] = SV(i, 0);
		sxform_c(from, to, t, rotate);
		mxv_c(rotate, posi, poso);
		for (int i = 0; i < 6; i++) SV(i, 0) = poso[i];
	}
}
