#pragma once
#include "stdafx.h"
namespace OrbMod
{
	Derivatives::Derivatives()
	{
	};
	Derivatives::~Derivatives()
	{
	};
	//производные от вектра состояния по Элементам орбиты по Монтенбруку
	Matrix Derivatives::dSVdOscEl_Mont(double SV[6], double mu)
	{
		Matrix Out(6, 6), Out1(6, 6), PQW(3, 3), RzOm(3, 3), Rxi(3, 3), Rzw(3, 3), dXYZ_dAEM(3, 3), dXYZ_dOWI(3, 3), dVxVyVz_dAEM(3, 3), dVxVyVz_dOmWI(3, 3);
		triple dX_dAEM, dY_dAEM, dVX_dAEM, dVY_dAEM;
		double elts[8];
		oscelt_c(SV, 0, mu, elts);
		double e = elts[1];
		//функции эксцентриситета
		double e2 = e*e;
		double de2 = sqrt(1.0 - e2);
		double DE2 = de2*de2;

		//sma
		double a = elts[0] / (1.0 - e);

		double inc = elts[2];
		double Om = elts[3];
		double w = elts[4];
		double MA = elts[5];
		double TA = 0;
		double EA = 0;
		double X_, Y_, VX_, VY_;

		//Kepler equation
		Kepler::kepler(MA, e, EA, TA);
		double sEA = sin(EA);
		double cEA = cos(EA);
		double r = a*(1.0 - e*cEA);

		//Rotation
		RzOm.Rotate(Z, -Om);
		Rxi.Rotate(X, -inc);
		Rzw.Rotate(Z, -w);

		// Матрица перехода в орбитальную систему координат
		PQW = RzOm*Rxi*Rzw;
		triple P(PQW(0, 0), PQW(1, 0), PQW(2, 0));
		triple Q(PQW(0, 1), PQW(1, 1), PQW(2, 1));
		triple W(PQW(0, 2), PQW(1, 2), PQW(2, 2));
		triple N(cos(Om), sin(Om), 0.0);
		triple Ez(0.0, 0.0, 1.0);

		//радиус-вектор в орбитальной ситеме
		X_ = a*(cEA - e);
		Y_ = a*de2*sEA;
		VX_ = -sqrt(mu*a)*sEA / r;
		VY_ = sqrt(mu*a)*de2*cEA / r;
		//mean motion
		double n = sqrt(mu / (a*a*a));
		double adr = a / r;

		//dX dAEM
		dX_dAEM[0] = X_ / a;
		dY_dAEM[0] = Y_ / a;

		dX_dAEM[1] = -a - Y_*Y_ / (r*DE2);
		dY_dAEM[1] = X_*Y_ / (r*DE2);

		dX_dAEM[2] = VX_ / n;
		dY_dAEM[2] = VY_ / n;

		//dV dAEM
		dVX_dAEM[0] = -VX_ / (2.0*a);
		dVY_dAEM[0] = -VY_ / (2.0*a);

		dVX_dAEM[1] = VX_*adr*adr*(2.0*(X_ / a) + e*(Y_ / a)*(Y_ / a) / DE2);
		dVY_dAEM[1] = (n / de2)*adr*adr*(X_*X_ / r - Y_*Y_ / (a*DE2));

		dVX_dAEM[2] = -n*adr*adr*adr*X_;
		dVY_dAEM[2] = -n*adr*adr*adr*Y_;
		//dX dOmWI
		triple dP_dI, dP_dOm, dP_dw, dQ_dI, dQ_dOm, dQ_dw;

		dP_dI = W*sin(w);
		dP_dOm = Ez&P;
		dP_dw = Q*(-1.0);

		dQ_dI = W*cos(w);
		dQ_dOm = Ez&Q;
		dQ_dw = P*(-1.0);

		for (int i = 0; i < 3; i++)
		{
			dXYZ_dOWI(i, 0) = X_*dP_dw[i] + Y_*dQ_dw[i];
			dXYZ_dOWI(i, 1) = X_*dP_dw[i] + Y_*dQ_dw[i];
			dXYZ_dOWI(i, 2) = X_*dP_dI[i] + Y_*dQ_dI[i];

			dVxVyVz_dOmWI(i, 0) = VX_*dP_dw[i] + VY_*dQ_dw[i];
			dVxVyVz_dOmWI(i, 1) = VX_*dP_dw[i] + VY_*dQ_dw[i];
			dVxVyVz_dOmWI(i, 2) = VX_*dP_dI[i] + VY_*dQ_dI[i];

			for (int j = 0; j < 3; j++)
			{
				dXYZ_dAEM(i, j) = dX_dAEM[j] * PQW(i, 0) + dY_dAEM[j] * PQW(i, 1);
				dVxVyVz_dAEM(i, j) = dVX_dAEM[j] * PQW(i, 0) + dVY_dAEM[j] * PQW(i, 1);

				Out(i, j) = dXYZ_dOWI(i, j);
				Out(i, j + 3) = dXYZ_dAEM(i, j);
				Out(i + 3, j) = dVxVyVz_dOmWI(i, j);
				Out(i + 3, j + 3) = dVxVyVz_dAEM(i, j);
			}
		}
		for (int i = 0; i < 6; i++)
		{
			Out1(i, 0) = Out(i, 3);
			Out1(i, 1) = Out(i, 4);
			Out1(i, 2) = Out(i, 2);
			Out1(i, 3) = Out(i, 0);
			Out1(i, 4) = Out(i, 1);
			Out1(i, 5) = Out(i, 5);
		}

		return Out1;
	}
	//производные от вектра состояния по Элементам орбиты по Урмаеву
	Matrix	Derivatives::dSVdOscEl_Urm(double SV[6], double mu)
	{
		Matrix Out(6, 6), RzOm(3, 3), Rxi(3, 3), Rzw(3, 3), R(3, 3), RT(3, 3), dRTzdOm(3, 3), dRTxdi(3, 3), dRTzdw(3, 3), dRTdOm(3, 3), dRTdi(3, 3), dRTdw(3, 3);
		triple Xw, Vw, X, V;

		for (int i = 0; i < 3; i++)
		{
			X[i] = SV[i];
			V[i] = SV[i + 3];
		}
		double elts[8];
		oscelt_c(SV, 0, mu, elts);
		double e = elts[1];
		//функции эксцентриситета
		double e2 = e*e;
		double de2 = sqrt(1.0 - e2);
		double DE2 = de2*de2;

		//sma
		double a = elts[0] / (1.0 - e);

		double inc = elts[2];
		double Om = elts[3];
		double w = elts[4];
		double MA = elts[5];
		double TA = 0;
		double EA = 0;
		//Kepler equation
		Kepler::kepler(MA, e, EA, TA);
		double sEA = sin(EA);
		double cEA = cos(EA);
		double r = a*(1.0 - e*cEA);
		//mean motion
		double n = sqrt(mu / (a*a*a));
		double adr = a / r;

		//Rotation
		RzOm.Rotate(Axis::Z, Om);
		Rxi.Rotate(Axis::X, inc);
		Rzw.Rotate(Axis::Z, w);
		//`
		RT = RzOm*Rxi*Rzw;
		//RT = *RT;
		R = RT.Transpose();

		Xw = R*X;
		//Xw = RT*X;
		Vw = R*V;

		// dRz/dOm
		dRTzdOm(0, 0) = -sin(Om);	dRTzdOm(0, 1) = -cos(Om);	dRTzdOm(0, 2) = 0.0;
		dRTzdOm(1, 0) = cos(Om);	dRTzdOm(1, 1) = -sin(Om);	dRTzdOm(1, 2) = 0.0;
		dRTzdOm(2, 0) = 0.0;		dRTzdOm(2, 1) = 0.0;		dRTzdOm(2, 2) = 0.0;

		// dRx/di
		dRTxdi(0, 0) = 0.0;		dRTxdi(0, 1) = 0.0;				dRTxdi(0, 2) = 0.0;
		dRTxdi(1, 0) = 0.0;		dRTxdi(1, 1) = -sin(inc);		dRTxdi(1, 2) = -cos(inc);
		dRTxdi(2, 0) = 0.0;		dRTxdi(2, 1) = cos(inc);		dRTxdi(2, 2) = -sin(inc);

		// dRz/dw
		dRTzdw(0, 0) = -sin(w);		dRTzdw(0, 1) = -cos(w);		dRTzdw(0, 2) = 0.0;
		dRTzdw(1, 0) = cos(w);		dRTzdw(1, 1) = -sin(w);		dRTzdw(1, 2) = 0.0;
		dRTzdw(2, 0) = 0.0;			dRTzdw(2, 1) = 0.0;			dRTzdw(2, 2) = 0.0;

		// dRT/dOm
		dRTdOm = dRTzdOm*Rxi*Rzw;
		dRTdi = RzOm*dRTxdi*Rzw;
		dRTdw = RzOm*Rxi*dRTzdw;

		triple dXdOm, dXdi, dXdw, dVdOm, dVdi, dVdw;

		dXdOm = dRTdOm*Xw;
		dXdi = dRTdi*Xw;
		dXdw = dRTdw*Xw;

		dVdOm = dRTdOm*Vw;
		dVdi = dRTdi*Vw;
		dVdw = dRTdw*Vw;

		Matrix dXwdaeM(3, 3), dVwdaeM(3, 3);
		dXwdaeM(0, 0) = Xw[0] / a;				dXwdaeM(0, 1) = -a - Xw[1] * Xw[1] / (r*DE2);											dXwdaeM(0, 2) = Vw[0] / n;
		dXwdaeM(1, 0) = Xw[1] / a;				dXwdaeM(1, 1) = Xw[0] * Xw[1] / (r*DE2);												dXwdaeM(1, 2) = Vw[1] / n;
		dXwdaeM(2, 0) = 0.0;					dXwdaeM(2, 1) = 0.0;																	dXwdaeM(2, 2) = 0.0;

		dVwdaeM(0, 0) = -Vw[0] / (2.0* a);		dVwdaeM(0, 1) = Vw[0] * adr*adr*(2.0*Xw[0] / a + (e / DE2)*(Xw[1] / a)*(Xw[1] / a));	dVwdaeM(0, 2) = -n*adr*adr*adr*Xw[0];
		dVwdaeM(1, 0) = -Vw[1] / (2.0* a);		dVwdaeM(1, 1) = (n / de2)*adr*adr*(Xw[0] * Xw[0] / r - Xw[1] * Xw[1] / (a*DE2));		dVwdaeM(1, 2) = -n*adr*adr*adr*Xw[1];
		dVwdaeM(2, 0) = 0.0;					dVwdaeM(2, 1) = 0.0;																	dVwdaeM(2, 2) = 0.0;

		Matrix dXdaeM(3, 3), dVdaeM(3, 3);
		dXdaeM = RT*dXwdaeM;
		dVdaeM = RT*dVwdaeM;

		for (int i = 0; i < 3; i++)
		{
			Out(i, 0) = dXdaeM(i, 0);
			Out(i, 1) = dXdaeM(i, 1);
			Out(i, 2) = dXdi[i];
			Out(i, 3) = dXdOm[i];
			Out(i, 4) = dXdw[i];
			Out(i, 5) = dXdaeM(i, 2);
			Out(i + 3, 0) = dVdaeM(i, 0);
			Out(i + 3, 1) = dVdaeM(i, 1);
			Out(i + 3, 2) = dVdi[i];
			Out(i + 3, 3) = dVdOm[i];
			Out(i + 3, 4) = dVdw[i];
			Out(i + 3, 5) = dVdaeM(i, 2);
		}
		return Out;
	}

