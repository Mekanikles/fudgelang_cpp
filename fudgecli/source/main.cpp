#include <iostream>
#include <string>
#include <vector>

#include "fudge/fudge.h"

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	std::vector<std::string> args(argv + 1, argv + argc);

	if (args.size() < 1)
	{
		std::cerr << "No input files specified" << std::endl;
		return -1;
	}

	for (auto& a : args)
		fudge::run_file(a);
}

///////////////////////////////////////////////////////////////////////////////
