// ConsoleOrbMod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"OrbModLib\src\stdafx.h"
using namespace OrbMod;
int main()
{
	Control::loadKernels("metak.tm");
	cout << "meta" << endl;
	Control::loadObservatories("observatories.txt");
	cout << "obs" << endl;
	Control::Process("OrbMod.ini");
}

