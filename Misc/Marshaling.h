#pragma once
class Marsh
{
public:
	static char* Str2Char(System::String^Str);
	static System::String^ Char2Str(const char*);
	static System::String^ s2S(std::string str);
	static std::string S2s(System::String^Str);
	Marsh(void);
	~Marsh(void);
};

