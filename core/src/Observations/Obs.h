#pragma once
#include"Matrix.h"
#include"triple.h"
#include"Observatory.h"

namespace OrbMod
{
	class Obs
	{
	public:
		Obs();
		Obs(const Obs& other);
		virtual ~Obs();
		double t, dlt;
		Observatory observ;
		std::string  str_dbg;
		static  int compare(const Obs * a, const Obs * b);

		Algebra::triple getObsPos() const;
		
        virtual bool tryParce(std::string s) = 0;
		
        virtual void updateEquations(Algebra::Matrix &A, std::vector<double> &OmC, Algebra::Matrix &x, Algebra::Matrix &dxdx0, double  tau) = 0;
		
        virtual std::string getType() = 0;
		
        virtual Obs * clone() const = 0;

	protected:
		bool isOutl;
		virtual void writeResiduals() = 0;
		virtual bool isOutlier() { return false; };

	};
}
//
