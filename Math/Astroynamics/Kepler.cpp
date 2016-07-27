#include "stdafx.h"
#include "Kepler.h"
namespace OrbMod
{

	Kepler::Kepler()
	{
	}


	Kepler::~Kepler()
	{
	}
	//Convert true anomaly to eccentric
	double Kepler::True2Ecc(double TA, double ecc)
	{
		double use2 = (1.0 - ecc*ecc);
		double q = ecc / (1.0 + sqrt(use2));
		double Y = q*sin(TA);
		double X = 1.0 + q*cos(TA);

		double Ecc = TA - 2.0*atan(Y / X);
		return Ecc;
	}
	//Convert eccentric anomaly to mean
	double Kepler::Ecc2Mean(double Ecc, double ecc)
	{
		return(Ecc - ecc*sin(Ecc));
	}
	//Convert true anomaly to eccentric
	double Kepler::True2Mean(double TA, double ecc)
	{
		double Ecc = True2Ecc(TA, ecc);
		return Ecc2Mean(Ecc, ecc);
	}
	//решение ур-я Кеплера
	void Kepler::kepler(double M, double E, double &EX, double &TA)
	{
		double   F, F1, Ex0 = M, EXi;
		for (;;)
		{
			F = Ex0 - E*sin(Ex0) - M;
			F1 = 1.0 - E*cos(Ex0);
			EXi = Ex0 - F / F1;
			if (abs(Ex0 - EXi) < 1e-15) break;
			Ex0 = EXi;
		}

		EX = EXi;
		//double dTA = atan2(sqrt(1.0 - E*E)*sin(EXi), cos(EXi) - E);
		double sqE = SQR(E);
		TA = 2.0 * atan(sqrt((1.0 + sqE) / (1.0 - sqE))*tan(EXi / 2.0));
	}
	//
	/// <summary>
	/// перевычисление вектора состояния с эпохи tdb1 на эпоху tdb2 по формулам невозмущенного движения
	/// </summary>
	/// <param name="mu">GM центрального тела km^3 /sec^2 </param>
	/// <param name="sv1"> входной вектор состояния ( km, km /sec) в инерциальной системе координат на эпоху tdb1 </param>
	/// <param name="tdb1">эпоха TDB в секундах после J2000, соответствующая sv1 </param>
	/// <param name="tdb2">эпоха TDB в секундах после J2000, на которую нужно получить вектор состояния sv2 </param>
	/// <param name="sv2">выходной вектор состояния в инерциальной системе координат на эпоху tdb2</param>
	/// <returns>0, если вычисления завершены успешно, иначе 1</returns>
	int Kepler::PropSV(double mu, const double *sv1, double tdb1, double tdb2, double *sv2)
	{
		if (mu <= 0) return 1;
		if ((sv1[0] * sv1[0] + sv1[1] * sv1[1] + sv1[2] * sv1[2]) == 0) return 1;
		if ((sv1[3] * sv1[3] + sv1[4] * sv1[4] + sv1[5] * sv1[5]) == 0) return 1;

		double elts[8];
		oscelt_c(sv1, tdb1, mu, elts);
		conics_c(elts, tdb2, sv2);
		return 0;
	}
	//
	int Kepler::PropSV(double mu, const Matrix &SV1, double tdb1, double tdb2, Matrix &SV2)
	{
		double *sv1, sv2[6];
		SV1.ToOneDimArr(sv1);
		int j = PropSV(mu, sv1, tdb1, tdb2, sv2);
		SV2 = Matrix(sv2, 6, 1);
		delete[] sv1;
		return j;

	}
}