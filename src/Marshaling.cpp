#include "stdafx.h"
#include "Marshaling.h"


Marsh::Marsh(void)
{
}
Marsh::~Marsh(void)
{
}
char* Marsh::Str2Char(System::String^Str)
{
			System::IntPtr ptr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Str);
			 char * Chars = (char*)ptr.ToPointer();
			 return Chars;
};
System::String^ Marsh::Char2Str(const char* in)
{
				std::string str =  in;
				System::String^  Str = gcnew System::String(str.c_str());
				return Str;
};
System::String^ Marsh::s2S(std::string str)
{
				System::String^  Str = gcnew System::String(str.c_str());
				return Str;
};

std::string Marsh::S2s(System::String^Str)
{
	return (Marsh::Str2Char(Str));
};
