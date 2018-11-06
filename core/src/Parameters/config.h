#pragma once
#include"stdafx.h"
#include<map>
using namespace std;
typedef unsigned uint;

typedef  bool(*parce_ptr)(const string & s);
typedef  string(*format_ptr)(void);
typedef map< string, parce_ptr> parce_dict;
typedef vector<format_ptr> formatters;

namespace OrbMod
{
	class config
	{
	private:
		static parce_dict  parceDict;
		static formatters formatDict;

#pragma region parcers
		static bool IsTestMode(const string & s);
		static bool FittingMode(const string & s);
		static bool Obs(const string & s);
		static bool MinObsInbatch(const string & s);
		static bool ArcLength(const string & s);
		static bool NmNr(const string & s);
		static bool CB(const string & s);
		static bool Int(const string & s);
		static bool Var(const string & s);
		static bool NOR(const string & s);
		static bool step(const string & s);
		static bool eps(const string & s);
		static bool Autostep(const string & s);
		static bool Niter(const string & s);
		static bool t0(const string & s);
		static bool te(const string & s);
		static bool frame(const string & s);
		static bool EarthFixedFrame(const string & s);
		static bool tscale(const string & s);
		static bool TypeIC(const string & s);
		static bool UsePeriTime(const string & s);
		static bool IC(const string & s);
		static bool BigPlanets(const string & s);
		static bool AddBodies(const string & s);
		static bool AddBody5HT(const string & s);
		static bool CBHterms(const string & s);
		static bool Rel(const string & s);
		static bool SRP(const string & s);
		static bool Discr(const string & s);
		static bool Out(const string & s);
		static bool BFFID(const string & s);
		static bool Colors(const string & s);
		static bool useObs(const string & s);
		static bool ObsTimeFrame(const string & s);
		static bool ObservationsPath(const string & s);
		static bool orbFitEps(const string & s);
		static bool orbFitNiter(const string & s);
		static bool orbFitNiterPerBatch(const string & s);
		static bool orbFitRejOuts(const string & s);

		static bool IsLogResiduals(const string & s);
		static bool aprioriRMS(const string & s);
		static bool processNoise(const string & s);

#pragma endregion

#pragma region formatters
		static std::string IsTestMode();
		static std::string FittingMode();
		static std::string Obs();
		static std::string MinObsInbatch();
		static std::string ArcLength();
		static std::string NmNr();
		static std::string CB();
		static std::string Int();
		static std::string Var();
		static std::string NOR();
		static std::string Step();
		static std::string Eps();
		static std::string IsAutoStep();
		static std::string Niter();
		static std::string T_start();
		static std::string T_end();
		static std::string Frame();
		static std::string EarthFixedFrame();
		static std::string Time_scale();
		static std::string TypeIC();
		static std::string UsePeriTime();
		static std::string IC();
		static std::string BigPlanets();
		static std::string AddBodies();
		static std::string AddBody5HT();
		static std::string CBHterms();
		static std::string Rel();
		static std::string SRP();
		static std::string Discr();
		static std::string Out();
		static std::string BFFID();
		static std::string Colors();
		static std::string useObs();
		static std::string ObsTimeFrame();
		static std::string ObservationsPath();
		static std::string orbFitEps();
		static std::string orbFitNiter();
		static std::string orbFitNiterPerBatch();
		static std::string orbFitRejOuts();

		static std::string IsLogResiduals();
		static std::string aprioriRMS();
		static std::string processNoise();


#pragma endregion

	public:
		config();
		~config();

		static bool SaveCFG(string fileName);
		static bool LoadCFG(string fileName);
		static bool SetIC(std::string IC[], int IDC, TypeOfIC ICtype, FrameOfIC ICframe);
		static bool GetIC(std::string *IC, int IDC, TypeOfIC ICtype, FrameOfIC ICframe);

#pragma region буферные переменные 
		static int		NameNr;
		static double  SV[6];
		static std::string	s_t0;
		static std::string	s_te;
		static std::string	s_fileCBHarm;
		static std::string	s_fileAddHarm;

		static double SRP_albedo;
		static double SRP_S;
		static double SRP_Mass;
#pragma endregion

	};
}

