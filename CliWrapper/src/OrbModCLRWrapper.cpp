// This is the main DLL file.
#include"Marshaling.h"
#include "OrbModCLRWrapper.h"

#include"constant.h"
#include"Control.h"
#include"Global.h"
#include"config.h"

using namespace OrbMod;
using namespace consts;
using namespace ZedGraph;
using namespace std;

namespace OrbModCLRWrapper
{

	//
	void OrbModWrap::Process(System::String ^path)
	{
		OrbMod::Control::Process(Marsh::S2s(path));
	}
	//
	bool OrbModWrap::loadKernels(System::String ^path)
	{
		std::string str = Marsh::S2s(path);
		bool b = OrbMod::Control::loadKernels(str);
		return b;
	}
	//
	bool OrbModWrap::loadObservatories(System::String ^path)
	{
		return OrbMod::Control::loadObservatories(Marsh::S2s(path));
	}
	//
	bool OrbModWrap::loadConfig(System::String ^path)
	{
		return OrbMod::Control::loadConfig(Marsh::S2s(path));
	}
	//
	bool OrbModWrap::parseTime(System::String ^path, int TF, double % t)
	{
		double et = 0;
		if(!Control::parseTime(Marsh::S2s(path), (TimeFormat)TF, et)) return false;
		t = et;
		return true;
	}
	//
	String ^ OrbModWrap::getVersion()
	{
		return(Marsh::s2S(Global::FormCaption));
	}
	//
	bool OrbModWrap::setIC(cli::array <String^, 1> ^ IC, int IDC, int ICtype, int ICframe)
	{
		if (IC->Length < 6) return false;
		string sIC[6];
		for (size_t i = 0; i < 6; i++)
			sIC[i] = Marsh::S2s(IC[i]);
		return config::SetIC(sIC, IDC, (TypeOfIC)ICtype, (FrameOfIC)ICframe);
	}
	cli::array <String^, 1> ^  OrbModWrap::getIC( int IDC, int ICtype, int ICframe)
	{
		string sIC[6];
		config::GetIC(sIC, IDC, (TypeOfIC)ICtype, (FrameOfIC)ICframe);
		cli::array <String^, 1> ^ IC = gcnew  cli::array<String^>(6);

		for (size_t i = 0; i < 6; i++)
			IC[i] = Marsh::s2S(sIC[i]);

		return IC;
	}

}
