#pragma once
#include"ObsSet.h"
using namespace System;
using namespace OrbMod;


namespace OrbModCLRWrapper {


	public ref class _ObsSet : System::IDisposable
	{
	public:

		_ObsSet();
		_ObsSet(const ObsSet & setObs);
		~_ObsSet();

		//public fields
		int N;

		//methods
		ObsSet getIntObsSet();
		static _ObsSet^ getObsSetFromOrbMod();
		bool LoadObs(System::String ^path, int ObsType);
		void reset();
		bool setTimeFrames(double et_0, double et_1);
		int getObsNum();
		String ^ TypeOfObserv();
		void DataToForm(ZedGraph::GraphPane ^pane, System::Windows::Forms::DataGridView^  dgv_1);
		void ChangeTimeFrame(ZedGraph::GraphPane ^pane, System::Windows::Forms::DataGridView^  dgv_1, String ^% t_start, String ^% t_finish, double % t0, double % te);
		void SetUseObs(String ^ID, bool use);
		void SetObservationToCore();
		String^ UsedObs2String();
	private:
		ObsSet *setO;

	};
}

