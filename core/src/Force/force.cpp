#include"force.h"
#include"Global.h"
#include"constant.h"
#include"macroses.h"
#include"AtmosphericDrag.h"
#include"SRP.h"
#include"frame.h"

#include"SpiceUsr.h"

using namespace std;
using namespace Algebra;
using namespace consts;
//
namespace OrbMod
{
	double Force::mu;
	FILE * Force::facc;
	//
	Force::Force() {};
	//
	Force::Force(const double &t, const  triple &X, const triple &V)
	{
		this->time = t;
		this->X = X;
		this->V = V;
	};

	//
	Force::~Force() {};

	//
	void Force::AccFileOpen()
	{
        fopen_s(&facc, "acc.out", "w");
	}

	void Force::AccFileClose()
	{
		fclose(facc);
	}

	void Force::setMu()
	{
		if (Global::b_Cunn) mu = Global::GravField_CB.getGM();
		else mu = ID2GM(Global::IDC);
	};

	//
	triple Force::force_SODE(const double Ti, const triple &Xi, const triple &Vi)
	{
		Force f(Ti, Xi, Vi);
		return  (f.force_cb() + f.force_pert());
	}

	//
	//Central body acceleration 
	triple Force::force_cb()
	{
		double r = X.getAbs();
		triple a = (X)*(-mu) / (r*r*r);
		return a;
	}

	//
	//Perturbation acceleration
	triple Force::force_pert()
	{
		triple acc = triple(.0, .0, .0);
		triple accp;

		SRP EFG;
		AtmosphericDrag HIJ;

		//��������� �� ������������ ����
		if (Global::b_Cunn) acc = Global::GravField_CB.getAcceleration(Global::IDC, time, X);

		//��������
		if (Global::b_1) { accp = planet(1); acc = acc + accp; }
		//������
		if (Global::b_2) { accp = planet(2); acc = acc + accp; }
		//�����+����
		if (Global::b_3) { accp = planet(3); acc = acc + accp; }
		//����
		if (Global::b_4) { accp = planet(4); acc = acc + accp; }
		//������
		if (Global::b_5) { accp = planet(5); acc = acc + accp; }
		//������
		if (Global::b_6) { accp = planet(6); acc = acc + accp; }
		//����
		if (Global::b_7) { accp = planet(7); acc = acc + accp; }
		//������
		if (Global::b_8) { accp = planet(8); acc = acc + accp; }
		//������
		if (Global::b_9) { accp = planet(9); acc = acc + accp; }
		//������
		if (Global::b_10) { accp = planet(10); acc = acc + accp; }

		//add
		if (Global::b_add1) { accp = planet(Global::ID1); acc = acc + accp; }
		if (Global::b_add2) { accp = planet(Global::ID2); acc = acc + accp; }
		if (Global::b_add3) { accp = planet(Global::ID3); acc = acc + accp; }
		if (Global::b_add4) { accp = planet(Global::ID4); acc = acc + accp; }

		if (Global::b_add5)
		{
			accp = acc5th_body();
			acc += accp;
		}

		//SRP
		if (Global::b_SRP) {

			EFG.setpos(X);
			triple acc_SRP = EFG.getAcceleration(time);
			acc = acc + acc_SRP;
		}
		//����������� ����������
		if (Global::b_atm) {

			HIJ.setPos(X);
			HIJ.setVel(V);
			acc = acc + HIJ.getAcc(time);
		}

		//�������������� ���������� � ������ ������ �����������(PPN=1)
		if (Global::b_rel) { triple accr = relativ(); acc = acc + accr; }
		if (Global::b_rel_LT) { triple accLT = L_T(); acc = acc + accLT; }

		return(acc);
	};

	//
	triple Force::planet(int IDP) 
	{

		double mu = ID2GM(IDP);
		return planet(IDP, mu);

	}

	triple Force::planet(int IDP, double mu) {
		triple Xa = X;
		double poss[3];
		double lt1;
		triple rp, Delta;
		spkgps_c(IDP, time, "J2000", Global::IDC, poss, &lt1);

		triple Xp(poss);
		Delta = Xp - Xa;
		double d = Delta.getAbs();
		double r = Xp.getAbs();
		triple accp = Delta*mu / pow(d, 3) - Xp*mu / pow(r, 3);

		return accp;
	}

	//
	//the perturbation by additional body #5(central and none-central gravity)
	triple Force:: acc5th_body()
	{
		triple acc_;
		if (Global::b_add5_cun_on)
		{
			//centric part of  acceleration 
			triple acc_point = planet(Global::ID5, Global::GravField_add5.getGM());

			double pos[3], lt;
			spkgps_c(Global::IDC, time, "J2000", Global::ID5, pos, &lt);
			triple pos_CB(pos);
			triple Xbs = pos_CB + X;
			// non-centric part of  acceleration by #5
			triple fs = Global::GravField_add5.getAcceleration(Global::ID5, time, Xbs);
			triple fcb = Global::GravField_add5.getAcceleration(Global::ID5, time, pos_CB);

			acc_ = acc_point + (fs - fcb);
		}
		else
		{
			acc_ = planet(Global::ID5);
		}
		return acc_;
	}

	//
	triple Force::relativ()
	{
		double r = X.getAbs();
		double v2 = V.getSq();
		double r3 = r*r*r;
		double r4 = r3*r;
		double c2 = SoL*SoL;
		double K1 = 4.0 * mu*mu / (c2*r4);
		double K2 = mu / (c2*r3);

		triple rel = K1*X + K2*((4.0*(X*V))*V - v2*X);
		return rel;
	}

