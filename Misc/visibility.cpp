#include "stdafx.h"
#include "visibility.h"

namespace OrbMod
{
	void visi(FILE*fvisi, double time, double t0, triple X, triple V) {

		double RotIAU_m[3], RotNEU_m[3], R1[6], Rs[3], pri[3], sec[3], rot[3][3], twf[3][3], Xaxis[3], Yaxis[3], X3b[3];
		double r, colat, lon, mX, alph, alph_kr, lt, alphS, alphS_kr;
		bool visi = true;
		char *FRAME;
		int i_frame = 0;

		if (Global::i_fr == 0) { FRAME = "ECLIPJ2000"; i_frame = 17; }
		else { FRAME = "J2000"; i_frame = 1; }

		SpiceChar   utcstr[50];
		triple Vo;
		triple Vot, RotJ2k;
		timout_c(time, Global::pictur_utc, 50, utcstr);
		mX = X.getAbs();

		spkgeo_c(Global::IDC, time, FRAME, Global::N_visi, R1, &lt);
		if (Global::b_rot_with_3body == true)
		{
			for (int i = 0; i < 3; i++) { Xaxis[i] = R1[i]; Yaxis[i] = R1[i + 3]; X3b[i] = X[i]; }
			twovec_c(Xaxis, 1, Yaxis, 2, twf);
			mxv_c(twf, X3b, X3b);
		}
		triple Rtbto(R1[0], R1[1], R1[2]);
		triple Vtbto(R1[3], R1[4], R1[5]);

		for (int i = 0; i < 3; i++) { pri[i] = Rtbto[i]; sec[i] = Vtbto[i]; }

		if (Global::b_visi_rb == true) {

			triple roIAU(Global::R_visi);
			triple roJ2k = trpos(time, Global::N_visi, i_frame, roIAU);
			RotJ2k = Rtbto + X - roJ2k;
			triple RotIAU;
			RotIAU = trpos(time, i_frame, Global::N_visi, RotJ2k);
			for (int i = 0; i < 3; i++) RotIAU_m[i] = RotIAU[i];
			mxv_c(Global::M_visi, RotIAU_m, RotNEU_m);

			recsph_c(RotNEU_m, &r, &colat, &lon);
			if (colat > pi / 2.0) visi = false;
			if (visi == true)
			{
				alph_kr = asin(Global::Rm / mX);
				alph = triple::getAngle(RotJ2k, X);
				if (alph < alph_kr) visi = false;
				if (visi == true)
				{
					spkgps_c(10, time, FRAME, Global::N_visi, Rs, &lt);
					triple Ros(Rs);
					triple RVsun = Ros - roJ2k;
					alphS = triple::getAngle(RVsun, RotJ2k);
					alphS_kr = asin(Rsun / RVsun.getAbs());
					if (alphS < alphS_kr) visi = false;
					if (visi == true && Global::b_visi_pl == true)
					{
						double Rss[3];
						spkgps_c(Global::ID_visi, time, FRAME, Global::N_visi, Rss, &lt);
						triple r1(Rss);
						r1 = r1 + X;
						r1 = r1*(-1.);
						double aph = triple::getAngle(r1, RotJ2k);
						double aph_kr = asin(Global::R_pl / r1.getAbs());
						if (aph < aph_kr) visi = false;
					}
				}
			}
			triple w(.0, .0, Global::oz_visi);
			Vo = roIAU&w;
			triple VoJ2k = trpos(time, Global::N_visi, i_frame, Vo);
			Vot = Vo + Vtbto + V;

			fprintf(fvisi, "%s %25.16e %25.16e %d %25.16e %25.16e %25.16e %25.16e %25.16e %25.16e %25.16e %25.16e %25.16e", utcstr, time, t0, visi, RotJ2k[0], RotJ2k[1], RotJ2k[2], colat*rad, Vot[0], Vot[1], Vot[2], RotJ2k.getAbs(), Vot.getAbs());
		}
		else
		{
			triple Rot = Rtbto + X;
			triple Vot = Vtbto + V;
			double Rot_m[3];
			for (int i = 0; i < 3; i++) Rot_m[i] = Rot[i];
			//recsph_c(Rot_m,&r,&colat,&lon);
			//if(colat>pi/2.0) visi = false;
			//if (visi == true)

			alph_kr = asin(Global::Rm / mX);
			alph = triple::getAngle(Rot, X);
			if (alph < alph_kr) visi = false;
			//fprintf(fvisi,"%d\n",visi);

			if (visi == true)
			{
				spkgps_c(10, time, FRAME, Global::N_visi, Rs, &lt);

				triple Ros(Rs);

				alphS = triple::getAngle(Ros, Rot);

				alphS_kr = asin(Rsun / Ros.getAbs());
				double a = Vot[0];
				if (alphS < alphS_kr) visi = false;
				if (visi == true && Global::b_visi_pl == true)
				{
					double Rss[3];
					spkgps_c(Global::ID_visi, time, FRAME, Global::N_visi, Rss, &lt);
					triple r1(Rss);
					r1 = r1 + X;
					r1 = r1*(-1.);
					double aph = triple::getAngle(r1, Rot);
					double aph_kr = asin(Global::R_pl / r1.getAbs());
					if (aph < aph_kr) visi = false;
				}
			}
			fprintf(fvisi, "%s %25.16e %25.16e ", utcstr, time, t0);
			fprintf(fvisi, "%d %25.16e %25.16e %25.16e 0.0 ", visi, Rot[0], Rot[1], Rot[2]);
			fprintf(fvisi, " %25.16e %25.16e %25.16e %25.16e %25.16e", Vot[0], Vot[1], Vot[2], Rot.getAbs(), Vot.getAbs());
		}
		if (Global::b_rot_with_3body == true)
		{
			fprintf(fvisi, " %25.16e %25.16e %25.16e\n", X3b[0], X3b[1], X3b[2]);
		}
		else fprintf(fvisi, " 0 0 0 \n");

	};
}