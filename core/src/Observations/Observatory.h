#pragma once
#include"triple.h"

#include<vector>
#include<map>
#include<string>

namespace OrbMod
{
	class Observatory
	{
	public:
		Observatory();
		Observatory(const Observatory& obsy);

		~Observatory();
	public:
		//fields
		std::string  ID;
		Algebra::triple X;
		std::string Name;
		
		//methods
		bool tryParce(const std::string &str);

		static std::vector<Observatory> Obsrs;
		static std::map<std::string, Observatory> str2Obsy;
		static bool LoadObsrs(std::string FileName);
	};
}

