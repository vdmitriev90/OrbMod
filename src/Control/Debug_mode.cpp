#include "stdafx.h"


using namespace std;
//
namespace OrbMod
{
	void  Control::debugAction1()
	{

		ofstream f;
		f.open("custom.out");
		OrbFit::fo.open("Orbfit.out");
		const int  NOR = Global::NOR;
		double to = Global::t0;
		double te = Global::te;
		double step = 0;
		//максимальное число итераций
		int NI = Global::Niter;
		//Output parameters
		int NS = 0, NBS = 0, Neq = 10, I = 0;
		vector<double> X0;
		vector<vector<double>> Xvar(21);

		Integration::Instance.SwitchVar(Variables::FODE_KS);
		Integration::Instance.setPar(X0, Global::SV, to);
		vector<double> Xi(X0), var(Neq);

		//вариации
		for (int i = 0; i < Neq; i++) var[i] = X0[i] * 0.01;
		var[3] = var[2];
		//первое интегрирование без вариаций
		Integration::Instance.Gauss_FODE(Xi, to, te, step, NOR, NI, NS, NBS);
		Xvar[0] = Xi;
		//+
		f << "Xvar\t" << Xvar.size() << endl;

		f << "varEq+\n";
		for (I = 1; I < Neq + 1; I++)
		{
			Xi = X0;
			Xi[I - 1] += var[I - 1];
			Integration::Instance.Gauss_FODE(Xi, to, te, step, NOR, NI, NS, NBS);
			Xvar[I] = Xi;
			f << Xvar[I].size() << endl;
		}

		//-
		f << "varEq-\n";
		for (I = Neq + 1; I < 2 * Neq + 1; I++)
		{
			Xi = X0;
			Xi[I - Neq - 1] -= var[I - Neq - 1];
			Integration::Instance.Gauss_FODE(Xi, to, te, step, NOR, NI, NS, NBS);
			Xvar[I] = Xi;
			f << Xvar[I].size() << endl;
		}
		f << setprecision(12);
		//
		Matrix M(Neq, Neq);
		for (int j = 0; j < Neq; j++)
			for (int k = 0; k < Neq; k++)
			{
				double p = (Xvar[j + 1][k] - Xvar[0][k]) / var[j];
				double m = (Xvar[0][k] - Xvar[j + 11][k]) / var[j];
				M(k, j) = (p + m) / 2.0;
			}
		f << "Xvar\n";
		for (int j = 0; j < 21; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				f << Xvar[j][k] << "\t";
			}
			f << "\n";
		}
		f << "Var\n";
		for (int k = 0; k < 10; k++)
			f << var[k] << "\t";
		f << "\n";
		f << "findiff\n" << M.toString("\t", "%e", 20, 1);
		Matrix dXdX0(Neq, Neq);

