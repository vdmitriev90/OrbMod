#include"stdafx.h"
#include"ObsSet.h"
#include<algorithm>
#include <iterator>
#include <algorithm>
#include <vector>
namespace OrbMod
{
	double ObsSet::fct = 1;
	//
	bool ObsSet::isLogResid = false;
	//
	ObsSet::ObsSet()
	{
		isConverg = false;
		sigma = DBL_MAX;
		Nouts = 0;
		for (auto it : Observatory::Obsrs)
			tryAddObs(it.ID, false);
	}
	ObsSet::ObsSet(const ObsSet& other)
	{
		this->isConverg = other.isConverg;
		this->sigma = other.sigma;
		this->Nouts = other.Nouts;
		this->path = other.path;

		//observations
		this->obs.clear();
		for (int i = 0; i < other.obs.size(); i++)
			this->obs.push_back(other.obs[i]->clone());

		this->it = this->obs.begin()+(other.it - other.obs.begin());
		this->it0 = this->obs.begin() + (other.it0 - other.obs.begin());
		this->it_end = this->obs.begin() + (other.it_end - other.obs.begin());
		
		//observatories
		this->isUseObs.clear();
		for (auto it : other.isUseObs)
		{
			this->isUseObs.insert(it);
		}
	}
	//
	ObsSet & ObsSet::operator = (const ObsSet & other)
	{
		if (this != &other) // self-assignment protection
		{
			*this = ObsSet(other);
		}
		return *this;
	}
	//
	bool ObsSet::tryAddObs(string ID, bool val)
	{
		auto it1 = this->isUseObs.begin();
		it1 = this->isUseObs.find(ID);
		if (it1 != this->isUseObs.end()) 
			return false;
		else
		{
			pair<string, bool> p(ID, val);
			this->isUseObs.insert(p);
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
		
		t0 = et_s, te = et_e;

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