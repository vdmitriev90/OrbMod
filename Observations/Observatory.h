#pragma once
namespace OrbMod
{
	class Observatory
	{
	public:
		Observatory();
		~Observatory();
	public:
		std::string  ID;
		triple X;
		std::string Name;
		bool tryParce(const string &str);
		static vector<Observatory> Obsrs;
		static map<string, Observatory> str2Obsy;

		static bool LoadObsrs(std::string FileName);
	};
}

