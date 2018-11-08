#include "constant.h"

#include"Global.h"
#include"SpiceUsr.h"

using namespace OrbMod;

namespace consts
{

	double ID2GM(int ID)
	{
		double mu;
		switch (ID)
		{
		case 1: mu = BODY1_GM;
			break;
		case 2: mu = BODY2_GM;
			break;
		case 3: mu = BODY3_GM;
			break;
		case 4: mu = BODY4_GM;
			break;
		case 5: mu = BODY5_GM;
			break;
		case 6: mu = BODY6_GM;
			break;
		case 7: mu = BODY7_GM;
			break;
		case 8: mu = BODY8_GM;
			break;
		case 9: mu = BODY9_GM;
			break;
			//////////////////////////////////////////////////////
		case 199: mu = BODY199_GM;
			break;
			////////////////////////////////////////////////////
		case 299: mu = BODY299_GM;
			break;
			///////////////////////////////////////////////////
		case 399: mu = BODY399_GM;
			break;
		case 301: mu = BODY301_GM;
			break;
			///////////////////////////////////////////////////
		case 499: mu = BODY499_GM;
			break;
		case 401: mu = BODY401_GM;
			break;
		case 402: mu = BODY402_GM;
			break;
			//////////////////////////////////////////////////
		case 599: mu = BODY599_GM;
			break;
		case 501: mu = BODY501_GM;
			break;
		case 502: mu = BODY502_GM;
			break;
		case 503: mu = BODY503_GM;
			break;
		case 504: mu = BODY504_GM;
			break;
		case 505: mu = BODY505_GM;
			break;
		case 506: mu = BODY506_GM;
			break;
		case 507: mu = BODY507_GM;
			break;
		case 508: mu = BODY508_GM;
			break;
		case 509: mu = BODY509_GM;
			break;
		case 510: mu = BODY510_GM;
			break;
		case 511: mu = BODY511_GM;
			break;
		case 512: mu = BODY512_GM;
			break;
		case 513: mu = BODY513_GM;
			break;
		case 514: mu = BODY514_GM;
			break;
		case 515: mu = BODY515_GM;
			break;
		case 516: mu = BODY516_GM;
			break;

			////////////////////////////////////////////////
		case 699: mu = BODY699_GM;
			break;
		case 601: mu = BODY601_GM;
			break;
		case 602: mu = BODY602_GM;
			break;
		case 603: mu = BODY603_GM;
			break;
		case 604: mu = BODY604_GM;
			break;
		case 605: mu = BODY605_GM;
			break;
		case 606: mu = BODY606_GM;
			break;
		case 607: mu = BODY607_GM;
			break;
		case 608: mu = BODY608_GM;
			break;
		case 609: mu = BODY609_GM;
			break;
		case 610: mu = BODY610_GM;
			break;
		case 611: mu = BODY611_GM;
			break;
		case 612: mu = BODY612_GM;
			break;
		case 613: mu = BODY613_GM;
			break;
		case 614: mu = BODY614_GM;
			break;
		case 615: mu = BODY615_GM;
			break;
		case 616: mu = BODY616_GM;
			break;
		case 617: mu = BODY617_GM;
			break;
		case 618: mu = BODY618_GM;
			break;

			////////////////////////////////////////////////
		case 799: mu = BODY799_GM;
			break;
		case 701: mu = BODY701_GM;
			break;
		case 702: mu = BODY702_GM;
			break;
		case 703: mu = BODY703_GM;
			break;
		case 704: mu = BODY704_GM;
			break;
		case 705: mu = BODY705_GM;
			break;
		case 706: mu = BODY706_GM;
			break;
		case 707: mu = BODY707_GM;
			break;
		case 708: mu = BODY708_GM;
			break;
		case 709: mu = BODY709_GM;
			break;
		case 710: mu = BODY710_GM;
			break;
		case 711: mu = BODY711_GM;
			break;
		case 712: mu = BODY712_GM;
			break;
		case 713: mu = BODY713_GM;
			break;
		case 714: mu = BODY714_GM;
			break;
		case 715: mu = BODY715_GM;
			break;
			///////////////////////////////////////////////
		case 899: mu = BODY899_GM;
			break;
		case 801: mu = BODY801_GM;
			break;
		case 802: mu = BODY802_GM;
			break;
		case 803: mu = BODY803_GM;
			break;
		case 804: mu = BODY804_GM;
			break;
		case 805: mu = BODY805_GM;
			break;
		case 806: mu = BODY806_GM;
			break;
		case 807: mu = BODY807_GM;
			break;
		case 808: mu = BODY808_GM;
			break;
			//////////////////////////////////////////////
		case 999: mu = BODY999_GM;
			break;
		case 901: mu = BODY901_GM;
			break;
			/////////////////////////////////////////////
		case 10: mu = BODY10_GM;
			break;
			//asteroids
		case 2000001: mu = BODY2000001_GM;
			break;
		case 2000002: mu = BODY2000002_GM;
			break;
		case 2000004: mu = BODY2000004_GM;
			break;

		default:
			;
		}
		return(mu);
	};
	long int id2fixfr(long int ID)
	{
		long int numF;
		switch (ID)
		{
			//инерциальные
		case 1: numF = 1;	//J2000
			break;
		case 2: numF = 2;	//B1950
			break;
		case 3: numF = 3;	//FK4
			break;
		case 13: numF = 13;	//galactic
			break;
		case 17: numF = 17;	//ecliptic J2000
			break;
		case 20002: numF = 20002;	//средняя экваториальная геоцентрическая неинерциальная
			break;
		case 20004: numF = 20004;	//истинная экваториальная геоцентрическая неинерциальная
			break;
		case 20006: numF = 20006;	//истинная эклиптическая геоцентрическая неинерциальная
			break;
		case 199: numF = 10011;
			break;
		case 299: numF = 10012;
			break;
		case 399: numF = 10013;
			break;
		case 301: numF = 10020;
			break;
			//	Марс
		case 499: numF = 10014;
			break;
		case 401: numF = 10021;
			break;
		case 402: numF = 10022;
			break;
			//	Юпитер
		case 599: numF = 10015;
			break;
		case 501: numF = 10023;
			break;
		case 502: numF = 10024;
			break;
		case 503: numF = 10025;
			break;
		case 504: numF = 10026;
			break;
			//	Сатурн
		case 699: numF = 10016;
			break;
		case 601: numF = 10039;
			break;
		case 602: numF = 10040;
			break;
		case 603: numF = 10041;
			break;
		case 604: numF = 10042;
			break;
		case 605: numF = 10043;
			break;
		case 606: numF = 10044;
			break;
		case 608: numF = 10046;
			break;
			//	Уран
		case 799: numF = 10017;
			break;
		case 701: numF = 10056;
			break;
		case 702: numF = 10057;
			break;
		case 703: numF = 10058;
			break;
		case 704: numF = 10059;
			break;
		case 705: numF = 10060;
			break;
			//	Нептун
		case 899: numF = 10018;
			break;
		case 801: numF = 10071;
			break;
		case 802: numF = 10072;
			break;
		case 808: numF = 10078;
			break;
			//	Плутон
		case 999: numF = 10019;
			break;
		case 901: numF = 10079;
			break;
			// Солнце
		case 10:  numF = 10010;
			break;

		default:
			;
		}
		return(numF);
	};

