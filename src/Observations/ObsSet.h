#pragma once
#include"stdafx.h"
//typedef vector<OrbMod::Obs*>::iterator Obsiter;
namespace OrbMod
{
	typedef vector<Obs*> Vobs;

	class ObsSet
	{
		
	public:
		//static  ObsSet& Instance();
		static bool isLogResid;
		static double fct;

		static ObsSet setObs;
		uint it;
		uint it_end;
		double sigma, t0, te;
		bool isConverg;
		int  Nouts;
		ofstream f_res;

		std::string path = "obs_def.in";
		//список используемых обсерваторий
		map<string, bool> isUseObs;

		ObsSet();
		ObsSet(const ObsSet& other);
		//assignment operator
		ObsSet & operator = (const ObsSet & other);

		~ObsSet()
		{
			for (int i = obs.size() - 1; i >= 0; --i)  delete obs[i];
		}
		//
		Vobs::iterator begin();
		Vobs::iterator end();
		//
		//Obs  &operator[](const int index);
		
		Obs  &curr();
		Obs  &first();
		Obs &last();


		void reset();
		bool next();
		uint size();
		int getObsNum();


		bool tryAddObs(string ID, bool val);
		bool LoadObs(std::string FileName, TypeOfObs ObsType);
		bool setTimeFrames(double et_0, double et_1);
		uint  FindTime(double et);


	protected:
		uint it0;

		Vobs obs;
		//порождающая функция
		Obs * сreateObs(TypeOfObs id);

	};
}