	//Lenze-Thirring precession:
	triple Force::L_T()
	{
		double Xa[6];
		double Xb[6];
		double Va[3], Voz[3];
		double H[3];
		double Flenze[3], FlenzeI[3];

		Xa[0] = X[0];
		Xa[1] = X[1];
		Xa[2] = X[2];

		Xa[3] = V[0];
		Xa[4] = V[1];
		Xa[5] = V[2];
		double R = X.getAbs();

		double Rp = (Global::R[0] + Global::R[1] + Global::R[2]) / 3.0;

		double  oz = Global::oz;
		Voz[0] = 0.0;
		Voz[1] = 0.0;
		Voz[2] = oz;

		trsv(time, 1, Global::IDC, Xa, Xb);

		Va[0] = Xb[3];
		Va[1] = Xb[4];
		Va[2] = Xb[5];

		double k = 2.0*mu*Rp*Rp / (5.0*SoL*SoL*R*R*R);
		for (int i = 1; i < 3; i++) {
			H[i] = k*(Voz[i] - (3.0*Xb[i] * oz*Xb[2]) / (R*R));
		}
		Flenze[0] = 2.0*(Va[1] * H[2] - Va[2] * H[1]);
		Flenze[1] = 2.0*(Va[2] * H[0] - Va[0] * H[2]);
		Flenze[2] = 2.0*(Va[0] * H[1] - Va[1] * H[0]);

		trpos(time, Global::IDC, 1, Flenze, FlenzeI);

		return FlenzeI;
	}

	//
	void Force::force_w(double Ti)
	{
		ConstSpiceChar *pictur = "YYYY MM DD HR:MN:SC.####### ::UTC";

		triple acc, accp, accr, acc_SRP, accA;

		SRP EFG;
		AtmosphericDrag HIJ;

		SpiceChar        utcstr[100];
		//et2utc_c ( this->time,  "C", 10, 80, utcstr );
		timout_c(time, pictur, 50, utcstr);
		fprintf(facc, "%s", utcstr);
		fprintf(facc, et_F, time);
		triple acccb = force_cb();
		fprintf(facc, et_F, acccb.getAbs());

		//Central body + harmonic coefficients
		if (Global::b_Cunn)
		{
			triple accCunn = Global::GravField_CB.getAcceleration(Global::IDC, time, X);
			fprintf(facc, et_F, accCunn.getAbs());
		}
		else fprintf(facc, " 0");

		//Sun
		if (Global::b_10) { accp = planet(10); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }

		//Mercury 
		if (Global::b_1) { accp = planet(1); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }

		//Venus
		if (Global::b_2) { accp = planet(2); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }

		//Earth+Moon
		if (Global::b_3) { accp = planet(3); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }
		//Mars
		if (Global::b_4) { accp = planet(4); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }
		//Jupiter
		if (Global::b_5) { accp = planet(5); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }
		//Saturn
		if (Global::b_6) { accp = planet(6); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }
		//Uranus
		if (Global::b_7) { accp = planet(7); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }
		//Neptune
		if (Global::b_8) { accp = planet(8); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }
		//Pluto
		if (Global::b_9) { accp = planet(9); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }

		//add1
		if (Global::b_add1) { accp = planet(Global::ID1); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }
		//add2
		if (Global::b_add2) { accp = planet(Global::ID2); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }
		//add3
		if (Global::b_add3) { accp = planet(Global::ID3); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }
		//add4
		if (Global::b_add4) { accp = planet(Global::ID4); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }

		if (Global::b_add5) 
		{
			//add5's central gravity part 
			accp = planet(Global::ID5);
			// add5's non-central gravity part
			if (Global::b_add5_cun_on) {

				double pos[3], lt;
				spkgps_c(Global::IDC, time, "J2000", Global::ID5, pos, &lt);
				
				triple pos_CB(pos);
				triple Xbs = pos_CB + X;

				triple fs = Global::GravField_add5.getAcceleration(Global::ID5, time, Xbs);
				triple fcb = Global::GravField_add5.getAcceleration(Global::ID5, time, pos_CB);

				fprintf(facc, " %13.5e  %13.5e ", accp.getAbs(), (fs - fcb).getAbs());
			}
			else 
			{
				fprintf(facc, " %13.5e  0 ", accp.getAbs());
			}
		}
		else { fprintf(facc, " 0 0 "); }

		//SRP
		if (Global::b_SRP) {
			EFG.setpos(X);
			acc_SRP = EFG.getAcceleration(time);

			fprintf(facc, et_F, acc_SRP.getAbs());
		}
		else { fprintf(facc, " 0"); }

		//atmospheric drag
		if (Global::b_atm) {
			HIJ.setPos(X);
			HIJ.setVel(V);
			accA = HIJ.getAcc(time);

			fprintf(facc, et_F, accA.getAbs());
		}
		else { fprintf(facc, " 0"); }

		//General relativity effects (Swartsshild metric,PPN=1)
		if (Global::b_rel) { accp = relativ();  fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }

		//General relativity effects (L-T precession, PPN=1)
		if (Global::b_rel_LT) { accp = L_T(); fprintf(facc, et_F, accp.getAbs()); }
		else { fprintf(facc, " 0"); }
		fprintf(facc, "\n");
	}
}