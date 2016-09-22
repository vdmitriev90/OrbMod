#pragma once
#include "force.h"
namespace OrbMod
{
	class ForceIzo :
		public Force
	{
	protected:

		Matrix dfdv, ddFdy, dFcbdx, dFnmdx, dF3bdx;
		//произодные от  вектора сотояния в KS переменных по ветору сотояния в прямоугольных координатах на t0
		Matrix dYdy0;

		virtual triple planet(int IDP) override;
		virtual triple planet(int IDP, double mu) override;
		void	init_izo();
		void	merge_izo();
	public:
		ForceIzo();
		ForceIzo(const double &t, const  triple &X, const triple &V);
		~ForceIzo();

		virtual triple force_cb() override;

		void	getdXdX0(const vector<double> &Xks, vector<double> &X3d);
		Matrix	get_ddFdsv();
		Matrix	get_dFcbdx();
	};

}