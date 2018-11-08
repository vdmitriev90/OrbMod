#pragma once;
#include<string>
namespace OrbMod
{
	class dateTime
	{
	public:
		dateTime();
		~dateTime();
		dateTime(int Y, int M, int D, int h, int min, double sec);
		dateTime(int Y, int M, int D, int h, int min, int sec, int msec);

		int Y, M, D, h, min;
		double	sec;
		double msec();
		std::string toString();
	};
	class JD2
	{
	public:
		double jd1, jd2;
		JD2(double jd1_, double jd2_);
		JD2(const dateTime & dt, char* scale);
	};
}
