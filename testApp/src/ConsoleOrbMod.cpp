#include"Control.h"

#include<iomanip>
#include<iostream>

using namespace OrbMod;
using namespace std;

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        cout << "Too few parameters to run the appliaction. Exit. "<<endl;
        return -1;
    }

    cout << "SPICE kernels loading: ";
    cout << Control::loadKernels(argv[1]) << endl;//"metak.tm"

    cout << "Observatories loading: ";
    cout << Control::loadObservatories(argv[2]) << endl;//"observatories.txt"

    cout << "Process started " << endl;
    Control::Process(argv[3]);//"OrbMod.ini"
    cout << "Process finished " << endl;

    system("pause");
    return 0;
}
