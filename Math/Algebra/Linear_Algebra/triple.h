#pragma once
#include"stdafx.h"
//#include"Matrix.h"

namespace Algebra
{
	class Matrix;
	class triple
	{
	private:
		double a, b, c;
	public:
		triple(void);
		~triple(void);
		triple(double x, double y, double z) {
			a = x;
			b = y;
			c = z;
		}
		triple(double X[3])
		{
			a = X[0];
			b = X[1];
			c = X[2];
		}
		void fromSph(double ra, double dec, double r);
		double getAbs() const;
		double getSq()const;
		triple norm();
		void toSph(double &ra, double &dec, double &r);

		std::string toString() const;
		std::string toString(char* sep) const;
		std::string toString(char* sep, char* format) const;

		double & operator[](const int index);
		//
		friend triple operator+(const triple &left, const triple &right);
		friend triple operator-(const triple &left, const triple &right);
		friend triple operator*(const triple &left, const double &right);
		friend triple operator*(const double &left, const triple &right);

		triple operator&(const triple &right)const;
		double operator*(const triple &right)const;

		triple operator/(const double &right);
		triple operator/(const triple &right);

		void operator/=(const double &right);
		void operator*=(const double &right);
		void operator-=(const triple &right);
		void operator+=(const triple &right);

		static triple const zero;
		static double getAngle(const triple &a, const triple &b);

		//внешенее произведение
		static Matrix xxt(triple &a, triple &b);
	};
}
