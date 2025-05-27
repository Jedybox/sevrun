// sevrun.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <string>
#include <vector>

#ifndef FLAGS_H
#define FLAGS_H
const std::vector<std::string> flags = { "-s","-v",};
#endif

#ifndef COMMANDS_H
#define COMMANDS_H
const std::vector<std::string> commands = { "help", "serve", "add", "rename", "redi", "remove", "list"};
#endif

#ifndef ISVALID_COMMAND_FUNC
#define ISVALID_COMMAND_FUNC
bool IsValidCommand(const std::string& command) {
	for (const auto& cmd : commands) if (cmd == command) return true;
	return false;
}
#endif

#ifndef ISVALID_FLAG
#define ISVALID_FLAG
bool IsValidFlag(const std::string& flag) {
	for (const auto& f : flags) if (f == flag) return true;
	return false;
}
#endif
