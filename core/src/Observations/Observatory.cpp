#include "Observatory.h"
#include "constant.h"
#include "Control.h"

#include <fstream>

using namespace Algebra;
using namespace consts;
using namespace std;

namespace OrbMod
{
	Observatory::Observatory()
	{
	}
	//
	Observatory::Observatory(const Observatory& obsy)
	{
		this->ID = obsy.ID;
		this->X = obsy.X;
		this->Name = obsy.Name;
	}
	//
	Observatory::~Observatory()
	{
	}
	//
	vector<Observatory> Observatory::Obsrs;
	//
	map<string, Observatory> Observatory::str2Obsy;
	//
	bool Observatory::tryParce(const string &str)
	{
		double lon, rxy, rz;
		if (str.length() < 34) return false;
		try
		{
			this->ID = str.substr(0, 3);
			lon = stod(str.substr(3, 10))*deg2rad;
			rxy = stod(str.substr(13, 9))*Re;
			rz = stod(str.substr(22, 10))*Re;
			this->Name = str.substr(32, str.length());
		}
		catch (...)
		{
			return false;
		}

		this->X[0] = rxy*cos(lon);
		this->X[1] = rxy*sin(lon);
		this->X[2] = rz;

		return true;
	}
	//
	bool Observatory::LoadObsrs(std::string FileName)
	{
		Obsrs.clear();
		Obsrs.reserve(2000);
		ifstream file(FileName);

		if (file.is_open())
		{
			std::string line;
			//header line
			getline(file, line);
			while (!file.eof())
			{
				getline(file, line);
				Observatory obry;
				if (obry.tryParce(line))
					Obsrs.push_back(obry);
			}
		}
		else return false;
		file.close();
		for (auto it : Obsrs)
		{
			str2Obsy.insert(std::pair<string, Observatory>(it.ID, it));
			Control::Obs_.tryAddObs(it.ID, false);
		}

		return true;
	}
}