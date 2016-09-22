#pragma once

namespace OrbMod
{
	class tform
	{
	public:
		tform() {};
		~tform() {};
		static void trpos(char * from, char *to, double t, triple& in, triple& out);
		static void trsvs(char * from, char * to, double t, Matrix &SV);
	};

}