#pragma once
#include"constant.h"
#include"Observations.h"

#include<fstream>
#include<map>
#include<memory>


namespace OrbMod
{
    typedef std::vector<std::shared_ptr<Observations>> Vobs;

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
            //for (size_t i = obs.size() - 1; i >= 0; --i)  
            //    delete obs[i];
        }

        //
        Vobs::iterator begin();
        Vobs::iterator end();
        //
        //Obs  &operator[](const int index);

        Observations  &curr();
        Observations  &first();
        Observations &last();

        void reset();
        bool next();
        size_t size();
        int getObsNum();

        bool tryAddObs(const std::string & ID, bool val);
        bool LoadObs(const std::string & FileName, consts::TypeOfObs ObsType);
        bool setTimeFrames(double et_0, double et_1);
        int  FindTime(double et);

    protected:
        unsigned it0;

        Vobs obs;
        //порождающая функция
        obs_ptr сreateObs(consts::TypeOfObs id);

    };
}