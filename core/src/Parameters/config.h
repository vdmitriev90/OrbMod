#pragma once

#include"state.h"
#include"constant.h"

#include<map>
#include<vector>
typedef unsigned uint;

typedef bool(*parce_ptr)(const std::string & s);
typedef std::string(*format_ptr)(void);
typedef std::map< std::string, parce_ptr> parce_dict;
typedef std::vector<format_ptr> formatters;

namespace OrbMod
{
	class config
	{
	private:
		static parce_dict  parceDict;
		static formatters formatDict;

#pragma region parcers
		static bool IsTestMode(const std::string & s);
		static bool FittingMode(const std::string & s);
		static bool Obs(const std::string & s);
		static bool MinObsInbatch(const std::string & s);
		static bool ArcLength(const std::string & s);
		static bool NmNr(const std::string & s);
		static bool CB(const std::string & s);
		static bool Int(const std::string & s);
		static bool Var(const std::string & s);
		static bool NOR(const std::string & s);
		static bool step(const std::string & s);
		static bool eps(const std::string & s);
		static bool Autostep(const std::string & s);
		static bool Niter(const std::string & s);
		static bool t0(const std::string & s);
		static bool te(const std::string & s);
		static bool frame(const std::string & s);
		static bool EarthFixedFrame(const std::string & s);
		static bool tscale(const std::string & s);
		static bool TypeIC(const std::string & s);
		static bool UsePeriTime(const std::string & s);
		static bool IC(const std::string & s);
		static bool BigPlanets(const std::string & s);
		static bool AddBodies(const std::string & s);
		static bool AddBody5HT(const std::string & s);
		static bool CBHterms(const std::string & s);
		static bool Rel(const std::string & s);
		static bool SRP(const std::string & s);
		static bool Discr(const std::string & s);
		static bool Out(const std::string & s);
		static bool BFFID(const std::string & s);
		static bool Colors(const std::string & s);
		static bool useObs(const std::string & s);
		static bool ObsTimeFrame(const std::string & s);
		static bool ObservationsPath(const std::string & s);
		static bool orbFitEps(const std::string & s);
		static bool orbFitNiter(const std::string & s);
		static bool orbFitNiterPerBatch(const std::string & s);
		static bool orbFitRejOuts(const std::string & s);

		static bool IsLogResiduals(const std::string & s);
		static bool aprioriRMS(const std::string & s);
		static bool processNoise(const std::string & s);

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

		static bool SaveCFG(std::string fileName);
		static bool LoadCFG(std::string fileName);
		static bool SetIC(std::string IC[], int IDC, consts::TypeOfIC ICtype, consts::FrameOfIC ICframe);
		static bool GetIC(std::string *IC, int IDC, consts::TypeOfIC ICtype, consts::FrameOfIC ICframe);

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

