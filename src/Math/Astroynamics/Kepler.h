#pragma once

namespace OrbMod
{
	class Kepler
	{
	public:
		Kepler();
		~Kepler();

		//Convert true anomaly to eccentric
		static double  True2Ecc(double TA, double ecc);
		//Convert eccentric anomaly to mean
		static double  Ecc2Mean(double Ecc, double ecc);
		//Convert true anomaly to mean
		static double  True2Mean(double TA, double ecc);
		//solve kepler equation
		static void	 kepler(double M, double E, double &EX, double &TA);
		//propagate state from one epoch to another using equations of unperturbed motion
		static int PropSV(double mu, const double *sv1, double tdb1, double tdb2, double *sv2);
		//
		static int PropSV(double mu, const Matrix &sv1, double tdb1, double tdb2, Matrix &sv2);
	};
}