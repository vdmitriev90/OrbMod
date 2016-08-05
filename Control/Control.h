#pragma once
//#include"stdafx.h"
using namespace std;
namespace OrbMod
{
	class Control
	{
	public:

		static ObsSet Obs_;

		static void Process(std::string PathConfig);
		static bool loadKernels(std::string path);
		static bool loadObservatories(std::string path);
		static bool loadConfig(std::string path);

	private:
		static bool setTime();
		static void StartProcess();
		static void LogReport(std::string path);

		static void FODE();
		static void ParameterEstimation();
		static void FODE_test();
		static void	debugAction1();
		static void	debugAction2();
		static void	debugAction3();
		static void	debugAction4();
	};
}