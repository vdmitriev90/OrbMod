#pragma once
#include"Integrate.h"
using namespace std;
using namespace Algebra;

namespace OrbMod
{

	class var_2D : public ivar {
	public:
		var_2D();
		virtual void setPar(vector<double> &X, Matrix &mSV, double t0) override;
		virtual void GetX(vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0)override;
		virtual void force(const double Ti, const vector<double> &X, vector<double> &dXds) override;
		virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo, vector<double> &F0, vector<double> &P, vector< vector<double>> &B)override;
	};
	//
	class var_3D : public ivar {
	public:
		var_3D();
		virtual void setPar(vector<double> &X, Matrix &mSV, double t0) override;
		virtual void GetX(vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0)override;
		virtual void force(const double Ti, const vector<double> &X, vector<double> &dXds)override;
		virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo, vector<double> &F0, vector<double> &P, vector< vector<double>> &B)override;
	};
	//
	class var_3D_izo : public var_3D {
	public:
		var_3D_izo();

		virtual void setPar(vector<double> &X, Matrix &mSV, double t0)override;
		virtual void GetX(vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0)override;
		virtual void force(const double Ti, const vector<double> &X, vector<double> &dXds)override;
	};
	//
	class var_KS : public ivar {
	public:
		var_KS();
		virtual void setPar(vector<double> &X, Matrix &mSV, double t0) override;
		virtual void GetX(vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0)override;
		virtual void force(const double Ti, const vector<double> &X, vector<double> &dXds)override;
		virtual void endOfStep(double t0, double H, vector<double> &X, vector<double> &Y, vector<double> &F0, vector<double> &P, vector<vector<double>> &B) override;
		virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo, vector<double> &F0, vector<double> &P, vector< vector<double>> &B)override;
		void calcSV(double S, double t0, double tout, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Y);
	};
	//
	class var_KS_izo : public var_KS {
	public:
		var_KS_izo();
		Matrix dY0dy0;
		virtual void setPar(vector<double> &X, Matrix &mSV, double t0)override;
		virtual void GetX(vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0) override;
		virtual void force(const double Ti, const vector<double> &X, vector<double> &dXds)override;
		void getdXdX0(const vector<double> &X, Matrix &Fi);
	};
	//
	class var_SB : public ivar {
	public:
		var_SB();
		virtual void setPar(vector<double> &X, Matrix &mSV, double t0)override;
		virtual void GetX(vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0)override;
		virtual void force(const double Ti, const vector<double> &X, vector<double> &dXds)override;
		virtual void endOfStep(double t0, double H, vector<double> &X, vector<double> &Y, vector<double> &F0, vector<double> &P, vector<vector<double>> &B) override;
		virtual bool Inter(double t0, double H, vector<double> &X, vector<double> &Yo, vector<double> &F0, vector<double> &P, vector< vector<double>> &B)override;
		void calcSV(double S, double t0, double tout, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Y);
	};
	//
	class var_SB_izo : public var_SB {
	public:
		var_SB_izo();
		Matrix dY0dy0;
		virtual void setPar(vector<double> &X, Matrix &mSV, double t0) override;
		virtual void GetX(vector<double> &X, Matrix &mSV, double t0, Matrix &dXdX0) override;
		virtual void force(const double Ti, const vector<double> &X, vector<double> &dXds) override;
		void getdXdX0(const vector<double> &X, Matrix &Fi);
	};
}

 