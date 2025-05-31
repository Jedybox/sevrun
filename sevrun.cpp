// sevrun.cpp : Defines the entry point for the application.
//

/*
	 _____ _____ __ __ _____ _____ _____
	|   __|   __|  |  |  __ |  |  |   | | SEVRUN tool for running local server
	|__   |   __|  |  |  | -|  |  | | | | version 1.0
	|_____|_____|\___/|__|__|\___/|_|___| https://github.com/Jedybox/sevrun

	* This file is part of the SEVRUN project.
*/

#include <windows.h>
#include <filesystem>
#include "sevrun.h"

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "Error: no valid argument" << std::endl;
		return 1;
	}

	std::string command = std::string(argv[1]);

	if (!IsValidCommand(command)) {
		std::cerr << "Error: invalid command '" << command << "'" << std::endl;
		std::cerr << "Use 'sevrun help' to see the list of valid commands." << std::endl;
		return 1;
	}

	if ("help" == command) {
		PrintHelp();
		return 0;
	}

	if (!CheckJsonFile()) return 1;
	if ("add" == command) {
		if (argc < 5) {
			std::cerr << "Error: 'add' command requires a name, path, and a runner." << std::endl;
			return 1;
		}
		std::string pathName = argv[2];
		std::string pathAndFile = argv[3];
		std::string runner = argv[4];
		
		try {
			addPathToJson(pathAndFile, pathName, runner);
		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}

		return 0;
	}

	return 0;
}
