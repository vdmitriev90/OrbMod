#include"Control.h"

#include<iomanip>
#include<iostream>

using namespace OrbMod;
using namespace std;

int main()
{
	Control::loadKernels("metak.tm");
	cout << "meta" << endl;
	Control::loadObservatories("observatories.txt");
	cout << "obs" << endl;
	Control::Process("OrbMod.ini");
}