		Integration::Instance.SwitchVar(Variables::IZO_KS);
		Integration::Instance.setPar(X0, Global::SV, to);
		Integration::Instance.Gauss_FODE(X0, to, te, Global::step, NOR, NI, NS, NBS);
		dXdX0.setFromVec(Neq, X0);
		f << "varEq\n" << dXdX0.toString("\t", "%e", 20, 1);
		f.close();
		OrbFit::fo.close();
	}
	//
	void  Control::debugAction2()
	{
		OrbFit::fo.open("Orbfit.out");
		const int  NOR = Global::NOR;
		double to = Global::t0;
		double te = Global::te;
		double step = 0;

		//максимальное число итераций
		int NI = Global::Niter;

		//Output parameters
		int NS = 0, NBS = 0;
		int	Neq = 10, I = 0;
		vector<double> X0;

		var_KS_izo izoKS;
		double stept = 10;
		double tei = to + stept;
		Global::Discr = 0;

		while (tei < te)
		{

			Matrix dXdX0, SVks = Global::SV;
			//izoKS.setPar(X0, Global::SV, to);
			//int i = X0.size();
			//izoKS.Gauss_FODE(X0, to, tei, Global::step, NOR, NI, NS, NBS);
			//izoKS.GetX(X0, SVks, tei, dXdX0);
			//OrbFit::fo << "KS izo\n" << dXdX0.toString("\t", "%e", 20, 1);

			//izoKS.getdXdX0(X0, dXdX0);
			Integration::Instance.SwitchVar(Variables::IZO_KS);
			Integration::Instance.Integrate(SVks, to, tei, dXdX0);
			Matrix eltsKS = StVec(SVks, Force::getMu()).getOscEl(true);

			vector<double> X3d;
			var_3D_izo izo3D;
			Matrix dXdX03d, SV3d;
			izo3D.setPar(X3d, Global::SV, to);
			izo3D.Gauss_FODE(X3d, to, tei, Global::step, NOR, NI, NS, NBS);
			izo3D.GetX(X3d, SV3d, tei, dXdX03d);
			Matrix elts = StVec(SV3d, Force::getMu()).getOscEl(true);

			dXdX03d.setFromVec(6, X3d);
			//Matrix diff = dXdX03d - dXdX0;
			//OrbFit::fo << "3D izo\n" << dXdX03d.toString("\t", "%e", 20, 1);
			//OrbFit::fo << "diff\n" << (dXdX03d - dXdX0).toString("\t", "%e", 20, 1);
			//to = tei;
			string s_elst_ks = eltsKS.toString("\t", "%e", 20, 0);
			string s_elst_3d = elts.toString("\t", "%e", 20, 0);
			//string s_diff = diff.toString("\t", "%e", 20, 0);
			string s_dsv = (SV3d - SVks).toString("\t", "%e", 20, 0);

			OrbFit::fo << tei << "\t" << s_elst_ks << "\telts\t" << s_elst_3d << "\tdsv\t" << s_dsv << endl;
			tei += stept;
		}
		OrbFit::fo.close();
	}
	//
	void  Control::debugAction3()
	{
		//OrbFit::fo.open("Orbfit.out");
		//const int  NOR = Global::NOR;
		//double to = Global::t0;
		//double te = Global::te;
		//double step = 0;

		////максимальное число итераций
		//int NI = Global::Niter;
		////Output parameters
		//int NS = 0, NBS = 0;
		//int	Neq = 10, I = 0;
		//vector<double> X3d, X3ks;
		//Matrix dXdX03d, SV3d, dXdX0ks, SVks;

		//var_3D_izo2 izo3D;

		//izo3D.setPar(X3d, Global::SV, to);
		//OrbFit::fo << "izo3D\n" << Global::SV.toString("\t") << endl;
		//izo3D.Gauss_FODE(X3d, to, te, Global::step, NOR, NI, NS, NBS);
		//izo3D.GetX(X3d, SV3d, to, dXdX03d);

		//var_KS_izo2 izoKS;
		//izoKS.setPar(X3ks, Global::SV, to);
		//izoKS.Gauss_FODE(X3ks, to, te, step, NOR, NI, NS, NBS);
		//izoKS.GetX(X3ks, SVks, to, dXdX0ks);

		//double t = to;
		//for (size_t i = 0; i < izoKS.Fi.size(); i++)
		//{
		//	Matrix dizo = (izo3D.Fi[i] - izoKS.Fi[i]);

		//	string s_dsv = (izo3D.SVi[i] - izoKS.SVi[i]).toString("\t", "%e", 20, 1);
		//	string s_dizo = dizo.toString("\t", "%e", 20, 1);
		//	string s_izo3D = (izo3D.Fi[i]).toString("\t", "%e", 20, 1);
		//	string s_izoKS = (izoKS.Fi[i]).toString("\t", "%e", 20, 1);

		//	//OrbFit::fo << t <</* "\t" << s_dsv <<*/ "\n----------\ndizo\n" << s_dizo << "\tdsv\n" << s_dsv << endl;
		//	OrbFit::fo << "izo3D\n" << s_izo3D << endl;
		//	OrbFit::fo << "izoKS\n" << s_izoKS << endl;
		//	OrbFit::fo << "dizo\t" << s_dizo << endl;
		//	t += Global::Discr;
		//}
		//OrbFit::fo.close();
	}

	void Control::debugAction4()
	{
		OrbFit::fo.open("Orbfit.out");

		PreObrit::test();

		OrbFit::fo.close();
	}
}