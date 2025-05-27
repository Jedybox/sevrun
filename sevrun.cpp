// sevrun.cpp : Defines the entry point for the application.
//

/*
	 _____ _____ __ __ _____ _____ _____
	|   __|   __|  |  |  __ |  |  |   | | SEVRUN tool for running local server
	|__   |   __|  |  |  | _|  |  | | | | version 1.0
	|_____|_____|\___/|__|__|\___/|_|___| https://github.com/Jedybox/sevrun

	* This file is part of the SEVRUN project.
*/

#include <windows.h>
#include <filesystem>
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
			std::cerr << "Error: Unknown argument '" << arg << "'" << std::endl;
			return 1;
		}
	}

	if ("help" == std::string(argv[1])) {
		PrintHelp();
		return 0;
	}

	// Get the directory of the executable
	char exepath[MAX_PATH];
	GetModuleFileNameA(NULL, exepath, MAX_PATH);
	std::filesystem::path exeDir = std::filesystem::path(exepath).parent_path();
	// Check if paths.json exists in the same directory as the executable
	std::string jsonPath = exeDir.string() + "\\paths.json";

	if (!std::filesystem::exists(jsonPath)) {
		std::cerr << "Error: paths.json not found in the executable directory." << std::endl;
		return 1;
	}

	if (!CheckJsonFile(jsonPath)) return 1;	

	return 0;
}