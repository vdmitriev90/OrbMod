#pragma once
#include "ModAstroObs.h"

using namespace Algebra;

namespace OrbMod
{
	class ModAstroObs2 :public AstroObs
	{
	public:
		ModAstroObs2();
		virtual ~ModAstroObs2();

		virtual bool tryParce(std::string s) override;
		virtual void setParEq(Matrix &A, vector<double> &OmC, Matrix &x, Matrix &dxdx0, double  tau) override;
		virtual string getType()override;
		virtual void writeRes()override;
		triple pos;
		triple posres;
	};
}
