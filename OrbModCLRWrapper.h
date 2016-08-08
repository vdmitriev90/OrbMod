// OrbModCLRWrapper.h

#pragma once
#include"OrbModLib\src\stdafx.h"
using namespace System;
using namespace OrbMod;

namespace OrbModCLRWrapper {


	public ref class _ObsSet : System::IDisposable
	{
	public:

		_ObsSet();
		_ObsSet(const ObsSet setObs);
		~_ObsSet();

		//public fields
		int N;

		//methods
		ObsSet getIntObsSet();
		bool LoadObs(System::String ^path, int ObsType);
		void reset();
		bool setTimeFrames(double et_0, double et_1);
		int getObsNum();
		String ^ TypeOfObserv();
		void DataToForm(ZedGraph::GraphPane ^pane, System::Windows::Forms::DataGridView^  dgv_1);
		void _ObsSet::ChangeTimeFrame(ZedGraph ::GraphPane ^pane, System::Windows::Forms::DataGridView^  dgv_1, String ^t_start, String ^t_finish);
		void SetUseObs(String ^ID, bool use);

	private:
		ObsSet *setO;

	};

	public ref class OrbModWrap
	{
	public:
		static OrbModWrap ^Instance;
		
		OrbModWrap();
		static OrbModWrap();
		OrbModWrap(const ObsSet& setObs);

		String ^ getVersion();
		_ObsSet ^SetObserv;

		static void Process(System ::String ^path);
		static bool loadKernels(System::String ^path);
		static bool loadObservatories(System::String ^path);
		static bool loadConfig(System::String ^path);

		static bool setIC(cli::array <String^, 1> ^, int IDC, int ICtype, int ICframe);
		static cli::array <String^, 1> ^ getIC( int IDC, int ICtype, int ICframe);

		static String^ getUsedObs();
	};

}
