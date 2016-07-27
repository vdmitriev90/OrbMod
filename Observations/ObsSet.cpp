#include"stdafx.h"
#include"ObsSet.h"
#include<algorithm>
namespace OrbMod
{
	ObsSet& ObsSet::Instance()
	{
		static ObsSet singleton;
		return singleton;
	}
	double ObsSet::fct = 1;
	//
	bool ObsSet::isLogResid = false;
	//
	ObsSet::ObsSet()
	{
		isConverg = false;
		sigma = DBL_MAX;
		Nouts = 0;
	}
	//
	bool ObsSet::tryAddObs(string ID, bool val)
	{
		auto it1 = ObsSet::Instance().isUseObs.begin();
		it1 = ObsSet::Instance().isUseObs.find(ID);
		if (it1 != ObsSet::Instance().isUseObs.end()) return false;
		else
		{
			pair<string, bool> p(ID, val);
			ObsSet::Instance().isUseObs.insert(p);
			return true;
		}
	}
	//
	bool ObsSet::LoadObs(std::string FileName, TypeOfObs ObsType)
	{
		obs.clear();
		obs.reserve(2000);
		ifstream file(FileName);
		path = FileName;
		if (file.is_open())
		{
			while (!file.eof())
			{
				std::string line;
				getline(file, line);
				Obs* obsi = ñreateObs(ObsType);
				if (obsi->tryParce(line))
					obs.push_back(obsi);
				else
					delete obsi;
			}
		}
		else return false;
		file.close();

		std::sort(obs.begin(), obs.end(), &Obs::compare);
		it0 = obs.begin();
		it_end = obs.end() - 1;
		if ((*it0)->getType() == "Astrometric") fct = rad2asec;
		return true;
	};
	//
	Obs * ObsSet::ñreateObs(TypeOfObs id)
	{
		Obs * p;
		switch (id)
		{
		case TypeOfObs::Astro: p = new AstroObs();
			break;
		case TypeOfObs::mDist: p = new ModDistObs();
			break;
		case TypeOfObs::mAstro: p = new ModAstroObs();
			break;
		case TypeOfObs::mAstro2: p = new ModAstroObs2();
			break;
		default:
			throw"Invalid Observation code";
		}
		return p;
	}
	//
	void ObsSet::reset()
	{
		it = it0;
	}
	//
	//äâîè÷íûé ïîèñê  ýïîõè ïî âðåìåíè
	Obsiter ObsSet::FindTime(double time)
	{
		int min = 0;
		int max = obs.size();
		int mid = 0;

		if (obs[0]->t > time) return obs.begin();
		if (obs[max - 1]->t < time) return obs.end() - 1;

		while (min < max)
		{
			mid = min + (max - min) / 2;

			if (time <= obs[mid]->t)
				max = mid;
			else
				min = mid + 1;
		}
		auto iter = obs.begin();
		for (size_t i = 0; i < mid; i++) iter++;

		return iter;
	}
	//
	bool ObsSet::setTimeFrames(double et_s, double et_e)
	{
		if (obs.size() < 2) return false;
		it0 = obs.begin();
		int N = obs.size();

		it = it0 = FindTime(et_s);
		it_end = FindTime(et_e);

		return true;
	}
	//
	int ObsSet::getObsNum()
	{
		return (it_end - it0);
	}
}