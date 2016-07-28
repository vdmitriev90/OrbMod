#pragma once
#include "variables\var.h"
namespace OrbMod
{
	class var_3D_izo2 :
		public var_3D_izo
	{
	public:
		var_3D_izo2();
		~var_3D_izo2();
		vector<Matrix> Fi, SVi;
		void setPar(vector<double> &X, Matrix &SV, double t0) override;
		bool Inter(double s0, double H, vector<double> &X, vector<double> &Y) override;

	};
}

