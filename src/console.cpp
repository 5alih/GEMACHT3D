#include "console.h"

DeveloperConsole::DeveloperConsole(){
	isEnabled= 0;
	input= "";
	possibleCommands= {};
	possibleCommandIndex= 0;

	//________________________________________________________________ COMMANDS _________________________________________________________________

	allCommands= {
	"CreateEntity",
	"command2",};
	
	executers.push_back([this](){ CreateEntity_exec(); });
	executers.push_back([this](){ executer2(); });
	
	//___________________________________________________________________________________________________________________________________________
}

void DeveloperConsole::Start()
{
	isEnabled= true;
}

void DeveloperConsole::Exit(){
	isEnabled= false;
}

void DeveloperConsole::GetInputString(){
	int key= GetKeyPressed();
	if(key== KEY_BACKSPACE && input.size()> 0){
		input.erase(input.end() -1);
	}
	else if(key== KEY_TAB && input.size()> 0){
		input= possibleCommands[possibleCommandIndex];
	}
	else if(key== KEY_UP && (size_t)possibleCommandIndex< (possibleCommands.size() -1)){
		possibleCommandIndex++;
	}
	else if(key== KEY_DOWN && possibleCommandIndex> 0){
		possibleCommandIndex--;
	}
	else{
		input.push_back(key);
	}

}

std::vector<std::string> DeveloperConsole::GetPossibleCommands() {
    possibleCommands.clear();
    for (int i = 0; (size_t)i < allCommands.size(); i++) {
        if (allCommands[i].find(input) != std::string::npos) {
            if (input.find(allCommands[i])) {
                ExecuteCommand(i);
                possibleCommands.push_back(allCommands[i]);
                return possibleCommands;
            }
            possibleCommands.push_back(allCommands[i]);
        }
    }
    return possibleCommands;
}

void DeveloperConsole::ExecuteCommand(int commandId){
	executers[commandId]();
}

const char *to_const_char(std::string str){
	const char *text= str.c_str();
	return text;
}

void DeveloperConsole::log(){
	DrawText(to_const_char(logText), 5, 25, 20, WHITE);
}

std::string to_string(int value){
    std::ostringstream ss;
    ss << value;
	std::string str= ss.str();
	return str;
}

//_______________________________________________________________ EXECUTERS ________________________________________________________________

void DeveloperConsole::CreateEntity_exec(){	// "CreateEntity"
	Entity entity= ecs.CreateEntity();
	logText= to_string(entity.GetId());
}

void DeveloperConsole::executer2(){
}
