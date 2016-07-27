#include"stdafx.h"
#include"dateTime.h"
using namespace std;
namespace OrbMod
{
	dateTime::dateTime()
	{
		Y = 0, M = 0, D = 0, h = 0, min = 0, sec = 0;
	}
	dateTime::dateTime(int Y_, int M_, int D_, int h_, int min_, double sec_)
	{
		Y = Y_, M = M_, D = D_, h = h_, min = min_, sec = sec_;
	}

	dateTime::dateTime(int Y_, int M_, int D_, int h_, int min_, int sec_, int msec_)
	{
		Y = Y_, M = M_, D = D_, h = h_, min = min_, sec = sec_ + msec_ / 1000.0;
	}
	double dateTime::msec()
	{
		return (int)((sec - (int)sec) * 1000 + 0.5);
	}
	string dateTime::toString()
	{
		char  c_Y[5], c_Mounth[3], c_Day[3], c_hours[3], c_min[3];
		sprintf(c_Y, "%.4i", Y);
		sprintf(c_Mounth, "%.2i", M);
		sprintf(c_Day, "%.2i", D);
		sprintf(c_hours, "%.2i", h);
		sprintf(c_min, "%.2i", min);
		string s = "";
		s += c_Y; s += '-';
		s += c_Mounth;	s += '-';
		s += +c_Day; s += 'T';
		s += c_hours; s += ':';
		s += c_min; s += ':';
		s += to_string(sec);
		return s;

	}
	dateTime::~dateTime()
	{

	}
	JD2::JD2(double jd1_, double jd2_)
	{
		jd1 = jd1_, jd2 = jd2_;
	}
	JD2::JD2(dateTime dt, char* scale)
	{

	}
}