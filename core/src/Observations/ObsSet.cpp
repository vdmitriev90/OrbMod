#include"stdafx.h"
#include"ObsSet.h"
#include "constant.h"
#include "AstroObs.h"
#include "ModAstroObs.h"
#include "ModAstroObs2.h"
#include "ModDistObs.h"

#include<algorithm>
#include <fstream>

using namespace Algebra;
using namespace consts;
using namespace std;

namespace OrbMod
{
	double ObsSet::fct = 1;
	//
	bool ObsSet::isLogResid = false;

	ObsSet::ObsSet()
	{
		isConverg = false;
		sigma = DBL_MAX;
		Nouts = 0;
		for (auto it : Observatory::Obsrs)
			tryAddObs(it.ID, false);

		this->it = this->it = 0;
		this->it_end = 0;
	}

	ObsSet::ObsSet(const ObsSet& other)
	{
		if (this != &other) // self-assignment protection
		{
			this->isConverg = other.isConverg;
			this->sigma = other.sigma;
			this->Nouts = other.Nouts;
			this->path = other.path;

			//observations
			this->obs.clear();
			for (int i = 0; i < other.obs.size(); i++)
				this->obs.push_back(other.obs[i]->clone());

			this->it = other.it;
			this->it0 = other.it0;
			this->it_end = other.it_end;

			//observatories
			this->isUseObs.clear();
			for (auto&& it : other.isUseObs)
				this->isUseObs.insert(it);
			
		}
	}

	//
	ObsSet & ObsSet::operator = (const ObsSet & other)
	{
		if (this != &other) // self-assignment protection
		{
			this->isConverg = other.isConverg;
			this->sigma = other.sigma;
			this->Nouts = other.Nouts;
			this->path = other.path;

			//observations
			this->obs.clear();
			for (int i = 0; i < other.obs.size(); i++)
				this->obs.push_back(other.obs[i]->clone());

			this->it = other.it;
			this->it0 = other.it0;
			this->it_end = other.it_end;

			//observatories
			this->isUseObs.clear();
			for (auto&& it : other.isUseObs)
				this->isUseObs.insert(it);
			
		}
		return *this;
	}
	//Obs  &ObsSet::operator[](const int index)
	//{
	//	if (index < obs.size())
	//		return *(obs[index]);
	//}
	//
	Vobs::iterator ObsSet:: begin()
	{
		return obs.begin();
	}
	Vobs::iterator ObsSet:: end()
	{
		return obs.end();
	}
	//
	bool ObsSet::next()
	{
		it++;
		return (it == this->obs.size()) ? 0 : 1;
	}
	//
	Obs  &ObsSet::curr()
	{
		return *obs[it];
	}
	//
	Obs  &ObsSet::first()
	{
		return *obs[it0];
	}
	//
	Obs &ObsSet::last()
	{
		return *obs[it_end];
	}
	//

	void ObsSet::reset()
	{
		it = it0;
	}
	//
	size_t ObsSet::size()
	{
		return obs.size();
	}
	//
	int ObsSet::getObsNum()
	{
		return (it_end - it0);
	}
	//
	bool ObsSet::tryAddObs(const string& ID, bool val)
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
	bool ObsSet::LoadObs(const string& FileName, TypeOfObs ObsType)
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
		else 
            return false;

		file.close();

		std::sort(obs.begin(), obs.end(), &Obs::compare);
		it0 = 0;
		it_end = obs.size() - 1;
		if ((obs[0])->getType() == "Astrometric") fct = rad2asec;
		return true;
	};
	//
    Obs * ObsSet::ñreateObs(TypeOfObs id)
    {
        switch (id)
        {
        case TypeOfObs::Astro: return new AstroObs();
            break;
        case TypeOfObs::mDist: return new ModDistObs();
            break;
        case TypeOfObs::mAstro: return new ModAstroObs();
            break;
        case TypeOfObs::mAstro2: return new ModAstroObs2();
            break;
        default:
            throw invalid_argument("Unsupported type of observations");
        }
    }

	//
	//äâîè÷íûé ïîèñê  ýïîõè ïî âðåìåíè
	int ObsSet::FindTime(double time)
	{
		int min = 0;
        size_t max = obs.size();
		int mid = 0;

		if (obs[0]->t > time) return 0;
		if (obs[max - 1]->t < time) return obs.size()-1 ;

		while (min < max)
		{
			mid = min + (max - min) / 2;

			if (time <= obs[mid]->t)
				max = mid;
			else
				min = mid + 1;
		}
		return mid;
	}
	//
	bool ObsSet::setTimeFrames(double et_s, double et_e)
	{
		if (obs.size() < 2) return false;
		it0 = 0;
        size_t N = obs.size();
		
		t0 = et_s, te = et_e;

		it = it0 = FindTime(et_s);
		it_end = FindTime(et_e);

		return true;
	}

}