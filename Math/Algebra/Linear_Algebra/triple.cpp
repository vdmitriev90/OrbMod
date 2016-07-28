#include "stdafx.h"
#include "triple.h"
namespace Algebra
{
	triple::triple()
	{
	}

	triple::~triple()
	{
	}
	const triple triple::zero = triple(.0, .0, .0);
	//
	double triple::getAbs() const
	{
		return sqrt(this->getSq());
	}
	//
	void triple::fromSph(double ra, double dec, double r)
	{
		this->a = r*cos(ra)*cos(dec);
		this->b = r*sin(ra)*cos(dec);
		this->c = r*sin(dec);
	}
	//
	double triple::getSq() const
	{
		return a*a + b*b + c*c;
	}
	triple  triple::norm()
	{
		double r = this->getAbs();
		return triple(a / r, b / r, c / r);
	}
	void triple::toSph(double &ra, double &dec, double &r)
	{
		r = this->getAbs();

		ra = atan2(this->b, this->a);
		ra = (ra >= 0) ? ra : ra + Consts::twopi;

		dec = atan(this->c / (sqrt(SQR(this->a) + SQR(this->b))));
	}
	std::string triple::toString(char* sep, char* format) const
	{
		string str = "";
		triple tr(this->a, this->b, this->c);
		for (int i = 0; i < 3; i++)
		{
			char buf[30];

			std::sprintf(buf, format, tr[i]);
			str += buf;
			str += sep;
		}
		return str;
	}
	std::string triple::toString(char* sep) const
	{
		return this->toString(sep, "%f");
	}
	//
	std::string triple::toString() const
	{
		return this->toString("\t", "%f");
	}
	//
	double  &triple::operator[](const int index)
	{
		switch (index)
		{
		case 0: return this->a;
			break;
		case 1: return this->b;
			break;
		case 2: return this->c;
			break;
		default:
			throw("triple: Index out of range exceptoin.");
			break;
		}
	}
	//
	triple operator+(const triple &left, const triple &right)
	{
		triple res;
		res.a = left.a + right.a;
		res.b = left.b + right.b;
		res.c = left.c + right.c;
		return res;
	}
	//
	triple operator-(const triple &left, const triple &right)
	{
		triple res;
		res.a = left.a - right.a;
		res.b = left.b - right.b;
		res.c = left.c - right.c;
		return res;
	}
	//
	triple operator*(const triple &left, const double &right)
	{
		triple res;
		res.a = left.a* right;
		res.b = left.b* right;
		res.c = left.c* right;
		return res;
	}
	//
	triple operator*(const double &left, const triple &right)
	{
		triple res;
		res.a = right.a* left;
		res.b = right.b* left;
		res.c = right.c* left;
		return res;
	}
	//
	triple triple::operator&(const triple &right)const
	{
		triple res;
		res.a = this->b*right.c - this->c*right.b;
		res.b = this->c*right.a - this->a*right.c;
		res.c = this->a*right.b - this->b*right.a;
		return res;
	}
	//
	double triple::operator*(const triple &right) const
	{
		double res;
		res = this->a*right.a + this->b*right.b + this->c*right.c;
		return res;
	}
	//
	triple triple::operator/(const double &right)
	{
		triple res;
		res.a = this->a / right;
		res.b = this->b / right;
		res.c = this->c / right;
		return res;
	}
	//
	triple triple::operator/(const triple &right)
	{
		triple res;
		res.a = this->a / right.a;
		res.b = this->b / right.b;
		res.c = this->c / right.c;
		return res;
	}
	//
	void triple::operator+=(const triple &right)
	{
		this->a = this->a + right.a;
		this->b = this->b + right.b;
		this->c = this->c + right.c;
	}
	//
	void triple::operator-=(const triple &right)
	{
		this->a = this->a - right.a;
		this->b = this->b - right.b;
		this->c = this->c - right.c;
	}
	//
	void triple::operator*=(const double &right)
	{
		this->a = this->a*right;
		this->b = this->b * right;
		this->c = this->c * right;
	}
	//
	void triple::operator/=(const double &right)
	{
		this->a = this->a / right;
		this->b = this->b / right;
		this->c = this->c / right;
	}
	//
	double triple::getAngle(const triple &a, const triple &b)
	{
		double angle, abs_a, abs_b, cos;
		triple C;

		abs_a = a.getAbs();
		abs_b = b.getAbs();
		cos = a*b / (abs_a*abs_b);

		angle = acos(cos);

		return angle;
	}
	//
	Matrix triple::xxt(triple &a, triple &b)
	{
		Matrix R(3, 3);
		int i = 0, j = 0;
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				R(i, j) = a[i] * b[j];
		return R;
	};
}