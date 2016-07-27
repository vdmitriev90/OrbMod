#pragma once
using namespace std;
#include"stdafx.h"
namespace Algebra
{
	class KS
	{
	private:
		//initializer
		void Init(triple X, triple V);

	public:
		//4-вектор положения
		Matrix Q = Matrix(4, 1);

		//4-вектор скорости
		Matrix P = Matrix(4, 1);

		//конструкторы
		KS();
		KS(triple X, triple V);
		KS(double SV[]);
		KS(const vector<double> &X);
		KS(Matrix Q, Matrix P);
		KS(Matrix QP);

		//деструктор
		~KS();
		//
		Matrix B();
		triple  X();
		triple  V();
		Matrix SV3d();
		double* KS::getSVxy();

		double r();
		Matrix dydY();
		Matrix dYdy(double mu);
		Matrix Y0(double mu, double t0);
		void   Y0(double mu, double t0, vector<double> &X);
		double h0(double mu);

		static Matrix Lam(triple Tri);

	};

}