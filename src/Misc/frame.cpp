#include "stdafx.h"
#include "frame.h"
namespace OrbMod
{
	triple trpos(SpiceDouble et, long int from, long int to, triple xin) {

		SpiceDouble Xin[3], Xout[3];

		Xin[0] = xin[0];
		Xin[1] = xin[1];
		Xin[2] = xin[2];


		SpiceChar   namefrom[60], nameto[60];
		SpiceDouble rotate[3][3];
		long int idfrom = id2fixfr(from);
		long int idto = id2fixfr(to);

		frmnam_c(idfrom, 60, namefrom);
		frmnam_c(idto, 60, nameto);
		//transformation matrix
		pxform_c(namefrom, nameto, et, rotate);

		mxv_c(rotate, Xin, Xout);

		triple xout(Xout[0], Xout[1], Xout[2]);
		//printf("xin %e %e %e\n", xout[0], xout.getY(), xout.getZ());
		return(xout);
	};

	void trpos(SpiceDouble et, long int from, long int to, SpiceDouble Xin[3], SpiceDouble Xout[3]) {

		SpiceChar               namefrom[60], nameto[60];
		SpiceDouble rotate[3][3];
		long int idfrom = id2fixfr(from);
		long int idto = id2fixfr(to);

		frmnam_c(idfrom, 60, namefrom);
		frmnam_c(idto, 60, nameto);
		//transformation matrix
		pxform_c(namefrom, nameto, et, rotate);

		mxv_c(rotate, Xin, Xout);
	};

