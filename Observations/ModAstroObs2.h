#pragma once
#include "ModAstroObs.h"

using namespace Algebra;

namespace OrbMod
{
	class ModAstroObs2 :public AstroObs
	{
	public:
		ModAstroObs2();
		ModAstroObs2(const ModAstroObs2& otr);

		//fields
		triple pos;
		triple posres;

		//methods
		virtual ~ModAstroObs2();
		virtual bool tryParce(std::string s) override;
		virtual void setParEq(Matrix &A, vector<double> &OmC, Matrix &x, Matrix &dxdx0, double  tau) override;
		virtual string getType()override;
		virtual void writeRes()override;
		virtual ModAstroObs2* clone() const override;

	};
}
