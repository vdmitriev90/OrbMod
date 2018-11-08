#include "AtmosphericDrag.h"
#include "Global.h"
#include "frame.h"

#include "SpiceUsr.h"

#include<fstream>

using namespace std;
using namespace Algebra;

namespace OrbMod
{
    AtmosphericDrag::AtmosphericDrag(void) {}
    AtmosphericDrag::~AtmosphericDrag(void) {}

    double AtmosphericDrag::Catm;
    double AtmosphericDrag::H;
    double AtmosphericDrag::Massa;
    double AtmosphericDrag::ro_0;
    double AtmosphericDrag::Area;
    double AtmosphericDrag::Peri;
    vector<double> AtmosphericDrag::AtmModel_Dens;
    vector<double> AtmosphericDrag::AtmModel_H;

    void AtmosphericDrag::setEarthAtmModel(char* str)
    {
        char buf[400];
        double H;
        double Dens;
        string s;
        std::ifstream fi;
        fi.open(str, ios::in);
        fi.getline(buf, 400);
        fi.getline(buf, 400);
        while (!fi.eof())
        {
            fi >> H;
            AtmosphericDrag::AtmModel_H.push_back(H);

            for (int i = 0; i < 5; i++) fi >> s;
            fi >> Dens;
            AtmosphericDrag::AtmModel_Dens.push_back(Dens);
        }

    };

    triple AtmosphericDrag::getAcc(double t)
    {
        double ro;
        bool a = true;
        size_t size = AtmModel_H.size();
        double pos399[3];
        double lt;
        spkgps_c(399, t, "J2000", 10, pos399, &lt);
        triple r399 = triple(pos399);
        triple rz = r - r399;

        if (a == true) {
            double 	H = rz.getAbs() - 6371.0;
            if (H > AtmModel_H[size - 1]) return triple::zero;

            for (int i = 1; i < size; i++) {
                if (AtmModel_H[i - 1]<H && AtmModel_H[i]>H)
                {
                    ro = AtmModel_Dens[i - 1] + (AtmModel_Dens[i] - AtmModel_Dens[i - 1]) / (AtmModel_H[i] - AtmModel_H[i - 1])*(H - AtmModel_H[i - 1]);
                }
            }

        }

        else
        {
            //высота над перицентром(перцентр эпохи t0)
            double h = r.getAbs() - Peri;
            ro = ro_0 * exp(-h / H);
        }
        //скорость относительно атмосферы
        triple w = triple(0.0, 0.0, Global::oz);
        w = trpos(t, Global::IDC, 1, w);
        triple Vatm;
        Vatm = w & r;
        triple Vrel = v - Vatm;

        //возм. ускорение вызванное атмосферным торможением.
        double K = -Catm * Area*ro*Vrel.getAbs()*1e+3 / (2.0*Massa);
        //fprintf(f,"%f %e %e\n",h,ro,K);
        //fclose(f);
        triple acc = Vrel * K;

        return(acc);

    };
}