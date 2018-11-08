#pragma once
#include"constant.h"
#include"Obs.h"

#include<fstream>
#include<map>


namespace OrbMod
{
    typedef std::vector<Obs*> Vobs;

    class ObsSet
    {

    public:
        //static  ObsSet& Instance();
        static bool isLogResid;
        static double fct;

        static ObsSet setObs;
        unsigned it;
        unsigned it_end;
        double sigma, t0, te;
        bool isConverg;
        int  Nouts;
        std::ofstream f_res;

        std::string path = "obs_def.in";
        //список используемых обсерваторий
        std::map<std::string, bool> isUseObs;

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
        size_t size();
        int getObsNum();

        bool tryAddObs(std::string ID, bool val);
        bool LoadObs(std::string FileName, consts::TypeOfObs ObsType);
        bool setTimeFrames(double et_0, double et_1);
        int  FindTime(double et);

    protected:
        unsigned it0;

        Vobs obs;
        //порождающая функция
        Obs * сreateObs(consts::TypeOfObs id);

    };
}