	//System::String^ id2name(int ID){
	//	System::String^ name;
	//	switch (ID)
	//	{
	//	case 1: name="Mercury";	
	//		break;
	//	case 2:name="Venus";	
	//		break;
	//	case 3: name="Earth-Moon barycenter";	
	//		break;
	//	case 4: name="Mars barycenter";	
	//		break;
	//	case 5: name="Jupiter barycenter";	
	//		break;
	//	case 6: name="Saturn barycenter";	
	//		break;
	//	case 7: name="Uranus barycenter";	
	//		break;
	//	case 8: name="Neptune barycenter";	
	//		break;
	//	case 9: name="Pluto barycenter";	
	//		break;
	//	case 10: name="Sun";	
	//		break;
	//	case 199: name="Mercury";	
	//		break;
	//	case 299: name="Venus";	
	//		break;
	////---------------------------------------------------
	//	case 399: name="Earth";	
	//		break;
	//	case 301: name="Moon";	
	//		break;
	////---------------------------------------------------
	//	case 499: name="Mars";	
	//		break;
	//	case 401: name = "Phobos";
	//		break;
	//	case 402: name = "Deimos";
	//		break;
	////---------------------------------------------------
	//	case 599: name="Jupiter";	
	//		break;
	//	case 501: name="Io";	
	//		break;
	//	case 502: name="Europa";	
	//		break;
	//	case 503: name="Ganymede";	
	//		break;
	//	case 504: name="Callisto";	
	//		break;
	////---------------------------------------------------
	//	case 699: name="Saturn";	
	//		break;
	//	case 601: name="Mimas";	
	//		break;
	//	case 602: name="Enceladus";	
	//		break;
	//	case 603: name="Tethys";	
	//		break;
	//	case 604: name="Dione";	
	//		break;
	//	case 605: name="Rhea";	
	//		break;
	//	case 606: name="Titan";	
	//		break;
	//	case 608: name="Iapetus";	
	//		break;
	////---------------------------------------------------
	//	case 799: name="Uranus";	
	//		break;
	//	case 701: name="Ariel";	
	//		break;
	//	case 702: name="Umbriel";	
	//		break;
	//	case 703: name="Titanija";	
	//		break;
	//	case 704: name="Oberon";	
	//		break;
	//	case 705: name="Miranda";	
	//		break;
	////---------------------------------------------------
	//	case 899: name="Neptune";	
	//		break;
	//	case 801: name="Triton";	
	//		break;
	//	case 802: name="Nereid";	
	//		break;
	//	case 808: name="Proteus";	
	//		break;
	//	case 999: name="Pluto";	
	//		break;
	////---------------------------------------------------
	//	case 901: name="Charon";	
	//		break;
	//
	//	default:
	//		name="Noname"
	//		;
	//	}
	//	return(name);
	//};
	//int name2id(System::String^ name)
	//{
	//	int id;
	//
	//	if(name == "Mercury") id=1;
	//
	//	if(name == "Venus") id=2;	
	//
	//	if(name ==  "Earth-Moon barycenter") id=3;	
	//
	//	if(name == "Mars barycenter") id=4;	
	//
	//	if(name ==  "Jupiter barycenter") id=5;	
	//
	//	if(name == "Saturn barycenter") id=6;	
	//
	//	if(name == "Uranus barycenter") id=7;	
	//
	//	if(name == "Neptune barycenter") id=8;	
	//
	//	if(name == "Pluto barycenter") id=9;	
	//
	//	if(name == "Sun") id=10;	
	//
	//	if(name == "Mercury") id=199;	
	//
	//	if(name == "Venus") id=299;	
	////-----------------------------------------------------------------
	//	if(name == "Earth") id=399;	
	//
	//	if(name == "Moon") id=301;	
	////-----------------------------------------------------------------
	//	if(name == "Mars") id=499;	
	//
	//	if (name == "Phobos") id = 401;
	//
	//	if (name == "Deimos") id = 402;
	////-----------------------------------------------------------------	
	//	if(name == "Jupiter") id=599;
	//
	//	if(name == "Io") id=501;
	//
	//	if(name == "Europa") id=502;
	//
	//	if(name == "Ganymede") id=503;
	//
	//	if(name == "Callisto") id=504;
	////--------------------------------------------------------
	//
	//	if(name == "Saturn") id=699;
	//
	//	if(name == "Mimas") id=601;
	//
	//	if(name == "Enceladus") id=602;
	//
	//	if(name == "Tethys") id=603;
	//
	//	if(name == "Dione") id=604;
	//	
	//	if(name == "Rhea") id=605;
	//	
	//	if(name == "Titan") id=606;
	//
	//	if(name == "Iapetus") id=608;
	////-------------------------------------------------
	//	if(name == "Uranus") id=799;
	//
	//	if(name == "Ariel") id=701;
	//
	//	if(name == "Umbriel") id=702;
	//
	//	if(name == "Titanija") id=703;
	//
	//	if(name == "Oberon") id=704;
	//
	//	if(name == "Miranda") id=701;
	////------------------------------------------------
	//	if(name ==  "Neptune") id=899;
	//
	//	if(name ==  "Triton") id=801;
	//
	//	if(name ==  "Nereid") id=802;
	//
	//	if(name ==  "Proteus") id=808;
	////------------------------------------------------
	//	if(name == "Pluto") id=999;
	//
	//	if(name == "Charon") id=901;
	//
	//	return(id);
	//
	//};

