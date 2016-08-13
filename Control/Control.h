#pragma once
//#include"stdafx.h"
using namespace std;
namespace OrbMod
{
	class Control
	{
	public:
		
		Control();
		Control(const Control& othr);

		~Control();
		ObsSet *Obs_;
		//static 
		static Control Inst;
		static void Process(std::string PathConfig);
		static bool loadKernels(std::string path);
		static bool loadObservatories(std::string path);
		static bool loadConfig(std::string path);

		static bool parseTime(string s_t, TimeFormat TForm, double t);
		
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