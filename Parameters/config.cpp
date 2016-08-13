#include "stdafx.h"
#include "config.h"
#include <exception>

namespace OrbMod
{
#pragma region constructors
	config::config()
	{
	}
	config::~config()
	{
	}
#pragma endregion

#pragma region буферные переменные
	double		config::SV[6];
	std::string	config::s_t0;
	std::string	config::s_te;
	std::string	config::s_fileCBHarm;
	std::string	config::s_fileAddHarm;

	double		config::SRP_albedo;
	double		config::SRP_S;
	double		config::SRP_Mass;

#pragma endregion

	formatters config::formatDict
	{
		IsTestMode,
		FittingMode,
		Obs,
		MinObsInbatch,
		ArcLength,
		NmNr,
		CB,
		Int,
		Var,
		NOR,
		 Step,
		 Eps,
		 orbFitEps,
		IsAutoStep ,
		Niter,
		orbFitNiter,
		orbFitNiterPerBatch,
		orbFitRejOuts,
		 T_start ,
		 T_end ,
		 Frame,
		 EarthFixedFrame,
		 Time_scale,
		 TypeIC,
		 UsePeriTime,
		 IC,
		BigPlanets,
		AddBodies,
		AddBody5HT,
		CBHterms,
		Rel,
		SRP,
		Discr,
		Out,
		BFFID,
		Colors,
		useObs,
		ObsTimeFrame,
		ObservationsPath,
		 IsLogResiduals,
		 aprioriRMS,
		 processNoise
	};