	//производные от вектора прямоугольных координат по сферическим
	Matrix Derivatives::dNEUdDAzEl(triple DAzEl)
	{
		double R = DAzEl[0];
		double Az = DAzEl[1];
		double El = DAzEl[2];

		Matrix M(3, 3);
		M(0, 0) = cos(El)*cos(Az);;
		M(1, 0) = cos(El)*sin(Az);
		M(2, 0) = sin(El);

		M(0, 1) = -R*cos(El)*sin(Az);
		M(1, 1) = -R*cos(El)*cos(Az);
		M(2, 1) = 0.0;

		M(0, 2) = -R*sin(El)*cos(Az);
		M(1, 2) = -R*sin(El)*sin(Az);
		M(2, 2) = R*cos(El);


		return M;

	};
	Matrix Derivatives::dXYZdBLH(triple BLH)
	{
		Matrix Mat(3, 3);
		double B = BLH[0];
		double L = BLH[1];
		double H = BLH[2];
		double a = 6378137.0;
		double f = 1.0 / 298.257223563;
		double e2 = f*(2.0 - f);

		double Z = sqrt(1.0 - e2*sin(B)*sin(B));
		double N = a / Z;
		double M = N*(1.0 - e2) / (Z*Z);

		Mat(0, 0) = -(M + H)*sin(B)*cos(L); Mat(0, 1) = (N + H)*cos(B)*sin(L);	Mat(0, 2) = cos(B)*cos(L);
		Mat(1, 0) = -(M + H)*sin(B)*sin(L); Mat(1, 1) = (N + H)*cos(B)*cos(L);	Mat(1, 2) = cos(B)*sin(L);
		Mat(2, 0) = (M + H)*cos(B);			Mat(2, 1) = 0.0;					Mat(2, 2) = sin(B);

		return Mat;

	}
}