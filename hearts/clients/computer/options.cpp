#include "options.h"

namespace {
	std::string name_ = "Killer Tomato";
}

std::string Options::name()
{
	return name_;
}

void Options::parse_args(char* argv[])
{
	for (unsigned i = 0; argv[i]; ++i)
	{
		if (std::string(argv[i]) == "--playername")
		{
			if (argv[i + 1]) name_ = argv[i + 1];
		}
	}
}

