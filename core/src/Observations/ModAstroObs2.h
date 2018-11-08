#pragma once
#include "AstroObs.h"
#include"Matrix.h"
#include"triple.h"
using namespace Algebra;

namespace OrbMod
{
    class ModAstroObs2 :public AstroObs
    {
    public:
        ModAstroObs2();
        ModAstroObs2(const ModAstroObs2& otr);

        //fields
        Algebra::triple pos;
        Algebra::triple posres;

        //methods
        virtual ~ModAstroObs2();
        virtual bool tryParce(std::string s) override;
        virtual void updateEquations(Algebra::Matrix &A, std::vector<double> &OmC, Algebra::Matrix &x, Algebra::Matrix &dxdx0, double  tau) override;
        virtual std::string getType()override;
        virtual void writeResiduals()override;
        virtual obs_ptr clone() const override;

    };
}
