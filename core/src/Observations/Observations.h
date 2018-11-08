#pragma once
#include"Matrix.h"
#include"triple.h"
#include"Observatory.h"
#include<memory>


namespace OrbMod
{
    class Observations;
    typedef std::shared_ptr<Observations> obs_ptr;

	class Observations
	{
	public:
		Observations();
		Observations(const Observations& other);
		virtual ~Observations();
		double t, dlt;
		Observatory observ;
		std::string  str_dbg;
		static int compare(const obs_ptr& a, const obs_ptr&  b);

		Algebra::triple getObsPos() const;
		
        virtual bool tryParce(std::string s) = 0;
		
        virtual void updateEquations(Algebra::Matrix &A, std::vector<double> &OmC, Algebra::Matrix &x, Algebra::Matrix &dxdx0, double  tau) = 0;
		
        virtual std::string getType() = 0;
		
        virtual obs_ptr clone() const = 0;

	protected:
		bool isOutl;

		virtual void writeResiduals() = 0;
		
        virtual bool isOutlier() { return false; };

	};
}
//
