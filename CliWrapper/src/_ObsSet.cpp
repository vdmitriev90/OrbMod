#include "_ObsSet.h"
#include "Marshaling.h"

#include "dateTime.h"
#include "Control.h"
#include "constant.h"
#include "Misc.h"
#include "Global.h"

#include"SpiceUsr.h"



using namespace OrbMod;
using namespace ZedGraph;
using namespace consts;
using namespace std;

typedef pair<string, vector<OrbMod::dateTime> > pobs;

namespace OrbModCLRWrapper
{
	//
	_ObsSet::_ObsSet()
	{
		setO = new ObsSet();
	}

	//
	_ObsSet::_ObsSet(const ObsSet &setObs)
	{
		this->setO = new ObsSet(setObs);
	}
	//
	
    _ObsSet^ _ObsSet::getObsSetFromOrbMod()
	{
		return gcnew _ObsSet(Control::Obs_);
	}
	//
	
    _ObsSet ::~_ObsSet()
	{
		delete setO;
	}

	//
	ObsSet _ObsSet::getIntObsSet()
	{
		return (*this->setO);
	}
	
    //
	void _ObsSet::reset()
	{
		this->setO->reset();
	}
	//
	
    bool _ObsSet::setTimeFrames(double et_0, double et_1)
	{
		return (this->setO->setTimeFrames(et_0, et_1));
	}
	
    //
	int _ObsSet::getObsNum()
	{
		return this->setO->getObsNum();
	}
	
    //
	bool _ObsSet::LoadObs(System::String ^ FileName, int ObsType)
	{
		return this->setO->LoadObs(Marsh::S2s(FileName), (TypeOfObs)ObsType);
	}
	//
	String ^ _ObsSet::TypeOfObserv()
	{
		if (this->setO->size() > 0)
		{
			return Marsh::s2S(setO->curr().getType());
		}
		else  return "";
	}
	//
	void _ObsSet::DataToForm(ZedGraph::GraphPane ^pane, System::Windows::Forms::DataGridView^  dgv_1)
	{
		Random ^ran = gcnew Random();

		OrbMod::dateTime dt;
		map<string, vector<OrbMod::dateTime> > dict;
		auto oi = dict.begin();

		for (auto it : ((*this->setO)))
		{
			double et = it->t;

			char ptr[100];
			et2utc_c(et, "ISOC", 5, 100, ptr);
			string s_utc = ptr;
			if (!Misc::tryPrcSpUTC(s_utc, dt)) continue;

			Observatory o = it->observ;
			string OCode = o.ID;
			oi = dict.begin();
			oi = dict.find(OCode);
			if (oi == dict.end())
			{
				vector<OrbMod::dateTime> vdt;
				vdt.push_back(dt);
				pobs p1(OCode, vdt);
				dict.insert(p1);
			}
			else
			{
				oi->second.push_back(dt);
			}
		}
		N = dict.size();

		cli::array <ZedGraph::PointPairList^, 1>^ ListObs = gcnew cli::array<ZedGraph::PointPairList^>(N);
		cli::array <ZedGraph::LineItem^, 1 >^  ListCurve = gcnew cli::array<ZedGraph::LineItem^>(N);
		cli::array <String^, 1> ^  AccNames = gcnew cli::array<String^>(N);

		int i = 0;
		for (auto it : dict)
		{
			ListObs[i] = gcnew ZedGraph::PointPairList();
			string sid = it.first;
			AccNames[i] = Marsh::s2S(Observatory::str2Obsy[sid].Name);

			for (auto it1 : it.second)
			{
				int msec = (it1.sec - (int)it1.sec) * 1000;
				XDate dt = XDate(it1.Y, it1.M, it1.D, it1.h, it1.min, (int)it1.sec, msec);
				ListObs[i]->Add(dt, i + 1);
			}

			// color 
			System::Drawing::Color colr = System::Drawing::Color::FromArgb(255, ran->Next(256), ran->Next(256), ran->Next(256));

			int  n = ListObs[i]->Count;

			OrbMod::dateTime dts = it.second[0];
			String ^dt1 = Marsh::s2S(dts.toString());
			dts = it.second[n - 1];
			String ^dt2 = Marsh::s2S(dts.toString());
			bool b = this->setO->isUseObs[sid];

			dgv_1->Rows->Add(i + 1, b, Marsh::s2S(sid), AccNames[i], n, dt1, dt2);
			dgv_1->Rows[i]->Cells[0]->Style->BackColor = colr;


			ListCurve[i] = pane->AddCurve(Marsh::s2S(sid), ListObs[i], colr, SymbolType::Square);
			ListCurve[i]->Symbol->Size = 7;
			ListCurve[i]->Symbol->Fill->Type = FillType::None;
			ListCurve[i]->Line->IsVisible = false;
			ListCurve[i]->Line->Width = 1;

			i++;
		}
	}
	//
	void _ObsSet::ChangeTimeFrame(GraphPane ^pane, System::Windows::Forms::DataGridView^  dgv_1, String ^% t_start, String ^% t_finish, double % t0, double % te)
	{
		//Обсерватории наблюдения которых будут использованы
		for (int i = 0; i < N; i++)
		{
			String ^ s = Convert::ToString(dgv_1->Rows[i]->Cells[2]->Value);
			bool b = Convert::ToBoolean(dgv_1->Rows[i]->Cells[1]->Value);
			string id = Marsh::S2s(s);
			this->setO->isUseObs[id] = b;
		}

		XDate dt0 = pane->XAxis->Scale->Min;
		XDate dte = pane->XAxis->Scale->Max;

		OrbMod::dateTime t_0(dt0.DateTime.Year, dt0.DateTime.Month, dt0.DateTime.Day, dt0.DateTime.Hour, dt0.DateTime.Minute, dt0.DateTime.Second, dt0.DateTime.Millisecond);
		OrbMod::dateTime t_e(dte.DateTime.Year, dte.DateTime.Month, dte.DateTime.Day, dte.DateTime.Hour, dte.DateTime.Minute, dte.DateTime.Second, dte.DateTime.Millisecond);


		//Интервал времени наблюдения на котором будут использованы
		string st0 = t_0.toString();
		string st1 = t_e.toString();
		const char *TDB_start = st0.c_str();
		const char *TDB_finish = st1.c_str();

		double et0, et1;
		str2et_c(TDB_start, &et0);
		str2et_c(TDB_finish, &et1);
		char t_first[70], t_last[70];
		this->setO->setTimeFrames(et0, et1);
		t0 = et0; te = et1;
		timout_c(this->setO->curr().t, Global::pictur_tdb, 70, t_first);
		timout_c(this->setO->last().t, Global::pictur_tdb, 70, t_last);

		t_start = Marsh::s2S(t_first);
		t_finish = Marsh::s2S(t_last);

	}

	void _ObsSet::SetUseObs(String ^ID, bool use)
	{
		string id = Marsh::S2s(ID);
		this->setO->isUseObs[id] = use;
	}

	void _ObsSet::SetObservationToCore()
	{
		Control::Obs_  =  *this->setO;
	}

	String^ _ObsSet::UsedObs2String()
	{
		std::string str = "";
		for (auto it : (*this->setO).isUseObs)
			str += it.first + ',' + to_string((int)it.second) + ';';
		return Marsh::s2S(str);
	}
}