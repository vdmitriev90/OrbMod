#pragma once
//
using namespace std;
namespace OrbMod
{
	class body
	{
	public:
		body();
		~body();

	private:
		int ID;
		double GM;
		string FRAME = "";

	public:
		Cunningham Gfield;
		string Title = "";
		static map<int, body> bodies;
		bool tryParse(string str);

		int getID();
		double getGM();
		string getFrame();

	};
}

