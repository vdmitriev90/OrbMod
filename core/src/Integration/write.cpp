#define _CRT_SECURE_NO_WARNINGS
#include "Integration_.h"
#include "Global.h"
#include "force.h"
#include "constant.h"
#include "frame.h"
#include "visibility.h"

#include "SpiceUsr.h"

using namespace consts;
using namespace std;
//
namespace OrbMod
{
	void Integration::streamsOpen()
	{
        #pragma region Output

		fosv = fopen("sv_J2000.out", "w");
		//fprintf(fosv,"year month day hms(UTC) TDB(sec) interval(days) X Y Z Vx Vy Vz \n");

		foel = fopen("elts_J2000.out", "w");
		//	fprintf(foel,"year month day hms(UTC) TDB(sec) interval(days) A E I NODE W M \n");
		foSvEcl = fopen("sv_ECLIPJ2000.out", "w");
		foelEcl = fopen("elts_ECLIPJ2000.out", "w");
		fosvR = fopen("sv_IAUplanet.out", "w");
		//	fprintf(fosvR,"year month day hms(UTC) TDB(sec) interval(days) X Y Z Vx Vy Vz \n");

		//fosvp = fopen("sv_planetIAU.out", "w");
		//	fprintf(fosvp,"year month day hms(UTC) TDB(sec) interval(days) X Y Z Vx Vy Vz \n");

	   //foelp = fopen("elts_planetIAU.out", "w");
		//	fprintf(foelp,"year month day hms(UTC) TDB(sec) interval(days) A E I NODE W M \n");

		//foelR = fopen("elts_IAUplanet.out", "w");
		//	fprintf(foelR,"year month day hms(UTC) TDB(sec) interval(days) A E I NODE W M \n");

		foBL = fopen("BL.out", "w");
		//	fprintf(foBL,"year month day hms(UTC) TDB(sec) interval(days) L B H \n");

		foNEU = fopen("NEU.out", "w");
		//	fprintf(foNEU,"year month day hms(UTC) TDB(sec) interval(days) N E U \n");

		fopen_s(&fvisi, "visibility.out", "w");

        fo3bg = fopen("3body_geodetic.out", "w");

#pragma endregion
	}


