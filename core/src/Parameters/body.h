#pragma once
#include"Cunningham.h"
#include<map>

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
		std::string FRAME = "";

	public:
		Cunningham Gfield;
        std::string Title = "";
		static std::map<int, body> bodies;
		bool tryParse(const std::string & str);

		int getID();
		double getGM();
        std::string getFrame();

	};
}

