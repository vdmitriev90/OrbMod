#include"Control.h"

#include<iomanip>
#include<iostream>

using namespace OrbMod;
using namespace std;

int main(char ** args)
{
    cout << "SPICE kernels loading: ";
    cout << Control::loadKernels(args[0]) << endl;//"metak.tm"

    cout << "Observatories loading: ";
    cout << Control::loadObservatories(args[1]) << endl;//"observatories.txt"

    cout << "Process started " << endl;
    Control::Process(args[2]);//"OrbMod.ini"
    cout << "Process finished " << endl;

    system("pause");
}
