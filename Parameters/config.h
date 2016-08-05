#pragma once
#include"stdafx.h"
#include<map>
using namespace std;
typedef unsigned uint;

typedef  bool(*parce_ptr)(std::string s);
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
		static bool IsTestMode(string s);
		static bool FittingMode(string s);
		static bool Obs(string s);
		static bool MinObsInbatch(string s);
		static bool ArcLength(string s);
		static bool NmNr(string s);
		static bool CB(string s);
		static bool Int(string s);
		static bool Var(string s);
		static bool NOR(string s);
		static bool step(string s);
		static bool eps(string s);
		static bool Autostep(string s);
		static bool Niter(string s);
		static bool t0(string s);
		static bool te(string s);
		static bool frame(string s);
		static bool EarthFixedFrame(string s);
		static bool tscale(string s);
		static bool TypeIC(string s);
		static bool UsePeriTime(string s);
		static bool IC(string s);
		static bool BigPlanets(string s);
		static bool AddBodies(string s);
		static bool AddBody5HT(string s);
		static bool CBHterms(string s);
		static bool Rel(string s);
		static bool SRP(string s);
		static bool Discr(string s);
		static bool Out(string s);
		static bool BFFID(string s);
		static bool Colors(string s);
		static bool useObs(string s);
		static bool ObservationsPath(string s);
		static bool orbFitEps(string s);
		static bool orbFitNiter(string s);
		static bool orbFitNiterPerBatch(string s);
		static bool orbFitRejOuts(string s);

		static bool IsLogResiduals(string s);
		static bool aprioriRMS(string s);
		static bool processNoise(string s);

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

