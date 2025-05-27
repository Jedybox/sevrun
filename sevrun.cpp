// sevrun.cpp : Defines the entry point for the application.
//

#include "sevrun.h"

using namespace std;


int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "Error: no valid argument" << std::endl;
		return 1;
	}

	for (const auto& arg : std::vector<std::string>(argv + 1, argv + argc)) {
		if (IsValidFlag(arg) || IsValidCommand(arg)) continue;
		else {
			std::cerr << "Error: Invalid argument '" << arg << "'" << std::endl;
			return 1;
		}
	}

	return 0;
}
