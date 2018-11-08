#pragma once
#include "force.h"
#include "triple.h"
#include "Matrix.h"

namespace OrbMod
{
    class ForceIzo :
        public Force
    {
    protected:

        Algebra::Matrix dfdv, ddFdy, dFcbdx, dFnmdx, dF3bdx;

        //произодные от  вектора сотояния в KS переменных по ветору сотояния в прямоугольных координатах на t0
        Algebra::Matrix dYdy0;

        virtual Algebra::triple planet(int IDP) override;
        virtual Algebra::triple planet(int IDP, double mu) override;
        void	init_izo();
        void	merge_izo();
    public:
        ForceIzo();
        ForceIzo(const double &t, const  Algebra::triple &X, const Algebra::triple &V);
        ~ForceIzo();

        virtual Algebra::triple force_cb() override;

        void getdXdX0(const std::vector<double> &Xks, std::vector<double> &X3d);
        Algebra::Matrix	get_ddFdsv();
        Algebra::Matrix	get_dFcbdx();
    };

}