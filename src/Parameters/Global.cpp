#include"stdafx.h"
#include"Global.h"
//
namespace OrbMod
{
	std::string		Global::FormCaption = "3.8";
	//
	ConstSpiceChar * Global::pictur_utc = "YYYY MM DD HR:MN:SC.####### ::UTC";
	ConstSpiceChar * Global::pictur_tdb = "YYYY MM DD HR:MN:SC.####### ::TDB";
	ConstSpiceChar * Global::pictur_tdt = "YYYY MM DD HR:MN:SC.####### ::TDT";
	//
	EarthFixFrame	Global::EFrame = EarthFixFrame::IAU_EARTH;
	char *			Global::EarthFrame = "IAU_EARTH";

	//Вид уравнений движения
	Variables		Global::Var = SODE_XV;
	TypeOfObs		Global::ObsT = Astro;

	//режим
	Mode			Global::mode = Mode::Propagation;
	//способ уточнения
	FitMode			Global::fitMode = FitMode::LS;
	//
	double			Global::ArcLength = 864000;
	int				Global::MinObsinBatch = 6;

	//
	long int		Global::start;
	FrameOfIC				Global::ICFrame;
	TimeFormat				Global::  Tscale;
	//тип начальных условий
	int				Global::i_IC = 1;
	bool			Global::IsUsePeriTime = false;
	//настройки интегрирования
	int				Global::NOR = 15;
	double			Global::eps = 1e-10;
	double			Global::t0 = 0;
	double			Global::te = 0;
	double			Global::step = 100;
	int				Global::Niter = 8;

	Matrix			Global::SV(6, 1);
	Matrix		    Global::SV_start(6, 1);
	Matrix			Global::Q;

	double			Global::Discr = 0;
	int				Global::prog = 0;
	bool			Global::IsAutoStep = false;

	//Центральное тело
	unsigned int	Global::IDC = 0;

	//его константы
	double			Global::mu = .0;
	double			Global::R[3] = { 0.0,0.0,0.0 };
	double			Global::f = .0;
	double			Global::Re = .0;
	double			Global::Rm = .0;
	double			Global::oz = .0;

	unsigned int	Global::ID1 = 0;
	unsigned int	Global::ID2 = 0;
	unsigned int	Global::ID3 = 0;
	unsigned int	Global::ID4 = 0;
	unsigned int	Global::ID5 = 0;
	//от планет
	bool			Global::b_10 = false;
	bool			Global::b_1 = false;
	bool			Global::b_2 = false;
	bool			Global::b_3 = false;
	bool			Global::b_4 = false;
	bool			Global::b_5 = false;
	bool			Global::b_6 = false;
	bool			Global::b_7 = false;
	bool			Global::b_8 = false;
	bool			Global::b_9 = false;
	//Доп. тела
	bool			Global::b_add1 = false;
	bool			Global::b_add2 = false;
	bool			Global::b_add3 = false;
	bool			Global::b_add4 = false;
	bool			Global::b_add5 = false;
	Cunningham		Global::GravField_add5;
	bool			Global::b_add5_cun_on = false;
	bool			Global::b_add5_tide_sun = false;
	bool			Global::b_add5_tide_body = false;
	int				Global::add5_tide_ID = 0;
	//релятивистские эффекты
	bool			Global::b_rel = false;
	bool			Global::b_rel_LT = false;
	// настройки вывода
	bool			Global::b_out_sv_J2000 = false;
	bool			Global::b_out_el_J2000 = false;

	bool			Global::cb_out_sv_ECLIPJ2000 = false;
	bool			Global::cb_out_el_ECLIPJ2000 = false;

	bool			Global::b_out_sv_IAUPlanet = false;

	bool			Global::b_out_BL = false;

	bool			Global::b_out_NEU = false;
	bool			Global::b_out_AZR = false;

	bool			Global::b_out_acc = false;
	//BFF(body fixed frame) 3-го тела
	bool			Global::b_3_BFF_sv = false;
	int				Global::ID_3_BFF_num = 399;
	// пертурбационная функция планеты
	bool			Global::b_Cunn = false;
	Cunningham		Global::GravField_CB;
	bool			Global::b_tide_CB_sun = false;
	bool			Global::b_tide_CB_body = false;
	int				Global::CB_tide_ID = 0;
	//световое давление:
	bool			Global::b_SRP = false;
	//сопротивление атмосферы
	bool			Global::b_atm = false;
	//для топоцентрической системы координат
	double			Global::Lat_topo;
	double			Global::Lon_topo;
	double			Global::H_topo;

	double			Global::R_topo[3] = { 0.0 };
	double			Global::M_topo[3][3] = { 0.0 };
	//Видимость
	bool			Global::b_visi = false;
	bool			Global::b_rot_with_3body = false;
	bool			Global::b_visi_rb = false;
	int				Global::i_fr = 0;
	int				Global::N_visi = 0;
	double		    Global::B_visi = 0.0;
	double			Global::L_visi = 0.0;
	double			Global::H_visi = 0.0;
	double			Global::R_visi[3] = { .0,.0,.0 };
	double			Global::M_visi[3][3] = { .0 };
	double			Global::oz_visi = .0;
	bool			Global::b_visi_pl = false;
	int				Global::ID_visi = 0;
	double			Global::R_pl = 0;
	//количество обращений к правым частям дифф. уравнений:
	long unsigned int Global::N_rp = 0;

	//colors
	int					Global::col_Main;
	int					Global::ColorsAcc[22];

	unsigned int		Global::ElapsedTime = 0;

}