#pragma once
#include"Integrate.h"
#include"Matrix.h"

//class ivar;
namespace OrbMod
{
	class var_2D : public ivar {
	public:
		var_2D();
		virtual void setPar(std::vector<double> &X, Algebra::Matrix &mSV, double t0) override;
		virtual void GetX(const std::vector<double> &X, Algebra::Matrix &mSV, double t0, Algebra::Matrix &dXdX0)override;
		virtual void force(const double Ti, const std::vector<double> &X, std::vector<double> &dXds) override;
		virtual bool Inter(double t0, double H, std::vector<double> &X, std::vector<double> &Yo)override;
	};
	//
	class var_3D : public ivar {
	public:
		var_3D();
		virtual void setPar(std::vector<double> &X, Algebra::Matrix &mSV, double t0) override;
		virtual void GetX(const std::vector<double> &X, Algebra::Matrix &mSV, double t0, Algebra::Matrix &dXdX0)override;
		virtual void force(const double Ti, const std::vector<double> &X, std::vector<double> &dXds)override;
		virtual bool Inter(double t0, double H, std::vector<double> &X, std::vector<double> &Yo)override;
	};
	//
	class var_3D_izo : public var_3D {
	public:
		var_3D_izo();

		virtual void setPar(std::vector<double> &X, Algebra::Matrix &mSV, double t0)override;
		virtual void GetX(const std::vector<double> &X, Algebra::Matrix &mSV, double t0, Algebra::Matrix &dXdX0)override;
		virtual void force(const double Ti, const std::vector<double> &X, std::vector<double> &dXds)override;
	};
	//
	class var_KS : public ivar {
	public:
		var_KS();
		virtual void setPar(std::vector<double> &X,  Algebra::Matrix &mSV, double t0) override;
		virtual void GetX(const std::vector<double> &X, Algebra::Matrix &mSV, double t0, Algebra::Matrix &dXdX0)override;
		virtual void force(const double Ti, const std::vector<double> &X, std::vector<double> &dXds)override;
		virtual void endOfStep(double t0, double H, std::vector<double> &X, std::vector<double> &Y) override;
		virtual bool Inter(double t0, double H, std::vector<double> &X, std::vector<double> &Yo)override;
		void calcSV(double S, double t0, double tout, std::vector<double> &X, std::vector<double> &Y);
	};
	//
	class var_KS_izo : public var_KS {
	public:
		var_KS_izo();
		Algebra::Matrix dY0dy0;
		virtual void setPar(std::vector<double> &X, Algebra::Matrix &mSV, double t0)override;
		virtual void GetX(const std::vector<double> &X, Algebra::Matrix &mSV, double t0, Algebra::Matrix &dXdX0) override;
		virtual void force(const double Ti, const std::vector<double> &X, std::vector<double> &dXds)override;
		void getdXdX0(const std::vector<double> &X, Algebra::Matrix &Fi);
	};
	//
	class var_SB : public ivar {
	public:
		var_SB();
		virtual void setPar(std::vector<double> &X, Algebra::Matrix &mSV, double t0) override;
		virtual void GetX(const std::vector<double> &X, Algebra::Matrix &mSV, double t0, Algebra::Matrix &dXdX0)override;
		virtual void force(const double Ti, const std::vector<double> &X, std::vector<double> &dXds)override;
		virtual void endOfStep(double t0, double H, std::vector<double> &X, std::vector<double> &Y) override;
		virtual bool Inter(double t0, double H, std::vector<double> &X, std::vector<double> &Yo)override;
		void calcSV(double S, double t0, double tout, std::vector<double> &X, std::vector<double> &Y);
	};
	//
	class var_SB_izo : public var_SB {
	public:
		var_SB_izo();
		Algebra::Matrix dY0dy0;
		virtual void setPar(std::vector<double> &X, Algebra::Matrix &mSV, double t0) override;
		virtual void GetX(const std::vector<double> &X, Algebra::Matrix &mSV, double t0, Algebra::Matrix &dXdX0) override;
		virtual void force(const double Ti, const std::vector<double> &X, std::vector<double> &dXds) override;
		void getdXdX0(const std::vector<double> &X, Algebra::Matrix &Fi);
	};
}
 