#pragma once


namespace OrbMod
{
	class Control
	{
	public:
		static void Process();
	private:
		static void FODE();
		static void ParameterEstimation();
		static void FODE_test();
		static void	debugAction1();
		static void	debugAction2();
		static void	debugAction3();
		static void	debugAction4();
	};
}