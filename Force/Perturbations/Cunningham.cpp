#include "stdafx.h"
#include "Force\Perturbations\Cunningham.h"
using namespace std;
namespace OrbMod
{
	//факториал
	long double factorial(int N) {
		//if (N<0) {cout<<"error fatorial <0"; exit(0);};
		if (N < 2) return 1;

		return (N*factorial(N - 1));
	}
	//двойной факториал
	long double dblefactorial(int N) {
		//if (N<0) {cout<<"error fatorial <0"; exit(0);};
		if (N < 2) return 1;

		return (N*dblefactorial(N - 2));
	}
	//GM и R0 
/*	double Cunningham::GM;
	double Cunningham::R0;
	//Макс. степень учета гармоник ГП
	int Cunningham::Ngf;
	vector<vector<ComplexNum>>  Cunningham:: GravModel;
*/
	Cunningham::Cunningham(void)
	{
	}

	Cunningham::~Cunningham(void)
	{
	}

	double enom(int m) {
		if (m == 0) return 1.0;
		return 2.0;
	}

	//загрузка модели ГП
	void Cunningham::LoadGravityModel(string str) 
	{
		//задание n,m
		this->GravModel.resize(this->Ngf + 1);

		for (int i = 0; i <= this->Ngf; i++) this->GravModel[i].resize(this->Ngf + 1);

		char str_GM[50], str_R0[50], str_XZ[50], str_Nmax[50], str_Mmax[50], str_Normalize[50], str_1[50], str_2[50], str_n[5], str_m[5], str_C[50], str_S[50], str_mC[50], str_mS[30];

		double C, S, coef;

		int n, m;

		ComplexNum CSnm;
		this->FileModel = str;

		FILE*f = fopen(str.c_str(), "r");

		fscanf(f, "%s %s %s %s %s %s %s %s\n", str_R0, str_GM, str_XZ, str_Nmax, str_Mmax, str_Normalize, str_1, str_2);

		//GM и R0
		Cunningham::GM = atof(str_GM);
	    Cunningham:R0 = atof(str_R0);

		unsigned int Normalize = atoi(str_Normalize);
		//reading of file with gravity model
		while (!feof(f)) {

			fscanf(f, "%s %s %s %s %s %s \n", str_n, str_m, str_C, str_S, str_mC, str_mS);

			n = atoi(str_n);
			m = atoi(str_m);
			C = atof(str_C);
			S = atof(str_S);

			if (n > this->Ngf) break;

			//denormalization
			coef = enom(m) *(2.0*n + 1)*factorial(n - m) / factorial(n + m);
			coef = sqrt(coef);
			C *= coef;
			S *= coef;

			CSnm.setNum(C, -S);

			this->GravModel[n][m] = CSnm;
		}
		fclose(f);
		//excluding of central part of gravity
		GravModel[0][0].setNum(0, 0);

		this->init_poly(Ngf);
		this->mu_sun = BODY10_GM;
		//this->mu_body = ID2GM(this->bodyID);
		//for (int i = 0; i < 3; i++) { dCS_body[i].setNum(0., 0.); dCS_sun[i].setNum(0., 0.); }
	}
	//
	void Cunningham::init_poly(int N)
	{
		this->dVx.resize(N + 1);
		for (int i = 0; i <= N; i++) this->dVx[i].resize(N + 1);

		this->dVy.resize(N + 1);
		for (int i = 0; i <= N; i++) this->dVy[i].resize(N + 1);

		this->dVz.resize(N + 1);
		for (int i = 0; i <= N; i++) this->dVz[i].resize(N + 1);

		V.resize(N + 3);
		for (int i = 0; i <= N + 2; i++) V[i].resize(N + 3);
	}
	//Cunninghan's polinoms
	void Cunningham::validdV()
	{
		double r1 = this->r.getAbs();
		double r2 = r1*r1;
		double R0dr1 = R0 / r1;
		double rho = SQR(R0dr1);
		double R0dr2 = R0 / r2;

		double x0 = this->r[0] * R0dr2;
		double y0 = this->r[1] * R0dr2;
		double z0 = this->r[2] * R0dr2;

		for (int n = 0; n <= this->Ngf + 2; n++)
			for (int m = 0; m <= n; m++)
			{
				if (n == 0 && m == 0) 
				{
					V[n][m].setNum(R0dr1);
					continue;
				}

				if (n == m) 
				{
					ComplexNum xy(x0, y0);
					V[n][m] = xy*V[n - 1][m - 1] * (2.0*n - 1);
					continue;
				}

				if (n == m + 1) 
				{
					V[n][m] = V[n - 1][m] * z0*(2.0*n - 1);
					continue;
				}

				V[n][m] = (V[n - 1][m] * z0*(2.0*n - 1) - V[n - 2][m] * rho*(n + m - 1)) / (n - m);

			}

		for (int n = 0; n <= this->Ngf; n++)
			for (int m = 0; m <= n; m++)
			{
				dVz[n][m] = V[n + 1][m] * long double(-n + m - 1);

				if (m == 0)
				{
					dVx[n][m] = V[n + 1][1] * (-1.0);
					dVy[n][m] = V[n + 1][1].doti();
				}
				else
				{
					long double coef = long double((n - m + 2)*(n - m + 1)) / 2.0;
					dVx[n][m] = V[n + 1][m + 1] * (-0.5) + V[n + 1][m - 1] * coef;
					dVy[n][m] = (V[n + 1][m + 1] * 0.5).doti() + (V[n + 1][m - 1] * coef).doti();
				}
			}
	}
	void Cunningham::dCS_tide(double et, int IDtide, double  mu_tide)
	{

		//double lt, pos[3], P2[3];
		//spkgps_c(IDtide, et, "J2000", Global::IDC, pos, &lt);
		//triple P(pos);

		//P = trpos(et, 1, Global::IDC, P);
		//double r = P.getAbs();
		//double sinFi = P[2] / r;
		//double dxy = sqrt(P[0] * P[0] + P[1] * P[1]);
		//double lambda = atan2(P[1], P[0]);
		////запаздывание приливного горба
		//lambda = lambda - 5.0 / rad;

		//P[0] = (dxy*cos(lambda));
		//P[1] = (dxy*sin(lambda));

		//P2[0] = (3.*sinFi*sinFi - 1.) / 2.;
		//P2[1] = 3.*sinFi*sqrt(1. - sinFi*sinFi);
		//P2[2] = 3.*(1. - sinFi*sinFi);

		//double dC20 = this->k2*(mu_tide / Global::mu)*2.*pow(this->R0 / r, 3)*P2[0];
		//double dS20 = /*this->k2*(ID2GM(IDtide)/Global::mu)*2.*pow(this->R0/r,3)*P2[0];*/0.;

		//double dC21 = this->k2*(mu_tide / Global::mu) / 3.*pow(this->R0 / r, 3)*P2[1] * cos(lambda);
		//double dS21 = this->k2*(mu_tide / Global::mu) / 3.*pow(this->R0 / r, 3)*P2[1] * sin(lambda);

		//double dC22 = this->k2*(mu_tide / Global::mu) / 24.*pow(this->R0 / r, 3)*P2[2] * cos(2.*lambda);
		//double dS22 = this->k2*(mu_tide / Global::mu) / 24.*pow(this->R0 / r, 3)*P2[2] * sin(2.*lambda);

		//this->dCS[0].setNum(dC20, -dS20);
		//this->dCS[1].setNum(dC21, -dS21);
		//this->dCS[2].setNum(dC22, -dS22);
	}

