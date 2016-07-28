#pragma once
#include "variables\var.h"
namespace OrbMod
{
	class var_KS_izo2 :
		public var_KS_izo
	{
	public:
		vector<Matrix> Fi, SVi;
		var_KS_izo2();
		~var_KS_izo2();
		void setPar(vector<double> &X, Matrix &SV, double t0) override;
		bool Inter(double s0, double H, vector<double> &X, vector<double> &Y) override;

	};
}