	parce_dict config::parceDict
	{
		{ "Mode", IsTestMode },
		{ "FittingMode", FittingMode },
		{ "Obs", Obs },
		{ "MinObsInbatch", MinObsInbatch },
		{ "ArcLength", ArcLength },
		{ "NmNr", NmNr },
		{ "IDC", CB },
		{ "Integrator", Int },
		{ "Variables", Var },
		{ "NOR", NOR },
		{ "Step", step },
		{ "Eps", eps},
		{ "OrbFitEps", orbFitEps },
		{ "IsAutoStep", Autostep },
		{ "Niter", Niter },
		{ "OrbFitNiter", orbFitNiter },
		{ "orbFitNiterPerBatch", orbFitNiterPerBatch },
		{ "orbFitRejOuts", orbFitRejOuts },
		{ "T_start", t0 },
		{ "T_end", te },
		{ "Frame", frame },
		{ "EarthFixedFrame", EarthFixedFrame },
		{ "Time_scale", tscale },
		{ "Type_of_IC", TypeIC },
		{ "UsePeriTime",UsePeriTime },
		{ "IC", IC },
		{ "PerturbationsByPlanets", BigPlanets },
		{ "PerturbationsBySpecificBodies", AddBodies },
		{ "AddBody5HT", AddBody5HT },
		{ "CBHterms", CBHterms },
		{ "Rel", Rel },
		{ "SRP", SRP },
		{ "Discr", Discr },
		{ "Out", Out },
		{ "BFFID", BFFID },
		{ "Colors", Colors },
		{ "useObservatoris", useObs },
		{ "ObsTimeFrame", ObsTimeFrame },
		{ "ObservationsPath", ObservationsPath },

		{ "IsLogResiduals", IsLogResiduals },
		{ "aprioriRMS", aprioriRMS },
		{ "processNoise", processNoise }
	};

#pragma region parcers
	bool config::NmNr(string s)
	{
		//Global::NameNr = (NameOrNumber)stoi(s);
		return true;
	}
	//
	bool config::IsTestMode(string s)
	{
		Global::mode = (Mode)stoi(s);
		return true;
	}
	//
	bool config::FittingMode(string s)
	{
		Global::fitMode = (FitMode)stoi(s);
		return true;
	}
	//
	bool config::Obs(string s)
	{
		Global::ObsT = (TypeOfObs)stoi(s);
		return true;
	}
	//
	bool config::ArcLength(string s)
	{
		Global::ArcLength = stod(s);
		return true;
	}
	//
	bool config::MinObsInbatch(string s)
	{
		Global::MinObsinBatch = stoi(s);
		return true;
	}
	//
	bool config::CB(string s)
	{
		Global::IDC = stoi(s);
		return true;
	}
	//
	bool config::Int(string s)
	{
		//Global:: = stoi(s);
		return true;
	}
	bool config::Var(string s)
	{
		Global::Var = (Variables)stoi(s);
		return true;
	}
	//
	bool config::NOR(string s)
	{
		Global::NOR = stoi(s);
		return true;
	}
	//
	bool config::step(string s)
	{
		Global::step = stof(s);
		return true;
	}
	//
	bool config::eps(string s)
	{
		Global::eps = pow(10, -stof(s));
		return true;
	}
	//
	bool config::orbFitEps(string s)
	{
		OrbFit::epsIter = pow(10, -stof(s));
		return true;
	}
	//
	bool config::Autostep(string s)
	{
		Global::IsAutoStep = stoi(s);
		return true;
	}
	//
	bool config::Niter(string s)
	{
		Global::Niter = stoi(s);
		return true;
	}
	//
	bool config::orbFitNiter(string s)
	{
		OrbFit::maxIter = stoi(s);
		return true;
	}
	//
	bool config::orbFitNiterPerBatch(string s)
	{
		OrbFit::maxIterPerBatch = stoi(s);
		return true;
	}
	//
	bool config::orbFitRejOuts(string s)
	{
		vector<string> strs = Misc::splitStr(s, ';');
		if (strs.size() < 2) return false;
		OrbFit::isRejOuts = stoi(strs[0]);
		OrbFit::OutlsThresh = stof(strs[1]);
		return true;
	}
	//
	bool config::t0(string s)
	{
		s_t0 = s;
		return true;
	}
	//
	bool config::te(string s)
	{
		s_te = s;
		return true;
	}
	//
	bool config::frame(string s)
	{
		Global::ICFrame = (FrameOfIC)stoi(s);
		return true;
	}
	//
	bool config::EarthFixedFrame(string s)
	{
		Global::EFrame = (EarthFixFrame)stoi(s);
		try
		{
			Global::EarthFrame = EarthFixedFrame_strs[(int)Global::EFrame];
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	//
	bool config::tscale(string s)
	{
		Global::Tscale = (TimeFormat)stoi(s);
		return true;
	}
	//
	bool config::TypeIC(string s)
	{
		Global::i_IC = stoi(s);

		return true;
	}
	bool config::UsePeriTime(string s)
	{
		Global::IsUsePeriTime = (bool)stoi(s);
		return true;
	}
	bool config::IC(string s)
	{
		vector<string> strs = Misc::splitStr(s, ';');
		if (strs.size() < 6) return false;
		for (int i = 0; i < 6; i++) Global::SV(i,0) =  config::SV[i] = stod(strs[i]);
		return true;
	}
	bool config::BigPlanets(string s)
	{
		vector<string> strs = Misc::splitStr(s, ';');
		if (strs.size() < 10) return false;
		Global::b_1 = (bool)stoi(strs[0]);
		Global::b_2 = (bool)stoi(strs[1]);
		Global::b_3 = (bool)stoi(strs[2]);
		Global::b_4 = (bool)stoi(strs[3]);
		Global::b_5 = (bool)stoi(strs[4]);
		Global::b_6 = (bool)stoi(strs[5]);
		Global::b_7 = (bool)stoi(strs[6]);
		Global::b_8 = (bool)stoi(strs[7]);
		Global::b_9 = (bool)stoi(strs[8]);
		Global::b_10 = (bool)stoi(strs[9]);
		return true;
	}
	bool config::AddBodies(string s)
	{
		vector<string> strs = Misc::splitStr(s, ';');
		if (strs.size() < 10) return false;

		Global::ID1 = stoi(strs[0]);
		Global::b_add1 = (bool)stoi(strs[1]);

		Global::ID2 = stoi(strs[2]);
		Global::b_add2 = (bool)stoi(strs[3]);

		Global::ID3 = stoi(strs[4]);
		Global::b_add3 = (bool)stoi(strs[5]);

		Global::ID4 = stoi(strs[6]);
		Global::b_add4 = (bool)stoi(strs[7]);

		Global::ID5 = stoi(strs[8]);
		Global::b_add5 = (bool)stoi(strs[9]);

		return true;
	}
	//
	bool config::AddBody5HT(string s)
	{
		vector<string> strs = Misc::splitStr(s, ';');
		if (strs.size() < 3) return false;
		Global::b_add5_cun_on = (bool)stoi(strs[0]);
		Global::GravField_add5.set_Ngf(stoi(strs[1]));
		Global::GravField_add5.FileModel = strs[2];
		return true;
	}
	//
	bool config::CBHterms(string s)
	{
		vector<string> strs = Misc::splitStr(s, ';');
		if (strs.size() < 3) return false;
		Global::b_Cunn = (bool)stoi(strs[0]);
		Global::GravField_CB.set_Ngf(stoi(strs[1]));
		Global::GravField_CB.FileModel = strs[2];

		return true;
	}
	bool config::Rel(string s)
	{
		vector<string> strs = Misc::splitStr(s, ';');
		if (strs.size() < 2) return false;
		Global::b_rel = (bool)stoi(strs[0]);
		Global::b_rel_LT = (bool)stoi(strs[1]);

		return true;
	}
	bool config::SRP(string s)
	{
		vector<string> strs = Misc::splitStr(s, ';');
		if (strs.size() < 4) return false;
		Global::b_SRP = (bool)stoi(strs[0]);
		config::SRP_albedo = stod(strs[1]);
		config::SRP_S = stod(strs[2]);
		config::SRP_Mass = stod(strs[3]);

		return true;
	}
	bool config::Discr(string s)
	{
		Global::Discr = stod(s);
		return true;
	}
	bool config::Out(string s)
	{
		vector<string> strs = Misc::splitStr(s, ';');
		if (strs.size() < 8) return false;

		Global::b_out_sv_J2000 = (bool)stoi(strs[0]);
		Global::b_out_el_J2000 = (bool)stoi(strs[1]);
		Global::cb_out_sv_ECLIPJ2000 = (bool)stoi(strs[2]);
		Global::cb_out_el_ECLIPJ2000 = (bool)stoi(strs[3]);
		Global::b_out_sv_IAUPlanet = (bool)stoi(strs[4]);
		Global::b_out_acc = (bool)stoi(strs[5]);
		Global::b_out_BL = (bool)stoi(strs[6]);
		Global::b_3_BFF_sv = (bool)stoi(strs[7]);
		return true;
	}
	//
	bool config::BFFID(string s)
	{
		Global::ID_3_BFF_num = stod(s);
		return true;
	}
	bool config::Colors(string s)
	{
		vector<string> strs = Misc::splitStr(s, ';');
		if (strs.size() < 23) return false;

		Global::col_Main = stoi(strs[0]);
		for (int i = 0; i < 22; i++)
			Global::ColorsAcc[i] = stoi(strs[i + 1]);

		return true;
	}
	bool config::useObs(string s)
	{
		try
		{
			vector<string> strs = Misc::splitStr(s, ';');
			for (auto it : strs)
			{
				if (it.size() < 5) return false;
				string key = it.substr(0, 3);
				int val = stoi(it.substr(4, 1));
				if (!Control::Inst.Obs_->tryAddObs(key, val))
					Control::Inst.Obs_->isUseObs[key] = val;
			}
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	//
    bool config ::ObsTimeFrame( string s)
	{
		vector<string> strs = Misc::splitStr(s, ';');
		if (strs.size() < 2) return false;
		
		Control::Inst.Obs_->t0 = stod(strs[0]);
		Control::Inst.Obs_->te = stod(strs[1]);
		return true;
	}
	//
	bool config::ObservationsPath(string s)
	{
		Control::Inst.Obs_->path = s;
		return true;
	}
	//
	bool config::IsLogResiduals(string s)
	{
		ObsSet::isLogResid = stoi(s);
		return true;
	}
	bool config::aprioriRMS(string s)
	{
		vector<string> strs = Misc::splitStr(s, ';');
		if (strs.size() < 3) return false;
		Control::Inst.Obs_->sigma = stod(strs[0]);
		OrbFit::PosRMS = stod(strs[1]);
		OrbFit::VelRMS = stod(strs[2]);

		return true;
	}
	//
	bool config::processNoise(string s)
	{
		OrbFit::Qnoise = stod(s);
		return true;
	}
#pragma endregion

#pragma region formatters
	std::string config::NmNr()
	{
		std::string str = " ";
		//str += to_string((int)Global::NameNr);
		return str;
	}
	//
	std::string config::IsTestMode()
	{
		std::string str = "Mode:";
		str += to_string((int)Global::mode);
		return str;
	}
	std::string config::FittingMode()
	{
		std::string str = "FittingMode:";
		str += to_string((int)Global::fitMode);
		return str;
	}
	//
	std::string config::Obs()
	{
		std::string str = "Obs:";
		str += to_string((int)Global::ObsT);
		return str;
	}
	//
	std::string config::MinObsInbatch()
	{
		std::string str = "MinObsInbatch:";
		str += to_string(Global::MinObsinBatch);
		return str;
	}
	//
	std::string config::ArcLength()
	{
		std::string str = "ArcLength:";
		str += to_string(Global::ArcLength);
		return str;
	}
	//
	std::string config::CB()
	{
		std::string str = "IDC:";
		str += to_string(Global::IDC);
		return str;
	}
	//
	std::string config::Int()
	{
		return "Integrator:0";
	}
	//
	std::string config::Var()
	{
		std::string str = "Variables:";
		str += to_string(Global::Var);
		return str;
	}
	std::string config::NOR()
	{
		std::string str = "NOR:";
		str += to_string(Global::NOR);
		return str;
	}
	std::string config::Step()
	{
		std::string str = "Step:";
		char buf[50];
		std::sprintf(buf, "%29.19f", Global::step);
		str += buf;
		return str;
	}
	std::string config::Eps()
	{
		std::string str = "Eps:";
		str += to_string(abs(log10(Global::eps)));
		return str;
	}
	std::string config::orbFitEps()
	{
		std::string str = "OrbFitEps:";
		str += to_string(abs(log10(OrbFit::epsIter)));
		return str;
	}
	std::string config::IsAutoStep()
	{
		std::string str = "IsAutoStep:";
		str += to_string((int)Global::IsAutoStep);
		return str;
	}
	//
	std::string config::Niter()
	{
		std::string str = "Niter:";
		str += to_string(Global::Niter);
		return str;
	}
	//
	std::string config::orbFitNiter()
	{
		std::string str = "OrbFitNiter:";
		str += to_string(OrbFit::maxIter);
		return str;
	}
	//
	std::string  config::orbFitNiterPerBatch()
	{
		std::string str = "orbFitNiterPerBatch:";
		str += to_string(OrbFit::maxIterPerBatch);

		return str;
	}
	//
	std::string  config::orbFitRejOuts()
	{
		std::string str = "orbFitRejOuts:";
		str += to_string((int)OrbFit::isRejOuts) + ";";
		str += to_string(OrbFit::OutlsThresh);

		return str;
	}
	std::string config::T_start()
	{
		std::string str = "T_start:";
		str += config::s_t0;
		return str;
	}
	std::string config::T_end()
	{
		std::string str = "T_end:";
		str += config::s_te;
		return str;
	}
	//
	std::string config::Frame()
	{
		std::string str = "Frame:";
		str += to_string((int)Global::ICFrame);
		return str;
	}
	//
	std::string config::EarthFixedFrame()
	{
		std::string str = "EarthFixedFrame:";
		str += to_string((int)Global::EFrame);
		return str;
	}
	//
	std::string config::Time_scale()
	{
		std::string str = "Time_scale:";
		str += to_string((int)Global::Tscale);
		return str;
	}
	std::string config::TypeIC()
	{
		std::string str = "Type_of_IC:";
		str += to_string(Global::i_IC);
		return str;
	}
	std::string config::UsePeriTime()
	{
		std::string str = "UsePeriTime:";
		str += to_string((int)Global::IsUsePeriTime);
		return str;
	}
	std::string config::IC()
	{
		std::string str = "IC:";
		for (int i = 0; i < 6; i++)
		{
			char buf[50];
			std::sprintf(buf, "%29.16f", config::SV[i]);
			str += buf;
			str += ';';
		}
		return str;
	}
	std::string config::BigPlanets()
	{
		std::string str = "PerturbationsByPlanets:";
		str += to_string((int)Global::b_1) + ";";
		str += to_string((int)Global::b_2) + ";";
		str += to_string((int)Global::b_3) + ";";
		str += to_string((int)Global::b_4) + ";";
		str += to_string((int)Global::b_5) + ";";
		str += to_string((int)Global::b_6) + ";";
		str += to_string((int)Global::b_7) + ";";
		str += to_string((int)Global::b_8) + ";";
		str += to_string((int)Global::b_9) + ";";
		str += to_string((int)Global::b_10) + ";";

		return str;
	}
	//
	std::string config::AddBodies()
	{
		std::string str = "PerturbationsBySpecificBodies:";
		str += to_string(Global::ID1) + ";" + to_string((bool)Global::b_add1) + ";";
		str += to_string(Global::ID2) + ";" + to_string((bool)Global::b_add2) + ";";
		str += to_string(Global::ID3) + ";" + to_string((bool)Global::b_add3) + ";";
		str += to_string(Global::ID4) + ";" + to_string((bool)Global::b_add4) + ";";
		str += to_string(Global::ID5) + ";" + to_string((bool)Global::b_add5) + ";";

		return str;
	}
	//
	std::string config::CBHterms()
	{
		std::string str = "CBHterms:";
		str += to_string(Global::b_Cunn) + ";" + to_string(Global::GravField_CB.get_Ngf()) + ';' + Global::GravField_CB.FileModel;

		return str;
	}
	//
	std::string config::AddBody5HT()
	{
		std::string str = "AddBody5HT:";
		str += to_string(Global::b_add5_cun_on) + ";" + to_string(Global::GravField_add5.get_Ngf()) + ';' + Global::GravField_add5.FileModel;
		return str;
	}
	//
	std::string config::Rel()
	{
		std::string str = "Rel:";
		str += to_string((int)Global::b_rel) + ";" + to_string(Global::b_rel_LT);

		return str;
	}
	//
	std::string config::SRP()
	{
		std::string str = "SRP:";
		str += to_string((int)Global::b_SRP) + ';' + to_string(config::SRP_albedo) + ';';
		str += to_string((int)config::SRP_S) + ';' + to_string((int)config::SRP_Mass);

		return str;
	}
	//
	std::string config::Discr()
	{
		std::string str = "Discr:";
		str += to_string(Global::Discr);

		return str;
	}
	//
	std::string config::Out()
	{
		std::string str = "Out:";
		str += to_string((int)Global::b_out_sv_J2000) + ";";
		str += to_string((int)Global::b_out_el_J2000) + ";";
		str += to_string((int)Global::cb_out_sv_ECLIPJ2000) + ";";
		str += to_string((int)Global::cb_out_el_ECLIPJ2000) + ";";
		str += to_string((int)Global::b_out_sv_IAUPlanet) + ";";
		str += to_string((int)Global::b_out_acc) + ";";
		str += to_string((int)Global::b_out_BL) + ";";
		str += to_string((int)Global::b_3_BFF_sv) + ";";

		return str;
	}
	//
	std::string config::BFFID()
	{
		std::string str = "BFFID:";
		str += to_string(Global::ID_3_BFF_num);
		return str;
	}
	//
	std::string config::Colors()
	{
		std::string str = "Colors:";
		str += to_string(Global::col_Main) + ';';
		for (int i = 0; i < 22; i++)
			str += to_string(Global::ColorsAcc[i]) + ';';
		return str;
	}
	//
	std::string config::useObs()
	{
		std::string str = "useObservatoris:";
		for (auto it : Control::Inst.Obs_->isUseObs)
			str += it.first + ',' + to_string((int)it.second) + ';';

		return str;
	}
	//
	std::string config::ObsTimeFrame()
	{
		std::string str = "ObsTimeFrame:";
		char buf[25];

		sprintf(buf, "%20.5f", Control::Inst.Obs_->t0 );
		str += buf; str +=";";

		sprintf(buf, "%20.5f", Control::Inst.Obs_->te);
		str += buf; str += ";";
		return str;
	}
	//
	std::string config::ObservationsPath()
	{
		std::string str = "ObservationsPath:";
		str += Control::Inst.Obs_->path;
		return str;
	}

	//
	std::string config::IsLogResiduals()
	{
		std::string str = "IsLogResiduals:";
		str += to_string((int)ObsSet::isLogResid);
		return str;
	}
	//
	std::string config::aprioriRMS()
	{
		std::string str = "aprioriRMS:";
		char buf[50];

		std::sprintf(buf, "%12.8e;", Control::Inst.Obs_->sigma);
		str += buf;
		std::sprintf(buf, "%12.8e;", OrbFit::PosRMS);
		str += buf;
		std::sprintf(buf, "%12.8e;", OrbFit::VelRMS);
		str += buf;
		return str;
	}
	//
	std::string config::processNoise()
	{
		std::string str = "processNoise:";
		char buf[50];
		std::sprintf(buf, "%12.8e", OrbFit::Qnoise);
		str += buf;
		return str;
	}
#pragma endregion
	//преобразование начальных условий во внутренний формат
	bool  config::SetIC(std::string IC_[], int IDC, TypeOfIC ICtype, FrameOfIC ICframe)
	{
		double   mu;
		double elts[8];
		for (int i = 0; i < 5; i++)
			elts[i] = stod(IC_[i]);

			mu = ID2GM(Global::IDC);

		if (ICtype == TypeOfIC::OrbitalElements)
		{
			double sma = elts[0];
			elts[0] = sma*(1.0 - elts[1]);
			elts[2] = elts[2] / rad;
			elts[3] = elts[3] / rad;
			elts[4] = elts[4] / rad;

			elts[6] = 0.0;
			elts[7] = mu;

			if (Global::IsUsePeriTime)
			{
				//mean motion
				double n = sqrt(mu / (sma*sma*sma));
				double et_peri = 0;
				if (!Misc::parceTime(IC_[5],Global::Tscale, et_peri)) return false;
				elts[5] = n*(Global::t0 - et_peri);

				conics_c(elts, 0, config::SV);
			}
			else
			{
				elts[5] = stod(IC_[5]) / rad;
				conics_c(elts, 0, config::SV);
			}
		}
		else if (ICtype == TypeOfIC::StateVector)
		{
			for (int i = 0; i < 5; i++)
				config::SV[i] = elts[i];
			config::SV[5] = stod(IC_[5]);
		}

		if (ICframe == FrameOfIC::Ecliptic_and_Equinox_J2000)
		{
			double matr[6][6];

			sxform_c("ECLIPJ2000", "J2000", 0, matr);
			mxvg_c(matr, config::SV, 6, 6, config::SV);
		}
		return true;
	}
	//
	//преобразование начальных условий из внутреннего формата
	bool config::GetIC(std::string *IC, int IDC, TypeOfIC ICtype, FrameOfIC ICframe)
	{
		double IC_[8], mu;
		char buf[70];
		double SV_tr[6];
		for (int i = 0; i < 6; i++)
			SV_tr[i] = config::SV[i];

		mu = ID2GM(IDC);

		if (ICframe == FrameOfIC::Ecliptic_and_Equinox_J2000)
		{
			double matr[6][6];

			sxform_c("J2000", "ECLIPJ2000", 0, matr);
			mxvg_c(matr, config::SV, 6, 6, SV_tr);
		}

		if (ICtype == TypeOfIC::OrbitalElements)
		{
			oscelt_c(SV_tr, 0, mu, IC_);
			double sma = IC_[0] / (1.0 - IC_[1]);
			IC_[0] = sma;
			for (int i = 0; i < 5; i++)
			{
				double val = IC_[i];
				if (i > 1) val = val * rad;
				sprintf(buf, "%20.13f", val);
				IC[i] = buf;
			}
			if (Global::IsUsePeriTime)
			{
				//mean motion
				double n = sqrt(mu / (sma*sma*sma));
				double et_peri = 0;
				double tp = Global::t0 - IC_[5] / n;
				string s_tp;
				Misc::et2cal(tp, Global::Tscale, s_tp);
				IC[5] = s_tp;
			}
			else
			{
				sprintf(buf, "%20.13f", IC_[5] * rad);
				IC[5] = buf;
			}
		}
		else
		{
			for (int i = 0; i < 6; i++)
			{
				sprintf(buf, "%20.13f", SV_tr[i]);
				IC[i] = buf;
			}

		}
		return true;
	}
	//
	bool config::LoadCFG(string fileName)
	{
		ifstream file(fileName);
		if (file.is_open())
		{
			while (!file.eof())
			{
				std::string line;
				getline(file, line);
				vector<string> _v = Misc::splitStr2(line, ':');
				if (_v.size() < 2) continue;
				parce_dict::iterator it = parceDict.find(_v[0]);
				if (it != parceDict.end())
					(*it).second(_v[1]);
			}
			file.close();
			return true;
		}
		else return false;
	}
	//
	bool config::SaveCFG(string fileName)
	{
		ofstream file(fileName);
		if (file.is_open())
		{
			try
			{
				for (auto it : formatDict)
				{
					file << (*it)() << endl;
				}
				file.close();
			}
			catch (std::exception &e)
			{
				file.close();
				throw e;
			}
			return true;
		}
		else return false;

		return true;
	}
}