	triple getR(int ID)
	{
		double valPM[3], RADII[3];
		SpiceInt dim;
		char  id[20];
		_itoa_s(ID, id, 10);
		bodvrd_c(id, "PM", 3, &dim, valPM);
		bodvrd_c(id, "RADII", 3, &dim, RADII);
		triple R(RADII);
		return R;
	};
	double getW(int ID)
	{
		double valPM[3];
		SpiceInt dim;
		char  id[20];
        _itoa_s(ID, id, 10);
		bodvrd_c(id, "PM", 3, &dim, valPM);

		double W = valPM[1] / rad / 24.0 / 3600.0;
		return W;

	};
	void getEllPar(int ID, double &Re, double &f, double &oz)
	{
		if (399 != ID)
		{
			double valPM[3], RADII[3];
			SpiceInt dim;
			char  id[20];
            _itoa_s(ID, id, 10);
			bodvrd_c(id, "PM", 3, &dim, valPM);
			bodvrd_c(id, "RADII", 3, &dim, RADII);
			oz = valPM[1] / rad / 24.0 / 3600.0;
			for (int i = 0; i < 3; i++)Global::R[i] = RADII[i];
			Re = (RADII[0] + RADII[1]) / 2.0;
			f = (Global::Re - Global::R[2]) / Global::Re;
			double Rm = (RADII[0] + RADII[1] + RADII[2]) / 3.0;
		}
		else
		{
			Re = 6378.137;
			f = 0.00335281066474748071984552861852;
			oz = 7.292115e-5;

		}
	};
}

