#include "stdafx.h"
#include "Misc.h"
namespace OrbMod
{
	int Misc::sum(int N)
	{
		int s = 0;
		for (int i = 0; i <= N; i++)
		{
			s = s + i;
		}
		return(s);
	}
	//set spacing for Everchart integrator
	vector<double> Misc::setSpacing(int NOR, char *path)
	{
		int ii = 1;
		int jj = 0;
		FILE*f = fopen(path, "r");
		char lineRad[300];

		vector<double> Spacing(NOR + 1);
		Spacing[0] = 0.0;
		while (!feof(f))
		{
			fscanf(f, "%s\n", lineRad);
			if (ii > Misc::sum(NOR - 1) && ii <= Misc::sum(NOR))
			{
				Spacing[jj + 1] = atof(lineRad);
				jj++;
			}
			ii++;
		}
		fclose(f);
		return Spacing;
	}
	//Split a String
	//http://www.cplusplus.com/articles/2wA0RXSz/
	const vector<string>  Misc::splitStr(const string& s, const char& c)
	{
		string buff{ "" };
		vector<string> v;

		for (auto n : s)
		{
			if (n != c) buff += n; else
				if (n == c && buff != "") { v.push_back(buff); buff = ""; }
		}
		if (buff != "") v.push_back(buff);

		return v;
	}
	const vector<string>  Misc::splitStr(const string& s, const string &c)
	{
		string buff{ "" };
		vector<string> v;

		for (auto n : s)
		{
			bool b = false;
			for (auto m : c)
			{
				if (n == m)
				{
					b = true;
					break;
				}
			}
			if (!b) buff += n; else
				if (b && buff != "") { v.push_back(buff); buff = ""; }
		}
		if (buff != "") v.push_back(buff);

		return v;
	}
	const vector<string>  Misc::splitStr(const string& s, const char* c, int num)
	{
		string buff{ "" };
		vector<string> v;

		for (auto n : s)
		{
			bool b = false;
			for (int i = 0; i < num; i++)
			{
				if (n == c[i])
				{
					b = true;
					break;
				}
			}
			if (!b) buff += n;
			else
				if (b && buff != "")
				{
					v.push_back(buff); buff = "";
				}
		}
		if (buff != "") v.push_back(buff);

		return v;
	}
	const vector<string>  Misc::splitStr2(const string& s, const char& c)
	{
		string buff{ "" };
		vector<string> v(2);
		bool b = false;
		for (auto n : s)
		{
			if (b == false)
			{
				if (n != c)
					buff += n;
				else
				{
					b = true;
					v[0] = buff;
					buff = "";
				}
			}
			else
			{
				buff += n;
			}
		}
		if (buff != "") v[1] = buff;

		return v;
	}
	//
	double Misc::dms2deg(int &sign, int &d, int &m, double &sec)
	{
		return sign*(abs(d) + m / 60.0 + sec / 3600.0);
	}
	//
	bool Misc::str2deg(string &str, const char& sep, double &deg)
	{
		vector<string> v = Misc::splitStr(str, sep);
		if (v.size() < 3) return false;
		int sign;
		switch (v[0][0])
		{
		case '+':sign = 1;
			break;
		case '-':sign = -1;
			break;
		default:
			sign = 1;
			break;
		}
		int d = stoi(v[0]);
		int m = stoi(v[1]);
		double sec = stod(v[2]);
		deg = dms2deg(sign, d, m, sec);
		return true;
	}

	// 2010 06 30 00:00:00.0000000
	bool Misc::tryPrcSpUTC(string &s, dateTime &dt)
	{
		vector<string> w = splitStr(s, 'T');
		if (w.size() < 2) return false;
		vector<string> w1 = splitStr(w[0], '-');
		if (w1.size() < 3) return false;
		dt.Y = stoi(w1[0]);
		dt.M = stoi(w1[1]);
		dt.D = stoi(w1[2]);
		vector<string> w2 = splitStr(w[1], ':');
		if (w2.size() < 3) return false;
		dt.h = stoi(w2[0]);
		dt.min = stoi(w2[1]);
		dt.sec = stod(w2[2]);
		return true;
	}
	bool Misc::parceTime(string str_in, double &et)
	{
		double t0 = 0;
		if (Global::i_tscale == 0)
		{
			const char *utc1 = str_in.c_str();
			str2et_c(utc1, &t0);
		}
		else if (Global::i_tscale == 1)
			t0 = stod(str_in);
		else if (Global::i_tscale == 2)
		{
			str_in += " TDB";
			const char *tdb1 = str_in.c_str();
			str2et_c(tdb1, &t0);
		}
		else
		{
			str_in += " TDT";
			const char *tdt1 = str_in.c_str();
			str2et_c(tdt1, &t0);
		}
		et = t0;
		return true;
	}
	bool Misc::et2cal(double et, string &str_out)
	{
		char str[50];

		if (Global::i_tscale == 0)
			timout_c(et, Global::pictur_utc, 50, str);
		else if (Global::i_tscale == 1)
			sprintf(str, "%20.13f", et);

		else if (Global::i_tscale == 2)
			timout_c(et, Global::pictur_tdb, 50, str);
		else
			timout_c(et, Global::pictur_tdt, 50, str);
		str_out = str;
		return true;
	}
}