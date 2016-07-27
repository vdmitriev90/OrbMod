#pragma once
#include"stdafx.h"
namespace Algebra
{
	class ComplexNum {
	private:
		long double Re, Im;
	public:
		ComplexNum(void);
		~ComplexNum(void);

		ComplexNum(long double re, long double im) {
			Re = re;
			Im = im;
		}

		long double getReal() { return Re; };
		long double getIm() { return Im; };

		void setNum(long double re, long double im = 0.);
		ComplexNum operator*(const ComplexNum &right);
		ComplexNum operator+(const ComplexNum &right);
		ComplexNum operator-(const ComplexNum &right);
		ComplexNum operator*(const long double &right);
		ComplexNum operator/(const ComplexNum &right);
		ComplexNum operator/(const long double &right);
		ComplexNum doti();

		friend std::ostream& operator<<(std::ostream& s,
			ComplexNum &right);
	};
}
