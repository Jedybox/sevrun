// sevrun.h : Include file for standard system include files
// or project specific include files.

#pragma once

#include <fstream>
#include "json.hpp"
#include <iostream>
#include <string>
#include <vector>

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
}
#endif

#ifndef CHECK_JSON_FILE
#define CHECK_JSON_FILE

bool CheckJsonFile() {

	// Get the directory of the executable
	char exepath[MAX_PATH];
	GetModuleFileNameA(NULL, exepath, MAX_PATH);
	std::filesystem::path exeDir = std::filesystem::path(exepath).parent_path();
	// Check if paths.json exists in the same directory as the executable
	std::string jsonPath = exeDir.string() + "\\paths.json";

	if (!std::filesystem::exists(jsonPath)) {
		std::cerr << "Error: json file for configurations of paths is missing " << std::endl;
		return 1;
	}
	
	std::ifstream file(jsonPath);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open json configuration " << jsonPath << std::endl;
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

#ifndef PATHEXISTS_H
#define PATHEXISTS_H
	/*
	* Function to check if a path exists in the JSON file
	* This function checks if a given path name exists in the JSON file.
	*/
bool pathExists(const std::string& pathName) {
	return std::filesystem::exists(pathName);
}
#endif

#ifndef ADD_SERVER_PATH
#define ADD_SERVER_PATH
	/*
	* Function to add a path to the JSON file
	* This function reads the existing JSON file, adds a new path under the specified name,
	* and writes the updated JSON back to the file.
	*/
void addPathToJson(const nlohmann::json& pathAndFile , const std::string& pathName, const std::string& runner) {
    if (!CheckJsonFile()) throw std::runtime_error("JSON file check failed");

    nlohmann::json obj;
    obj["path"] = pathAndFile;
    obj["runner"] = runner;

    nlohmann::json jsonData;
    char exepath[MAX_PATH];
    GetModuleFileNameA(NULL, exepath, MAX_PATH);
    std::filesystem::path exeDir = std::filesystem::path(exepath).parent_path();
    std::string jsonPath = exeDir.string() + "\\paths.json";

    std::ifstream inFile(jsonPath);
    if (inFile.is_open()) {
        try {
            inFile >> jsonData;
        } catch (const nlohmann::json::parse_error& e) {
            throw std::runtime_error("Unable to write your input to the path config");
        }
        inFile.close();
    } else {
        throw std::runtime_error("Could not open JSON file for reading.");
    }

    if (jsonData.contains(pathName)) 
		throw std::runtime_error("Path name already exists in the JSON file.");
	

	if(!pathExists(pathAndFile)) 
		throw std::runtime_error("Path does not exist: " + pathAndFile.dump());	

    jsonData[pathName] = obj;

    std::ofstream outFile(jsonPath);
    if (outFile.is_open()) {
        try {
            outFile << jsonData.dump(4);
        } catch (const nlohmann::json::exception& e) {
        	throw std::runtime_error("Error writing to JSON file: " + std::string(e.what()));
        }
        outFile.close();
        std::cout << pathName << " is added successfully" << std::endl;
    } else throw std::runtime_error("Could not open JSON file for writing.");
    
}


#endif

#ifndef RENAME_SERVER_PATH_NAME
#define RENAME_SERVER_PATH_NAME
	/*
	* Function to rename a path in the JSON file
	* This function renames an existing path in the JSON file.
	*/
void renameServerPathName(const std::string& oldName, const std::string& newName) {
	// TODO: Implement the rename functionality
}
#endif

#ifndef REDIRECT_SERVER_PATH
#define REDIRECT_SERVER_PATH
	/*
	* Function to redirect a server path in the JSON file
	* This function updates the path of an existing server path in the JSON file.
	*/
void redirectServerPath(const std::string& pathName, const std::string& newPath) {
	// TODO: Implement the redirect functionality
}
#endif

#ifndef REMOVE_SERVER_PATH
#define REMOVE_SERVER_PATH
	/*
	* Function to remove a server path from the JSON file
	* This function removes an existing server path from the JSON file.
	*/
void removeServerPath(const std::string& pathName) {
	// TODO: Implement the remove functionality
}
#endif

#ifndef LIST_SERVER_PATHS
#define LIST_SERVER_PATHS
	/*
	* Function to list all server paths in the JSON file
	* This function reads the JSON file and prints all server paths and their names.
	*/
void listServerPaths() {
	if (!CheckJsonFile()) return;

	std::string jsonPath = std::filesystem::path(__FILE__).parent_path().string() + "\\paths.json";

	std::ifstream inFile(jsonPath);
	if (!inFile.is_open()) {
		std::cerr << "Error: Could not open JSON file for reading." << std::endl;
		return;
	}

	nlohmann::json jsonData;
	try {
		inFile >> jsonData;
	} catch (const nlohmann::json::parse_error& e) {
		std::cerr << "Error: JSON parsing error: " << e.what() << std::endl;
		return;
	}
	inFile.close();

	if (jsonData.is_null() || jsonData.empty()) {
		std::cout << "No server paths found." << std::endl;
		return;
	}

	std::cout << "Server Paths:" << std::endl;
	for (const auto& item : jsonData.items()) {
		std::cout << "Name: " << item.key() << ", Path: " << item.value()["path"];
		std::cout << ", Runner: " << item.value()["runner"] << std::endl;
	}
}
#endif
// clean up defines to avoid redefinition errors
#undef COMMANDS_H
#undef FLAGS_H
#undef ISVALID_COMMAND_FUNC
#undef ISVALID_FLAG
#undef PRINT_HELP
#undef CHECK_JSON_FILE
#undef ADD_PATH_TO_JSON
#undef PATHEXISTS_H
