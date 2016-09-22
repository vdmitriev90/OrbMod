#pragma once
#include"stdafx.h"
using namespace std;
using namespace Consts;
using namespace Algebra;

namespace OrbMod
{
	class Cunningham;

	//enum NameOrNumber { Name = 0, Number = 1 };
	class Global
	{
	public:
		//
		static std::string FormCaption;
		//
		static ConstSpiceChar *pictur_utc;
		static ConstSpiceChar * Global::pictur_tdb;
		static ConstSpiceChar * Global::pictur_tdt;
		//
		static int lineWidth;
		static int symbolType;
		static int symbolSize;

		static EarthFixFrame EFrame;
		static char *		EarthFrame;
		
		//
		static TypeOfObs	ObsT;
		
		//��� ��������� ��������
		static Variables	Var;
		//�����
		static Mode			mode;
		//����� ����������� ������
		static FitMode		fitMode;

		static double		ArcLength;
		static int			MinObsinBatch;

		//����� ������
		static long int		start;

		//������ ���������
		static FrameOfIC	ICFrame;
		//����� �������
		static TimeFormat  Tscale;
		//��� ��������� �������
		static int			i_IC;
		static bool			IsUsePeriTime;
		//���������� ��������������
		static int			NOR;
		static double		eps;
		static double		t0;
		static double		te;
		static int			Niter;
		//
		static double		step;
		static Matrix		SV_start;
		static Matrix		SV;
		static Matrix		Q;
		static bool			IsAutoStep;
		//
		static double		Discr;
		static			int prog;

		//����������� ����
		static unsigned int	IDC;

		//��� ���������
		static double		mu;
		static double		R[3];
		static double		f;
		static double		Re;
		static double		Rm;
		static double		oz;

		//ID ���. ���
		static unsigned int	ID1;
		static unsigned int	ID2;
		static unsigned int	ID3;
		static unsigned int	ID4;
		static unsigned int	ID5;
		//����������
		//�� ������
		static bool			b_10;
		static bool			b_1;
		static bool			b_2;
		static bool			b_3;
		static bool			b_4;
		static bool			b_5;
		static bool			b_6;
		static bool			b_7;
		static bool			b_8;
		static bool			b_9;

		//���. ����
		static bool			b_add1;
		static bool			b_add2;
		static bool			b_add3;
		static bool			b_add4;
		static bool			b_add5;
		static Cunningham	GravField_add5;
		static bool			b_add5_cun_on;

		static bool			b_add5_tide_sun;
		static bool			b_add5_tide_body;
		static int			add5_tide_ID;

		//�������������� �������
		static bool			b_rel;
		static bool			b_rel_LT;

		// ��������� ������
		static bool			b_out_sv_J2000;
		static bool			b_out_el_J2000;

		static bool			cb_out_sv_ECLIPJ2000;
		static bool			cb_out_el_ECLIPJ2000;

		static bool			b_out_sv_IAUPlanet;

		static bool			b_out_BL;

		static bool			b_out_NEU;
		static bool			b_out_AZR;

		static bool			b_out_acc;
		static bool			b_in;

		//BFF(body fixed frame) 3-�� ����
		static bool			b_3_BFF_sv;
		static int			ID_3_BFF_num;

		// ��������������� ������� �������
		static bool			b_Cunn;
		static Cunningham	GravField_CB;
		static bool			b_tide_CB_sun;
		static bool			b_tide_CB_body;
		static int			CB_tide_ID;

		//�������� ��������:
		static bool			b_SRP;

		//������������� ���������
		static bool			b_atm;
		//
		//��� ���������������� ������� ���������
		static double		Lat_topo;
		static double		Lon_topo;
		static double		H_topo;
		static double		R_topo[3];
		static double		M_topo[3][3];
		//
		//���������
		static bool			b_visi;
		static bool			b_rot_with_3body;
		static int			i_fr;
		static bool			b_visi_rb;
		static int			N_visi;
		static double		B_visi;
		static double		L_visi;
		static double		H_visi;
		static double		R_visi[3];
		static double		M_visi[3][3];
		static long unsigned int N_rp;
		static double		oz_visi;
		static bool			b_visi_pl;
		static int			ID_visi;
		static double		R_pl;
		//
		//colors
		static int			col_Main;
		//
		static int ColorsAcc[22];
		//
		static unsigned int	ElapsedTime;


	};
}