	void trsv(SpiceDouble et, long int from, long int to, triple xin, triple vin, triple &xout, triple &vout) {

		SpiceDouble Xin[6], Xout[6];

		Xin[0] = xin[0];
		Xin[1] = xin[1];
		Xin[2] = xin[2];
		Xin[3] = vin[0];
		Xin[4] = vin[1];
		Xin[5] = vin[2];

		SpiceChar   namefrom[60], nameto[60];
		SpiceDouble rotate[6][6];
		long int idfrom = id2fixfr(from);
		long int idto = id2fixfr(to);

		frmnam_c(idfrom, 60, namefrom);
		frmnam_c(idto, 60, nameto);

		sxform_c(namefrom, nameto, et, rotate);
		mxvg_c(rotate, Xin, 6, 6, Xout);

		xout = triple::triple(Xout[0], Xout[1], Xout[2]);
		vout = triple::triple(Xout[3], Xout[4], Xout[5]);
	};
	void trsv(SpiceDouble et, long int from, long int to, SpiceDouble Xin[6], SpiceDouble Xout[6]) {

		SpiceChar   namefrom[60], nameto[60];
		SpiceDouble rotate[6][6];
		long int idfrom = id2fixfr(from);
		long int idto = id2fixfr(to);

		frmnam_c(idfrom, 60, namefrom);
		frmnam_c(idto, 60, nameto);

		sxform_c(namefrom, nameto, et, rotate);

		mxvg_c(rotate, Xin, 6, 6, Xout);

	};
	void trsv_NR(SpiceDouble et, long int from, long int to, SpiceDouble Xin[6], SpiceDouble Xout[6]) {

		SpiceChar   namefrom[60], nameto[60];
		SpiceDouble rotate[6][6];
		long int idfrom = id2fixfr(from);
		long int idto = id2fixfr(to);

		frmnam_c(idfrom, 60, namefrom);
		frmnam_c(idto, 60, nameto);

		sxform_c(namefrom, nameto, et, rotate);
		for (int i = 3; i < 6; i++) for (int j = 0; j < 3; j++) rotate[i][j] = 0.0;
		mxvg_c(rotate, Xin, 6, 6, Xout);

	};
	void trsv_pl(SpiceDouble et, long int from, long int to, SpiceDouble Xin[6], SpiceDouble Xout[6]) 
	{

		SpiceDouble Xfix[6];
		SpiceDouble poss[6];
		double valPM[3];
		SpiceInt dim;
		SpiceDouble lt1, dlt;
		SpiceDouble poleIAU[3] = { 0,0,1.0 };
		triple  Zeq = triple(0, 0, 1.0);
		triple Zorb, Node;
		SpiceDouble poleJ[3];
		SpiceChar   nameto[60], id[20];
		SpiceDouble M[3][3], Mtr[3][3];
		long int idto = id2fixfr(to);
		SpiceDouble Z[3], Zpl[3], N[3], Npl[3];

		frmnam_c(idto, 60, nameto);

		FILE*f = fopen("test.txt", "a");

		trsv(et, from, to, Xin, Xfix);


		spkacs_c(Global::IDC, et, "J2000", "NONE", 10, poss, &lt1, &dlt);
		pxform_c("J2000", nameto, et, M);
		xpose_c(M, Mtr);


		triple Xv = triple(poss[0], poss[1], poss[2]);

		triple Vv = triple(poss[3], poss[4], poss[5]);

		Zorb = Xv&Vv / (Xv.getAbs()*Vv.getAbs());


		Z[0] = Zorb[0];
		Z[1] = Zorb[1];
		Z[2] = Zorb[2];

		mxvg_c(M, Z, 3, 3, Zpl);
		mxvg_c(Mtr, poleIAU, 3, 3, poleJ);

		triple ZorbP = triple(Zpl);
		triple ZeqP = triple(poleJ);

		Node = ZorbP&ZeqP / (ZorbP.getAbs()*ZeqP.getAbs());

		N[0] = Node[0];
		N[1] = Node[1];
		N[2] = Node[2];
		mxvg_c(M, N, 3, 3, Npl);

		SpiceDouble S = atan2(Npl[1], Npl[0]);
		if (S < 0.0)  S = S + 2.0*pi;

		_itoa(Global::IDC, id, 10);
		bodvrd_c(id, "PM", 3, &dim, valPM);
		double oz = valPM[1] / rad / 24.0 / 3600.0;
		fprintf(f, "%f %f %f %f\n", Npl[0], Npl[1], Npl[2], S*rad);

		//------------------|Матрица преобразования координат|---------------------------------------------------------------------
		SpiceDouble R[6][6];

		R[0][0] = cos(S);     R[0][1] = -sin(S);     R[0][2] = 0.0; R[0][3] = 0.0;    R[0][4] = 0.0;     R[0][5] = 0.0;
		R[1][0] = sin(S);	  R[1][1] = cos(S);      R[1][2] = 0.0; R[1][3] = 0.0;    R[1][4] = 0.0;     R[1][5] = 0.0;
		R[2][0] = 0.0;		  R[2][1] = 0.0;         R[2][2] = 1.0; R[2][3] = 0.0;    R[2][4] = 0.0;     R[2][5] = 0.0;
		R[3][0] = -oz*sin(S); R[3][1] = -oz* cos(S);  R[3][2] = 0.0; R[3][3] = cos(S); R[3][4] = -sin(S); R[3][5] = 0.0;
		R[4][0] = oz*cos(S);  R[4][1] = -oz*sin(S);   R[4][2] = 0.0; R[4][3] = sin(S); R[4][4] = cos(S);	 R[4][5] = 0.0;
		R[5][0] = 0.0;		  R[5][1] = 0.0;         R[5][2] = 0.0; R[5][3] = 0.0;    R[5][4] = 0.0;     R[5][5] = 1.0;
		/*
				R[0][0] = cos(S);     R[0][1] = sin(S);     R[0][2] = 0.0; R[0][3] = 0.0;    R[0][4] = 0.0;     R[0][5] = 0.0;
				R[1][0] = -sin(S);	  R[1][1] = cos(S);      R[1][2] = 0.0; R[1][3] = 0.0;    R[1][4] = 0.0;     R[1][5] = 0.0;
				R[2][0] = 0.0;		  R[2][1] = 0.0;         R[2][2] = 1.0; R[2][3] = 0.0;    R[2][4] = 0.0;     R[2][5] = 0.0;
				R[3][0] = -oz*sin(S); R[3][1] =-oz* cos(S);  R[3][2] = 0.0; R[3][3] = cos(S); R[3][4] = sin(S); R[3][5] = 0.0;
				R[4][0] = -oz*cos(S);  R[4][1] =-oz*sin(S);   R[4][2] = 0.0; R[4][3] = -sin(S); R[4][4] = cos(S);	 R[4][5] = 0.0;
				R[5][0] = 0.0;		  R[5][1] = 0.0;         R[5][2] = 0.0; R[5][3] = 0.0;    R[5][4] = 0.0;     R[5][5] = 1.0;*/
				//-------------------------------------------------------------------------------------------------------------------------

		mxvg_c(R, Xfix, 6, 6, Xout);

		fclose(f);
	};

	/*
			R[0][0] = cos(S);     R[0][1] = sin(S);     R[0][2] = 0.0; R[0][3] = 0.0;    R[0][4] = 0.0;     R[0][5] = 0.0;
			R[1][0] = -sin(S);	  R[1][1] = cos(S);      R[1][2] = 0.0; R[1][3] = 0.0;    R[1][4] = 0.0;     R[1][5] = 0.0;
			R[2][0] = 0.0;		  R[2][1] = 0.0;         R[2][2] = 1.0; R[2][3] = 0.0;    R[2][4] = 0.0;     R[2][5] = 0.0;
			R[3][0] = -oz*sin(S); R[3][1] =-oz* cos(S);  R[3][2] = 0.0; R[3][3] = cos(S); R[3][4] = sin(S); R[3][5] = 0.0;
			R[4][0] = -oz*cos(S);  R[4][1] =-oz*sin(S);   R[4][2] = 0.0; R[4][3] = -sin(S); R[4][4] = cos(S);	 R[4][5] = 0.0;
			R[5][0] = 0.0;		  R[5][1] = 0.0;         R[5][2] = 0.0; R[5][3] = 0.0;    R[5][4] = 0.0;     R[5][5] = 1.0;*/
}