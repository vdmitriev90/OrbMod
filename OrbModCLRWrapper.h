#pragma once
#include"OrbModLib\src\stdafx.h"
#include"_ObsSet.h"
using namespace System;
using namespace OrbMod;

namespace OrbModCLRWrapper {



	public ref class OrbModWrap
	{
	public:
		static OrbModWrap ^Instance;
		
		OrbModWrap();
		

		OrbModWrap(const ObsSet& setObs);

		String ^ getVersion();
		_ObsSet ^SetObserv;

		static void OrbModWrap::getObsSetFromCtrl();
		static void Process(System ::String ^path);
		static bool loadKernels(System::String ^path);
		static bool loadObservatories(System::String ^path);
		static bool loadConfig(System::String ^path);
		static bool parseTime(System::String ^path, int TF, double % t);

		static bool setIC(cli::array <String^, 1> ^, int IDC, int ICtype, int ICframe);
		static cli::array <String^, 1> ^ getIC( int IDC, int ICtype, int ICframe);

	};

}
