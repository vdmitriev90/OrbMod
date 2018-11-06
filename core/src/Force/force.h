#pragma once
#include <stdio.h>
#include"stdafx.h"

using namespace std;
namespace OrbMod
{
	class Force
	{
	protected:
		static double mu;
		static FILE *facc;

		triple X, V, acc;
		double time;
		virtual triple planet(int IDP);
		virtual triple planet(int IDP, double mu);
		triple acc5th_body();
		triple relativ();
		triple L_T();

	public:
		static void AccFileOpen();
		static void AccFileClose();
		static void setMu();
		static double getMu() { return mu; };
		static triple force_SODE(const double Ti, const triple &Xi, const triple &Vi);

		Force();
		Force(const double &t, const  triple &X, const triple &V);
		virtual ~Force();

		virtual triple force_cb();
		virtual triple force_pert();
		//
		void   force_w(double Ti);

	};
}