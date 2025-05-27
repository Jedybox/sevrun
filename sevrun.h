// sevrun.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <fstream>
#include "json.hpp"
#include <iostream>
#include <string>
#include <vector>

#ifndef FLAGS_H
#define FLAGS_H 
// Define flags for the application
const std::vector<std::string> flags = { "-s","-v",};
#endif

#ifndef COMMANDS_H
#define COMMANDS_H
// Define commands for the application
const std::vector<std::string> commands = { "help", "serve", "add", "rename", "redi", "remove", "list"};
#endif

#ifndef ISVALID_COMMAND_FUNC
#define ISVALID_COMMAND_FUNC
// Function to check if a command is valid
bool IsValidCommand(const std::string& command) {
	for (const auto& cmd : commands) if (cmd == command) return true;
	return false;
}
#endif

#ifndef ISVALID_FLAG
#define ISVALID_FLAG
/*
	* Function to check if a flag is valid
	* This function checks if the provided flag is in the predefined list of flags.
	* It returns true if the flag is valid, otherwise false.
	*
	* @param flag The flag to check.
	* @return True if the flag is valid, false otherwise.
*/
bool IsValidFlag(const std::string& flag) {
	for (const auto& f : flags) if (f == flag) return true;
	return false;
}
#endif

#ifndef PRINT_HELP
#define PRINT_HELP
/*
	* Function to print help information
	* This function prints the usage instructions, available commands, and flags for the application.
	*/
void PrintHelp() {

	std::cout << "Usage: sevrun [command] [flags]" << std::endl;

	std::cout << "commands:" << std::endl;
	for (const auto& cmd : commands) {
		std::cout << "\t- " << cmd << std::endl;
	}
	std::cout << "flags:" << std::endl;
	for (const auto& flag : flags) {
		std::cout << "\t- " << flag << std::endl;
	}
}
#endif

#ifndef CHECK_JSON_FILE
#define CHECK_JSON_FILE

bool CheckJsonFile(const std::string& filename) {
	
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return false;
	}

	try {
		nlohmann::json jsonData;
		file >> jsonData;

		if (jsonData.is_null()) {
			std::cerr << "Error: JSON file is empty or invalid." << std::endl;
			return false;
		}

		// You can add more validation checks here if needed
		return true;

	} catch (const nlohmann::json::parse_error& e) {
		std::cerr << "Error: JSON parsing error: " << e.what() << std::endl;
		return false;
	}

	file.close();
	return true;
}
#endif

// clean up defines to avoid redefinition errors
#undef COMMANDS_H
#undef FLAGS_H
#undef ISVALID_COMMAND_FUNC
#undef ISVALID_FLAG
#undef PRINT_HELP
#undef CHECK_JSON_FILE