	//ускорение от гармоник геопотенциала 
	triple Cunningham::getAcceleration(int IDC, long double et, triple pos)
	{
		triple posR = trpos(et, 1, IDC, pos);

		this->setPosition(posR);
		this->validdV();
		
		ComplexNum sumdVx(0., 0.);
		ComplexNum sumdVy(0., 0.);
		ComplexNum sumdVz(0., 0.);
#pragma region tide

	/*	if (this->tide_by_body == true) { dCS_tide(et, this->bodyID, this->mu_body); for (int i = 0; i < 3; i++) dCS_body[i] = dCS[i]; }
		if (this->tide_by_sun == true) { dCS_tide(et, 10, this->mu_sun);			 for (int i = 0; i < 3; i++) dCS_sun[i] = dCS[i]; }*/
		//n=1
//sumdVz = sumdVz + this->GravModel[0][0] * this->dVz[0][0];
//sumdVx = sumdVx + this->GravModel[0][0] * this->dVx[0][0];
//sumdVy = sumdVy + this->GravModel[0][0] * this->dVy[0][0];
//n=2 + приливы
//for (int i = 0; i < 3; i++) {
//	sumdVz = sumdVz + (this->GravModel[2][i] + this->dCS_sun[i] + this->dCS_body[i])*this->dVz[2][i];
//	sumdVx = sumdVx + (this->GravModel[2][i] + this->dCS_sun[i] + this->dCS_body[i])*this->dVx[2][i];
//	sumdVy = sumdVy + (this->GravModel[2][i] + this->dCS_sun[i] + this->dCS_body[i])*this->dVy[2][i];
//}
//n>2  
#pragma endregion

		for (int n = 0; n <= this->Ngf; n++) 
		{
			for (int m = 0; m <= n; m++)
			{
				sumdVz = sumdVz + this->GravModel[n][m] * this->dVz[n][m];
				sumdVx = sumdVx + this->GravModel[n][m] * this->dVx[n][m];
				sumdVy = sumdVy + this->GravModel[n][m] * this->dVy[n][m];
			}
		}

		triple accR;
		accR[0] = sumdVx.getReal();
		accR[1] = sumdVy.getReal();
		accR[2] = sumdVz.getReal();
		
		double R02 = R0*R0;
		accR *= (GM / R02);

		triple accI = trpos(et, IDC, 1, accR);

		return accI;

	}
}