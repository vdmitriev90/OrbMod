#include "stdafx.h"
#include "Integration_.h"
using namespace std;

namespace OrbMod
{
	void Integration::SODE()
	{
		const int  NOR = Global::NOR;
		double eps = Global::eps;
		double t0 = Global::t0;
		double te = Global::te;
		double step = Global::step;
		double SVi[6]; for (int i = 0; i < 6; i++) SVi[i] = Global::SV(i, 0);

		char lineRad[300];
		vector<double> Rado(NOR);
		vector<double> h(NOR);
		vector<vector<double> > C(NOR, vector<double>(NOR));
		vector<triple > X1(NOR);
		vector<triple > V1(NOR);
		//vector<triple > Fi(NOR);

		vector <triple> A1(NOR), A2(NOR);
		vector<vector<double>> Dh(NOR, vector<double>(NOR));
		vector<triple> Alp(NOR);
		vector<triple> dF(NOR);

		double tout = t0;

		triple F0, X(SVi[0], SVi[1], SVi[2]), V(SVi[3], SVi[4], SVi[5]), Fi;

		FILE*f = fopen("Radau.txt", "r");

		fosv = fopen("sv_J2000.out", "w");
		//fprintf(fosv,"year month day hms(UTC) TDB(sec) interval(days) X Y Z Vx Vy Vz \n");

		foel = fopen("elts_J2000.out", "w");
		//	fprintf(foel,"year month day hms(UTC) TDB(sec) interval(days) A E I NODE W M \n");
		foSvEcl = fopen("sv_ECLIPJ2000.out", "w");
		foelEcl = fopen("elts_ECLIPJ2000.out", "w");


		fosvp = fopen("sv_planetIAU.out", "w");
		//	fprintf(fosvp,"year month day hms(UTC) TDB(sec) interval(days) X Y Z Vx Vy Vz \n");

		foelp = fopen("elts_planetIAU.out", "w");
		//	fprintf(foelp,"year month day hms(UTC) TDB(sec) interval(days) A E I NODE W M \n");

		fosvR = fopen("sv_IAUplanet.out", "w");
		//	fprintf(fosvR,"year month day hms(UTC) TDB(sec) interval(days) X Y Z Vx Vy Vz \n");

		foelR = fopen("elts_IAUplanet.out", "w");
		//	fprintf(foelR,"year month day hms(UTC) TDB(sec) interval(days) A E I NODE W M \n");

		foBL = fopen("BL.out", "w");
		//	fprintf(foBL,"year month day hms(UTC) TDB(sec) interval(days) L B H \n");

		foNEU = fopen("NEU.out", "w");
		//	fprintf(foNEU,"year month day hms(UTC) TDB(sec) interval(days) N E U \n");

		foAZR = fopen("AZR.out", "w");
		//	fprintf(foAZR,"year month day hms(UTC) TDB(sec) interval(days) Azimut Z R \n");

		fvisi = fopen("visibility.out", "w");

		fo3bg = fopen("3body_geodetic.out", "w");
		//Õ¿’Œ∆ƒ≈Õ»≈ ƒŒÀ√Œ“€ ¬Œ—’ŒƒﬂŸ≈√Œ ”«À¿ Õ¿ “0

		//	if(Global::b_out_elts_planet || Global::b_out_sv_planet || Global::b_out_el_IAUPlanet==true){ 

		double poss[6];
		double lt1, dlt;
		triple Zorb;
		double Zpl[3];
		double TimeNode = t0;

		spkacs_c(Global::IDC, t0, "J2000", "NONE", 10, poss, &lt1, &dlt);

		triple Xv = triple(poss[0], poss[1], poss[2]);
		triple Vv = triple(poss[3], poss[4], poss[5]);
		Xv = Xv / Xv.getAbs();
		Vv = Vv / Vv.getAbs();
		Zorb = Xv&Vv / sin(triple::getAngle(Xv, Vv));

		double Z[3] = { Zorb[0], Zorb[1], Zorb[2] };

		trpos(t0, 1, Global::IDC, Z, Zpl);
		triple ZorbP = triple(Zpl);
		triple PolP = triple(0.0, 0.0, 1.0);

		triple Node = ZorbP&PolP;
		Node = Node / Node.getAbs();

		double NodeA = atan2(Node[1], Node[0]);
		if (NodeA < 0.0) NodeA = NodeA + 2 * pi;


		// œÀ¿Õ≈“Œ÷≈Õ“–»◊≈— ¿ﬂ √–¿¬»“¿÷»ŒÕÕ¿ﬂ œŒ—“ŒﬂÕÕ¿ﬂ
		double mu = Global::mu;

		int ii = 1;
		int jj = 0;

		while (!feof(f))
		{
			fscanf(f, "%s\n", lineRad);
			if (ii > Misc::sum(NOR - 1) && ii <= Misc::sum(NOR))
			{
				Rado[jj] = atof(lineRad); jj++;
			}
			else {}
			ii++;
		}
		//ËÌÚÂ„ËÓ‚‡ÌËÂ Ì‡Á‡‰
		if (te < t0) { step = -step; Global::Discr = -Global::Discr; }

		//System::Threading::Thread Worker ^ = gcnew System::Threading::Thread(delegate() {  });
		//ÒÓ·ÒÚ‚ÂÌÌÓ, Ò‡Ï ËÌÚÂ„ÚÓ:
		while (abs(te - t0) != 0e0)
		{
			if (abs(te - t0) < 1e-12) break;
			if (step > 0)
			{
				if (t0 + step > te) step = te - t0;
			}
			else
			{
				if (t0 + step < te) step = te - t0;
			}

			for (int i = 0; i < NOR; i++) h[i] = step*Rado[i];

			for (int k = 0; k < NOR; k++)
			{
				Dh[k][k] = h[k];
				for (int j = 0; j < k; j++)
				{
					Dh[k][j] = h[k] - h[j];
				}
			}

			//˜ËÒÎ‡ CÚËÎËÌ„‡
			for (int i = 0; i < NOR; i++)
			{
				C[i][i] = 1.0;
				if (i > 0) C[i][0] = -h[i - 1] * C[i - 1][0];
				for (int j = 1; j < i; j++) C[i][j] = C[i - 1][j - 1] - h[i - 1] * C[i - 1][j];
			}

			//////////////////////////////////////////////////////		
			F0 = Force::force_SODE(t0, X, V);

			for (int j = 0; j < NOR; j++)
			{
				X1[j] = X + V*h[j] + F0*h[j] * h[j] / 2;
				V1[j] = V + F0*h[j];
				///////////////////////////////////////////////
				Fi = Force::force_SODE(t0 + h[j], X1[j], V1[j]);

				dF[j] = Fi - F0;
			}

			Alp[0] = dF[0] / h[0];
			for (int k = 1; k < NOR; k++)
			{
				Alp[k] = dF[k] / h[k];
				for (int j = 0; j < k; j++)
				{
					Alp[k] = (Alp[k] - Alp[j]) / Dh[k][j];
				}
			}

			for (int k = 0; k < NOR; k++)
			{
				A1[k] = triple(0., 0., 0.);
				for (int i = k; i < NOR; i++) A1[k] = A1[k] + Alp[i] * C[i][k];
			}

			int ij = 0;
			for (;;)
			{
				for (int k = 0; k < NOR; k++)
				{
					triple 	v2 = A1[0] * 0.5;
					triple 	x2 = A1[0] * (1.0 / 6.0);

					for (int i = 1; i < NOR; i++)
					{
						v2 = v2 + A1[i] * (pow(h[k], i) / (i + 2));
						x2 = x2 + A1[i] * (pow(h[k], i) / (i + 2) / (i + 3));
					}

					v2 = V1[k] + v2*(pow(h[k], 2));
					x2 = X1[k] + x2*(pow(h[k], 3));
					//////////////////////////////////////////////
					Fi = Force::force_SODE(t0 + h[k], x2, v2);

					dF[k] = Fi - F0;
				}

				Alp[0] = dF[0] / h[0];
				for (int k = 1; k < NOR; k++)
				{
					Alp[k] = dF[k] / h[k];
					for (int j = 0; j < k; j++)
					{
						Alp[k] = (Alp[k] - Alp[j]) / Dh[k][j];
					}
				}

				for (int k = 0; k < NOR; k++)
				{
					A2[k] = triple(0.0, 0., 0.);
					for (int i = k; i < NOR; i++) A2[k] = A2[k] + Alp[i] * C[i][k];
				}

				vector <triple> dV(NOR);
				double max = 0;
				vector<double> mdV(NOR);
				for (int i = 0; i < NOR; i++)
				{
					dV[i] = A2[i] - A1[i];
					mdV[i] = dV[i].getAbs();
					if (abs(max < mdV[i]))max = mdV[i];
				}
				if (max < eps && ij>2)	goto exit;
				if (ij > 7)	goto exit;

				A1 = A2;
				ij++;

			}

		exit:   triple dv = A1[0] * 0.5;
			triple dx = A1[0] * (1.0 / 6.0);

			for (int i = 1; i < NOR; i++)
			{
				dv = dv + A1[i] * (pow(step, i) / (i + 2.0));
				dx = dx + A1[i] * (pow(step, i) / (i + 2.0) / (i + 3.0));
			}

			//Á‡ÔËÒ¸ ÂÁÛÎ¸Ú‡ÚÓ‚:
			//int ik=int(t0-ts)%Global::Discr;
			if (Global::Discr != 0)
			{
				while (abs(tout - t0) < abs(step))
				{
					double hout = tout - t0;

					triple dvo = A1[0] * 0.5;
					triple dxo = A1[0] * (1.0 / 6.0);
					for (int i = 1; i < NOR; i++)
					{
						dvo = dvo + A1[i] * (pow(hout, i) / (i + 2.0));
						dxo = dxo + A1[i] * (pow(hout, i) / (i + 2.0) / (i + 3.0));
					}

					triple Xout = X + V*hout + F0*(hout*hout / 2.0) + dxo*(hout*hout*hout);
					triple Vout = V + F0*hout + dvo*(hout*hout);

					write(tout, Xout, Vout, TimeNode, NodeA);

					tout += Global::Discr;
				}
			}

			X = X + V*step + F0*(step*step / 2.0) + dx*(step*step*step);
			V = V + F0*step + dv*(step*step);


			t0 += step;

		};

		write(t0, X, V, TimeNode, NodeA);

		fclose(fosv);
		fclose(foel);

		fclose(foSvEcl);
		fclose(foelEcl);


		fclose(fosvR);
		fclose(foelR);

		fclose(fosvp);
		fclose(foelp);

		fclose(foBL);

		fclose(foNEU);
		fclose(foAZR);

		fclose(fvisi);
		fclose(fo3bg);

	};
}