#pragma once
#include"constant.h"
#include"dateTime.h"

namespace OrbMod
{
	class Misc
	{
	public:
		static int sum(int N);
		static std::vector<double> setSpacing(int NOR, char *path);
		static const std::vector<std::string> splitStr(const std::string& s, const char& c);
		static const std::vector<std::string> splitStr(const std::string& s, const char* c, int num);
		static const std::vector<std::string> splitStr(const std::string& s, const std::string &c);
		static const std::vector<std::string> splitStr2(const std::string& s, const char& c);

		static std::string  ToString(int d) { if (d == 0) return ""; else return ToString(d); };
		static  double dms2deg(int &sign, int &d, int &m, double &sec);
		static bool str2deg(std::string &str, const char& sep, double &deg);
		static bool tryPrcSpUTC(std::string &s, dateTime &dt);
		static bool parceTime(std::string str_in, consts::TimeFormat F, double &et);
		static bool et2cal(double et, consts::TimeFormat F, std::string &str_out);
	};
}
