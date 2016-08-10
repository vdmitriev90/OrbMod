#pragma once
#include"stdafx.h"
typedef vector<OrbMod::Obs*>::iterator Obsiter;
namespace OrbMod
{
	class ObsSet
	{
	public:
		//static  ObsSet& Instance();
		static bool isLogResid;
		static double fct;
		~ObsSet()
		{
			for (int i = obs.size() - 1; i >= 0; --i)  delete obs[i];
		}

		double sigma,t0,te;
		bool isConverg;
		int  Nouts;

		ofstream f_res;
		vector<Obs*> obs;
		Obsiter it;
		Obsiter it_end;
		std::string path = "obs_def.in";
		//список используемых обсерваторий
		map<string, bool> isUseObs;

		bool tryAddObs(string ID, bool val);
		bool LoadObs(std::string FileName, TypeOfObs ObsType);
		void reset();
		bool setTimeFrames(double et_0, double et_1);
		int getObsNum();
		Obsiter  FindTime(double et);

	
		ObsSet();
		ObsSet(const ObsSet& other);

	private:
		Obsiter it0;

		//порождающая функция
		Obs * сreateObs(TypeOfObs id);

	};
}