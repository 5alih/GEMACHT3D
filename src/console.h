#ifndef CONSOLE_H
#define CONSOLE_H

#include "my_functions.h"
#include "ECSwan.h"

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
	ECSwan *ecs;
	std::vector<std::string> logs;

	void UpdateConsole();
	void Initialize(ECSwan &ecs);
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
	void Echo_exec();
};

#endif // CONSOLE_H