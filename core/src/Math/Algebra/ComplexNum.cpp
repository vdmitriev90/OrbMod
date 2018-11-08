#include "ComplexNum.h"
#include<iostream>

using namespace std;
//
namespace Algebra
{
	ComplexNum::ComplexNum(void)
	{
	}
	//
	ComplexNum::~ComplexNum(void)
	{
	}
	//
	void ComplexNum::setNum(long double re, long double im) {
		Re = re;
		Im = im;
	}
	ComplexNum ComplexNum::operator*(const ComplexNum &right) {
		ComplexNum res;
		res.Re = this->Re* right.Re - this->Im* right.Im;
		res.Im = this->Re* right.Im + this->Im* right.Re;
		return res;
	}
	ComplexNum ComplexNum::operator+(const ComplexNum &right) {
		ComplexNum res;
		res.Re = this->Re + right.Re;
		res.Im = this->Im + right.Im;
		return res;
	}

	ComplexNum ComplexNum::operator-(const ComplexNum &right) {
		ComplexNum res;
		res.Re = this->Re - right.Re;
		res.Im = this->Im - right.Im;
		return res;
	}

	ComplexNum ComplexNum::operator*(const long double &right) {
		ComplexNum res;
		res.Re = this->Re* right;
		res.Im = this->Im * right;
		return res;
	}
	ComplexNum ComplexNum::operator/(const ComplexNum &right) {
		ComplexNum res;
		res.Re = (this->Re*right.Re + this->Im*right.Im) / (right.Re*right.Re + right.Im*right.Im);
		res.Im = (this->Im*right.Re - this->Re*right.Im) / (right.Re*right.Re + right.Im*right.Im);
		return res;
	}


	ComplexNum ComplexNum::operator/(const long double &right) {
		ComplexNum res;
		res.Re = this->Re / right;
		res.Im = this->Im / right;
		return res;
	}
	ComplexNum ComplexNum::doti() {
		ComplexNum res;
		res.Re = -this->Im;
		res.Im = this->Re;
		return res;
	}
	ostream& operator<<(ostream& s, ComplexNum& p) {
		s << p.getReal() << " " << p.getIm();
		return s;
	}

}