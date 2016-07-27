#pragma once
using namespace std;
#include"stdafx.h"
class dateTime;
namespace OrbMod
{
	class Misc
	{
	public:
		static int sum(int N);
		static vector<double> setSpacing(int NOR, char *path);
		static const vector<string> splitStr(const string& s, const char& c);
		static const vector<string>  splitStr(const string& s, const char* c, int num);
		static const vector<string>  splitStr(const string& s, const string &c);
		static const vector<string> splitStr2(const string& s, const char& c);

		static string  Tostring(int d) { if (d == 0) return ""; else return to_string(d); };
		static  double dms2deg(int &sign, int &d, int &m, double &sec);
		static bool str2deg(string &str, const char& sep, double &deg);
		static bool tryPrcSpUTC(string &s, dateTime &dt);
		static bool parceTime(string str_in, double &et);
		static bool et2cal(double et, string &str_out);
	};
}