	void Integration::streamsClose()
	{
		fclose(fosv);
		fclose(foel);

		fclose(foSvEcl);
		fclose(foelEcl);

		fclose(fosvR);
		//fclose(foelR);

		//fclose(fosvp);
		//fclose(foelp);

		fclose(foBL);

		fclose(foNEU);

		fclose(fvisi);
		fclose(fo3bg);
	}
	//
	void Integration::write(double t0, triple X, triple V)
	{
		ConstSpiceChar *pictur = "YYYY MM DD HR:MN:SC.####### ::TDB";
		Force Fs(t0, X, V);
		double mu = Force::getMu();

		double elts[8], eltsPl[8], eltsIAUpl[8], SVo[6], SViau[6], SViauNR[6], SVpl[6], NEU[6], SVEcl[6], eltsEcl[8];

		SVo[0] = X[0];
		SVo[1] = X[1];
		SVo[2] = X[2];
		SVo[3] = V[0];
		SVo[4] = V[1];
		SVo[5] = V[2];

		if (Global::cb_out_sv_ECLIPJ2000 == true || Global::cb_out_el_ECLIPJ2000 == true) trsv(0, 1, 17, SVo, SVEcl);
		if (Global::b_out_sv_IAUPlanet == true || Global::b_out_NEU == true || Global::b_out_AZR == true) trsv(t0, 1, Global::IDC, SVo, SViau);

		if (Global::b_out_NEU == true || Global::b_out_AZR == true)
		{
			double X0[3];
			for (int i = 0; i < 3; i++) 
                X0[i] = SViau[i] - Global::R_topo[i];
			mxv_c(Global::M_topo, X0, NEU);
		}

		char utcstr[50];
		timout_c(t0, pictur, 50, utcstr);

        //orbit elements J2000-----------------------				
		if (Global::b_out_el_J2000 == true) {
			fprintf(foel, "%s ", utcstr);
			fprintf(foel, " %25.16e ", t0);
			oscelt_c(SVo, 0, mu, elts);

			fprintf(foel, " %25.16e", elts[0]/**(1.0-elts[1])*/);
			fprintf(foel, " %25.16e", elts[1]);
			for (int i = 2; i < 6; i++) fprintf(foel, " %25.16e", elts[i] * rad);

			fprintf(foel, "\n");
		}
		else {}

		//state vector J2000--------------------------				
		if (Global::b_out_sv_J2000 == true) {
			fprintf(fosv, "%s ", utcstr);
			fprintf(fosv, " %25.16e ", t0);
			for (int i = 0; i < 6; i++) fprintf(fosv, " %25.16e", SVo[i]);

			fprintf(fosv, "\n");
		}
		else {}

		//orbit elements ECLIP2000-----------------------				
		if (Global::cb_out_el_ECLIPJ2000 == true) {
			fprintf(foelEcl, "%s ", utcstr);
			fprintf(foelEcl, " %25.16e ", t0);
			oscelt_c(SVEcl, 0, mu, eltsEcl);

			fprintf(foelEcl, " %25.16e", eltsEcl[0]/**(1.0-eltsEcl[1])*/);
			fprintf(foelEcl, " %25.16e", eltsEcl[1]);
			for (int i = 2; i < 6; i++) fprintf(foelEcl, " %25.16e", eltsEcl[i] * rad);

			fprintf(foelEcl, "\n");
		}

		//state vector ECLIPJ2000--------------------------				
		if (Global::cb_out_sv_ECLIPJ2000 == true) {
			fprintf(foSvEcl, "%s ", utcstr);
			fprintf(foSvEcl, " %25.16e ", t0);
			for (int i = 0; i < 6; i++) fprintf(foSvEcl, " %25.16e", SVEcl[i]);

			fprintf(foSvEcl, "\n");
		}

				//state vector IAU_PLANET---------------------	
		if (Global::b_out_sv_IAUPlanet == true) {
			fprintf(fosvR, "%s ", utcstr);
			fprintf(fosvR, " %25.16e ", t0);
			for (int i = 0; i < 6; i++) fprintf(fosvR, " %25.16e", SViau[i]);
			fprintf(fosvR, "\n");
		}

		// subsatellite point
		if (Global::b_out_BL == true) {
			double rectan[3];
			for (int iv = 0; iv < 3; iv++) rectan[iv] = SViauNR[iv];
			double lon;
			double lat;
			double alt;
			recgeo_c(rectan, Global::Re, Global::f, &lon, &lat, &alt);

			fprintf(foBL, "%s ", utcstr);
			fprintf(foBL, " %25.16e ", t0);
			fprintf(foBL, " %25.16e %25.16e %25.16e ", lon*rad, lat*rad, alt);
			fprintf(foBL, "\n");
		}
		//NEU
		if (Global::b_out_NEU == true) {
			fprintf(foNEU, "%s ", utcstr);
			fprintf(foNEU, " %25.16e ", t0);
			for (int i = 0; i < 3; i++)fprintf(foNEU, "%25.16e ", NEU[i]);
			fprintf(foNEU, "\n");
		}

		//visibility

		if (Global::b_visi == true)
		{
			if (Global::i_fr == 1) visi(fvisi, t0,  X, V);
			if (Global::i_fr == 0) visi(fvisi, t0,  triple(SVEcl[0], SVEcl[1], SVEcl[2]), triple(SVEcl[3], SVEcl[4], SVEcl[5]));
		}
		// Geodetic coordinates in 3-body frame
		if (true == Global::b_3_BFF_sv)	 write_3_BodyFix_sv(fo3bg, utcstr, t0,  X, V);

		//acceleration------------------------------------
		if (Global::b_out_acc == true) Fs.force_w(t0);
	};

	//
	void Integration::write_3_BodyFix_sv(FILE*f, SpiceChar* UTC, double t, triple X, triple V) {

		double sv[6], sv3b[6];
		double lt;
		triple RotFix, VotFix;
		if (Global::IDC == 10) for (int i = 0; i < 6; i++)sv[i] = .0;
		else spkgeo_c(Global::IDC, t, "J2000", 10, sv, &lt);

		triple Rsun_cb(sv[0], sv[1], sv[2]), Vsun_cb(sv[3], sv[4], sv[5]);

		spkgeo_c(Global::ID_3_BFF_num, t, "J2000", 10, sv3b, &lt);

		triple Rsun_3b(sv3b[0], sv3b[1], sv3b[2]), Vsun_3b(sv3b[3], sv3b[4], sv3b[5]);

		triple Rot = X + Rsun_cb - Rsun_3b;
		triple Vot = V + Vsun_cb - Vsun_3b;

		trsv(t, 1, Global::ID_3_BFF_num, Rot, Vot, RotFix, VotFix);

		fprintf(f, "%s ", UTC);
		fprintf(f, " %25.16e ", t);

		for (int i = 0; i < 3; i++) fprintf(f, " %25.16e ", RotFix[i]);
		for (int i = 0; i < 3; i++) fprintf(f, " %25.16e ", VotFix[i]);
		int ttt = Global::ID_3_BFF_num;
		double  rectan[3], flat, Re, oz, Lat, Lon, Alt;
		for (int i = 0; i < 3; i++)rectan[i] = RotFix[i];
		getEllPar(Global::ID_3_BFF_num, Re, flat, oz);
		recgeo_c(rectan, Re, flat, &Lon, &Lat, &Alt);
		fprintf(f, " %25.16e %25.16e %25.16e\n", Lon*rad, Lat*rad, Alt);

	};
}