#include "SB.h"
namespace Algebra
{
	void SB::Init(triple &X, triple &V, double &mu, double &t0)
	{
		double r = X.getAbs();
		this->q = X;
		this->p = V*r;
		double v2 = V.getSq();
		double _mu = mu / r;
		this->a = X*(v2 - _mu) - (X*V)*V;
		this->h = 0.5*v2 - _mu;
		this->t = t0;
	}
	SB::SB()
	{
		p = q = a = triple::zero;
		h = t = 0;
	}
	SB::SB(double  SV[6], double mu, double t0)
	{
		triple x = triple(SV[0], SV[1], SV[2]);
		triple v = triple(SV[3], SV[4], SV[5]);
		Init(x, v, mu, t0);

	}
	SB::SB(Matrix &SV, double mu, double t0)
	{
		triple x = triple(SV(0, 0), SV(1, 0), SV(2, 0));
		triple v = triple(SV(3, 0), SV(4, 0), SV(5, 0));

		Init(x, v, mu, t0);
	}
	SB::SB(const vector<double> &X)
	{
		if (X.size() < 11) throw ("Can't construct SB: input vector too short");
		for (size_t i = 0; i < 3; i++)
		{
			this->q[i] = X[i];
			this->p[i] = X[i + 3];
			this->a[i] = X[i + 6];
		}
		this->h = X[9];
		this->t = X[10];
	}
	void SB::copyToVect(vector<double>& X)
	{
		if (X.size() < 11) throw ("Can't copy SB to vector: input/output vector too short");
		for (size_t i = 0; i < 3; i++)
		{
			X[i] = this->q[i];
			X[i + 3] = this->p[i];
			X[i + 6] = this->a[i];
		}
		X[9] = this->h;
		X[10] = this->t;
	}
	double SB::r()
	{
		return (q.getAbs());
	}
	triple SB::v()
	{
		double r = q.getAbs();
		return (p / r);
	}
	Matrix SB::SV3d()
	{
		Matrix sv3d(6, 1);
		triple x = this->q;
		triple v = this->v();
		for (int i = 0; i < 3; i++)
		{
			sv3d(i, 0) = x[i];
			sv3d(i + 3, 0) = v[i];
		}
		return sv3d;
	}
	//
	Matrix SB::dydY()
	{
		double r = q.getAbs();
		double r3 = r*r*r;
		Matrix A(6, 11), B2(3, 3);
		B2.Identy();
		B2 /= r;
		Matrix B1 = triple::xxt(this->p, this->q);
		B1 *= (-1 / r3);
		A(0, 0) = A(1, 1) = A(2, 2) = 1.0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				A(i + 3, j) = B1(i, j);
				A(i + 3, j + 3) = B2(i, j);
			}
		return A;
	}
	//
	Matrix SB::dYdy(double mu)
	{
		double r = q.getAbs();
		triple v = this->p / r;
		double v2 = v.getSq();

		double r3 = r*r*r;
		double mr3 = mu / r3;

		Matrix A(11, 6), B2(3, 3);
		A(0, 0) = A(1, 1) = A(2, 2) = 1.0;

		B2.Identy();

		Matrix B1 = triple::xxt(v, q);
		Matrix ax = mr3*triple::xxt(q, q) - triple::xxt(v, v) + (v2 - mu / r)*B2;
		Matrix av = 2.0*B1.Transpose() - B1 + (q *v)*B2;

		B2 *= r;
		B1 /= r;

		triple t1 = mr3*this->q;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				A(i + 3, j) = B1(i, j);
				A(i + 3, j + 3) = B2(i, j);
				A(i + 6, j) = ax(i, j);
				A(i + 6, j + 3) = av(i, j);
			}
			A(9, i) = t1[i];
			A(9, i + 3) = v[i];
		}
		return A;
	}
	SB::~SB()
	{
	}
}