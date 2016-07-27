#include "stdafx.h"
#include "body.h"
//
using namespace std;
//
namespace OrbMod
{
	body::body()
	{
	}
	//
	body::~body()
	{
	}
	map<int, body> body::bodies;
	//
	bool body::tryParse(string str)
	{
		return true;
	}
	//
	int body::getID()
	{
		return ID;
	}
	//
	double body::getGM()
	{
		return GM;
	}
	//
	string body::getFrame()
	{
		return FRAME;
	}
}