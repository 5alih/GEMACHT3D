#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <bits/stdc++.h>
#include <fstream>
#include "raylib.h"
#include "ecs.h"

class DeveloperConsole{
public:
	bool isEnabled= true;
	bool isReady= false;
	Font consoleFont;
	std::string input;
	std::vector<std::string> allCommands;
	std::vector<std::string> possibleCommands;
	std::vector<std::function<void()>> executers;
	int possibleCommandIndex;
	int scrollAmounth;
	ECS ecs;
	std::vector<std::string> logs;

	void UpdateConsole();
	void Initialize();
	void Start();
	void Exit();
	void OnOff();
	bool GetIsEnabled();
	void GetInputString();
	std::vector<std::string> GetPossibleCommands();
	void ExecuteCommand(int commandId);

	void log(std::vector<std::string> list, int x, int y, int size, Color listColor, Color strColor, int length, int &scroll_length, std::string str);
	void RenderLog();

	//executers
	void Clear_exec();
	void Quit_exec();
	void CreateEntity_exec();
	void DeleteEntity_exec();
	void ListEntities_exec();
	void RunScript_exec();
};

const char *to_const_char(std::string str);
std::string to_string(int value);
bool is_number(const std::string& s);

std::vector<std::string> split_string(const std::string str, const char ch);
std::string cat_string(std::vector<std::string> parts, char ch);

#endif // CONSOLE_H