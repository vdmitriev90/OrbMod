#include "KS.h"
#include"macroses.h"
using namespace std;

namespace Algebra
{
#pragma region Constructors

	//
	KS::KS()
	{

	}
	//
	void KS::Init(triple X, triple V)
	{
		double r = X.getAbs();
		if (X[0] >= 0)
		{
			Q(0, 0) = sqrt((r + X[0]) / 2.0);
			Q(1, 0) = X[1] / (2.0*Q(0, 0));
			Q(2, 0) = X[2] / (2.0*Q(0, 0));
			Q(3, 0) = .0;
		}
		else
		{
			Q(1, 0) = sqrt((r - X[0]) / 2.0);
			Q(0, 0) = X[1] / (2.0*Q(1, 0));
			Q(2, 0) = .0;
			Q(3, 0) = X[2] / (2.0*Q(1, 0));
		}
		Matrix Mv = Matrix(3, 1);
		Mv(0, 0) = V[0];
		Mv(1, 0) = V[1];
		Mv(2, 0) = V[2];

		P = (this->B())*Mv;
	}

	KS::KS(triple X, triple V)
	{
		Init(X, V);
	}
	//
	KS::KS(double SV[])
	{
		triple x = triple(SV[0], SV[1], SV[2]);
		triple v = triple(SV[3], SV[4], SV[5]);
		Init(x, v);
	}
	//
	KS::KS(Matrix Q, Matrix P)
	{

		this->Q = Q;
		this->P = P;
	}
	//
	KS::KS(Matrix QP)
	{
		this->Q = QP.subMatrix(0, 4, 0, 1);
		this->P = QP.subMatrix(4, 4, 0, 1);
	}
	KS::KS(const vector<double> &QP)
	{
		for (int i = 0; i < 4; i++)
		{
			Q(i, 0) = QP[i];
			P(i, 0) = QP[i + 4];
		}
	}
#pragma endregion

	//
	double KS::r()
	{
		double R = SQR(Q(0, 0)) + SQR(Q(1, 0)) + SQR(Q(2, 0)) + SQR(Q(3, 0));
		return(R);
	}
	//
	Matrix KS::B()
	{
		Matrix B = Matrix(4, 3);
		B(0, 0) = Q(0, 0);	B(0, 1) = Q(1, 0);	B(0, 2) = Q(2, 0);

		B(1, 0) = -Q(1, 0);	B(1, 1) = Q(0, 0);	B(1, 2) = Q(3, 0);

		B(2, 0) = -Q(2, 0);	B(2, 1) = -Q(3, 0);	B(2, 2) = Q(0, 0);

		B(3, 0) = Q(3, 0);	B(3, 1) = -Q(2, 0);	B(3, 2) = Q(1, 0);

		return 2.0*B;

	}
	//
	triple KS::X()
	{
		Matrix X = 0.5*(this->B()).Transpose()*Q;
		return triple(X(0, 0), X(1, 0), X(2, 0));
	}
	//
	triple KS::V()
	{
		double r = this->r();

		Matrix V = (0.25 / r)*(this->B()).Transpose()*P;
		return triple(V(0, 0), V(1, 0), V(2, 0));
	}
	Matrix KS::SV3d()
	{
		Matrix sv3d(6, 1);
		triple x = this->X();
		triple v = this->V();
		for (int i = 0; i < 3; i++)
		{
			sv3d(i, 0) = x[i];
			sv3d(i + 3, 0) = v[i];
		}
		return sv3d;
	}
	

	//
	Matrix KS::Lam(triple F)
	{
		Matrix L = Matrix(4, 4);

		L(0, 0) = F[0];		L(0, 1) = F[1];		L(0, 2) = F[2];		L(0, 3) = .0;

		L(1, 0) = F[1];		L(1, 1) = -F[0];	L(1, 2) = .0;		L(1, 3) = F[2];

		L(2, 0) = F[2];		L(2, 1) = .0;		L(2, 2) = -F[0];	L(2, 3) = -F[1];

		L(3, 0) = .0;		L(3, 1) = F[2];		L(3, 2) = -F[1];	L(3, 3) = F[0];

		return 2.0*L;
	}
	//
	Matrix KS::dydY()
	{
		triple V = this->V();
		double r = this->r();
		Matrix BT = this->B().Transpose();
		Matrix P = Lam(V);

		Matrix B1 = BT;
		//Matrix B2 = Matrix(3, 4);
		Matrix B3 = (-0.25 / r)*BT*P;
		Matrix B4 = (0.25 / r)*BT;
		Matrix R(6, 10);

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 4; j++)
			{
				R(i, j) = B1(i, j);
				R(i + 3, j) = B3(i, j);
				R(i + 3, j + 4) = B4(i, j);
			}
		return R;
	}
	//
	Matrix KS::dYdy(double mu)
	{
		triple V = this->V();
		triple X = this->X();
		double r = X.getAbs();
		double r3 = r*r*r;

		Matrix B = this->B();
		Matrix P = Lam(V);

		Matrix B1 = (0.25 / r)*B;
		//Matrix B2 = Matrix(3, 4);
		Matrix B3 = (0.25 / r)*P*B;
		//Matrix B4 = B;
		triple B5 = X*(mu / r3);
		//B6=V

		Matrix R = Matrix(10, 6);

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
			{
				R(i, j) = B1(i, j);
				R(i + 4, j) = B3(i, j);
				R(i + 4, j + 3) = B(i, j);
			}
		for (int j = 0; j < 3; j++)
		{
			R(8, j) = B5[j];
			R(8, j + 3) = V[j];
		}
		return R;
	}
	//
	Matrix KS::Y0(double mu, double t0)
	{
		Matrix R = Matrix(10, 1);
		for (size_t i = 0; i < 4; i++)
		{
			R(i, 0) = Q(i, 0);
			R(i + 4, 0) = P(i, 0);
		}
		R(8, 0) = this->h0(mu);
		R(9, 0) = t0;

		return R;
	}
	//
	void KS::Y0(double mu, double t0, vector<double> &X)
	{
		for (size_t i = 0; i < 4; i++)
		{
			X[i] = Q(i, 0);
			X[i + 4] = P(i, 0);
		}
		X[8] = this->h0(mu);
		X[9] = t0;
	}
	//
	double KS::h0(double mu)
	{
		double v2 = this->V().getSq();
		double h = 0.5*v2 - mu / this->r();
		return h;
	}
	//
	KS::~KS()
	{
	}
}
