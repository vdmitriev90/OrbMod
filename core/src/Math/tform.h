#pragma once
#include"Matrix.h"
#include"triple.h"

namespace OrbMod
{
    class tform
    {
    public:
        tform() {};
        ~tform() {};
        static void trpos(char * from, char *to, double t, Algebra::triple& in, Algebra::triple& out);
        static void trsvs(char * from, char * to, double t, Algebra::Matrix &SV);
    };

}