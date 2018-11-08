#pragma once
#include"ObsSet.h"
#include"Observations.h"
#include"constant.h"

namespace OrbMod
{
	class Control
	{
	public:
		
//		static Control();
		//Control(const Control& othr);
		static ObsSet &inst();
		//~Control();
		static ObsSet Obs_;
		static bool loadObseravations(const std::string& path, consts::TypeOfObs OType);
		//static 
		static void Process(const std::string& PathConfig);
		static bool loadKernels(const std::string& path);
		static bool loadObservatories(const std::string& path);
		static bool loadConfig(const std::string& path);

		static bool parseTime(const std::string& s_t, consts::TimeFormat TForm, double t);
		
	private:
		
		static bool setTime();
		static bool InitProcess();
		static void FinalizeProcess();
		static void StartProcess();
		static void LogReport(const std::string& path);
		//
		static void FODE();
		static void ParameterEstimation();
		static void FODE_test();
		//
		static void	debugAction1();
		static void	debugAction2();
		static void	debugAction3();
		static void	debugAction4();
	};
}