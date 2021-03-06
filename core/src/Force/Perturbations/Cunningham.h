#pragma once
#include"triple.h"
#include"ComplexNum.h"

#include<vector>

namespace OrbMod
{
	long double factorial(int N);
	long double dblefactorial(int N);

	class Cunningham
	{
	private:
		Algebra::triple r;
		std::vector<std::vector<Algebra::ComplexNum>> dVx, dVy, dVz, V;
		int Ngf;
		double GM;
		double R0;
		double k2;
		bool tide_by_sun;
		bool tide_by_body;
		int bodyID;

        std::vector<std::vector<Algebra::ComplexNum>>  GravModel;  //������������ C,-S 
		//�������� � �����. ���������� ���������� ���������� �� ������� �������
        Algebra::ComplexNum dCS_sun[3], dCS_body[3], dCS[3];
		double mu_body;
		double mu_sun;
		void dCS_tide(double et, int IDtide, double mu_tide);
		void init_poly(int N);

	public:
		Cunningham(void);
		~Cunningham(void);

		std::string FileModel = "";

		void setPosition(Algebra::triple pos) { r = pos; }
		void setTide(bool b_sun, bool b_body) { this->tide_by_sun = b_sun; this->tide_by_body = b_body; };
		void setTide_body(int ID) { this->bodyID = ID; };
		void setLove(double Love_number) { this->k2 = Love_number; };
		void set_Ngf(int Number_of_harm) { this->Ngf = Number_of_harm; }
		int get_Ngf() { return this->Ngf; };
		double getGM() { return(GM); }
		double getR0() { return(R0); }
		
		void LoadGravityModel(std::string str);

		Algebra::triple getAcceleration(int, long double, Algebra::triple);
	protected:
		void validdV();

	};
}