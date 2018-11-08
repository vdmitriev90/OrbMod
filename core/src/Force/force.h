#pragma once
#include "triple.h"

#include <stdio.h>

namespace OrbMod
{
	class Force
	{
	protected:
		static double mu;
		static FILE *facc;

		Algebra::triple X, V, acc;
		double time;
		virtual Algebra::triple planet(int IDP);
		virtual Algebra::triple planet(int IDP, double mu);
		Algebra::triple acc5th_body();
		Algebra::triple relativ();
		Algebra::triple L_T();

	public:
		static void AccFileOpen();
		static void AccFileClose();
		static void setMu();
		static double getMu() { return mu; };
		static Algebra::triple force_SODE(const double Ti, const Algebra::triple &Xi, const Algebra::triple &Vi);

		Force();
		Force(const double &t, const  Algebra::triple &X, const Algebra::triple &V);
		virtual ~Force();

		virtual Algebra::triple force_cb();
		virtual Algebra::triple force_pert();
		//
		void   force_w(double Ti);

	};
}