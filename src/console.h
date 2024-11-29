#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include "raylib.h"
#include "ecs.h"

class DeveloperConsole{
public:
	bool isEnabled= 0;
	std::string input;
	std::vector<std::string> allCommands;
	std::vector<std::string> possibleCommands;
	std::vector<std::function<void()>> executers;
	int possibleCommandIndex= 0;
	ECS ecs;
	std::string logText= "test text";

	DeveloperConsole();
	void Start();
	void Exit();
	void GetInputString();
	std::vector<std::string> GetPossibleCommands();
	void ExecuteCommand(int commandId);

	void log();

	//executers
	void CreateEntity_exec();
	void executer2();
};

#endif // CONSOLE_H