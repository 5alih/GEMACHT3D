#include "console.h"

	//TO DO: add alias variable declaring with scripts
	//			alias number 1453
	//			alias fraction 12.25
	//			alias text "Hello World" 

void DeveloperConsole::Initialize(){
	isEnabled= true;
	possibleCommands= {};
	possibleCommandIndex= 0;
	logs.push_back("Developer Console Started");
	consoleFont= LoadFontEx("resource/font/JetBrainsMono-Regular.ttf", 12, 0, 0);
	scrollAmounth= 0;

	//________________________________________________________________ COMMANDS _________________________________________________________________

	allCommands= {
	"echo",
	"run",
	"clear",
	"quit",
	"createEntity",
	"deleteEntity",
	"listEntities"
	};
	
	executers.push_back([this](){ Echo_exec(); });
	executers.push_back([this](){ RunScript_exec(); });
	executers.push_back([this](){ Clear_exec(); });
	executers.push_back([this](){ Quit_exec(); });
	executers.push_back([this](){ CreateEntity_exec(); });
	executers.push_back([this](){ DeleteEntity_exec(); });
	executers.push_back([this](){ ListEntities_exec(); });
	//___________________________________________________________________________________________________________________________________________
}

void DeveloperConsole::UpdateConsole(){
	if(IsKeyPressed(KEY_GRAVE)){
		this->OnOff();
	}
	if(this->GetIsEnabled()== true){
		this->GetInputString();
		this->GetPossibleCommands();
		if(IsKeyPressed(KEY_ENTER) && (int)possibleCommands.size()< 2){
			isReady= true;
		}
		else{
			isReady= false;
		}

		if(IsKeyDown(KEY_LEFT_CONTROL)){
			if(IsKeyDown(KEY_KP_9)){
				scrollAmounth++;
			}
			if(IsKeyDown(KEY_KP_3) && scrollAmounth> 0){
				scrollAmounth--;
			}
		}
		else{
			if(IsKeyPressed(KEY_KP_9)){
				scrollAmounth++;
			}
			if(IsKeyPressed(KEY_KP_3) && scrollAmounth> 0){
				scrollAmounth--;
			}
		}
	}
}

void DeveloperConsole::Start(){
	isEnabled= true;
}

void DeveloperConsole::Exit(){
	isEnabled= false;
}

void DeveloperConsole::OnOff(){
	isEnabled= !isEnabled;
}

bool DeveloperConsole::GetIsEnabled(){
	return isEnabled;	
}

void DeveloperConsole::GetInputString(){
	int key= GetKeyPressed();
	if(key== KEY_BACKSPACE && input.size()> 0){
		if(IsKeyDown(KEY_LEFT_CONTROL)){
			std::vector<std::string> parts=  split_string(input, ' ');
			parts.erase(parts.begin() + ((int)parts.size() - 1));
			input= cat_string(parts, ' ');
			return;
		}
		input.pop_back();
	}
	else if(key== KEY_TAB && input.size()> 0 && !possibleCommands.empty()){
		input= possibleCommands[possibleCommandIndex];
	}
	else if(key== KEY_UP && (size_t)possibleCommandIndex< (possibleCommands.size() -1)){
		possibleCommandIndex++;
	}
	else if(key== KEY_DOWN && possibleCommandIndex> 0){
		possibleCommandIndex--;
	}
	else if(key>= 32 && key<= 126){
		input.push_back((char)GetCharPressed());
		possibleCommandIndex= 0;
	}
}

std::vector<std::string> DeveloperConsole::GetPossibleCommands() {
	possibleCommands.clear();
	for(int i= 0; (size_t)i < allCommands.size(); i++){
		if(allCommands[i].find(input) != std::string::npos) {
			possibleCommands.push_back(allCommands[i]);
		}
		if(isReady && input.find(allCommands[i]) != std::string::npos) {
			ExecuteCommand(i);
			input.clear();
			isReady = false;
			scrollAmounth= 0;
			break;
		}
	}
	return possibleCommands;
}

void DeveloperConsole::ExecuteCommand(int commandId){
	executers[commandId]();
}

void DeveloperConsole::log(std::vector<std::string> list, int x, int y, int size, Color listColor, Color strColor, int length, int &scroll_length, std::string str){
	int start= 0, i= 0;
	int padding= size + (size/5);
	std::string temp;
	if(length<= (int)list.size())
		start= (int)list.size() -length;
	int scroll= 0;
	if((int)list.size()== (length + scroll_length)){
		scroll_length= scroll_length -1;
	}
	if((int)list.size()> (length + scroll_length)){
		scroll= scroll_length;
		start= (int)list.size() -length -scroll_length;
	}
	for(i= start; i< (int)list.size() - scroll; i++){
		temp= list[i];

		//________________________________________________________ COLORED SYMBOLS _________________________________________________________

		if(temp.find("[!]")!= std::string::npos){
			DrawTextEx(consoleFont, "/!\\", (Vector2){(float)x, (float)(y + ((i -start)*padding))}, size, 2.0f, YELLOW);
			if(temp.size()> 3)
				temp.replace(0, 3, 3, ' ');
		}
		else if(temp.find("[X]")!= std::string::npos){
			DrawTextEx(consoleFont, "(X)", (Vector2){(float)x, (float)(y + ((i -start)*padding))}, size, 2.0f, RED);
			if(temp.size()> 3)
				temp.replace(0, 3, 3, ' ');
		}
		else if(temp.find("[$]")!= std::string::npos){
			DrawTextEx(consoleFont, "<$>", (Vector2){(float)x, (float)(y + ((i -start)*padding))}, size, 2.0f, PURPLE);
			if(temp.size()> 3)
				temp.replace(0, 3, 3, ' ');
		}
		else if(temp.find("[@]")!= std::string::npos){
			if(temp.size()> 3)
				temp.replace(0, 3, 1, '@');
			DrawTextEx(consoleFont, to_const_char(temp), (Vector2){(float)x, (float)(y + ((i -start)*padding))}, size, 2.0f, GRAY);
			temp.clear();
		}
		DrawTextEx(consoleFont, to_const_char(temp), (Vector2){(float)x, (float)(y + ((i -start)*padding))}, size, 2.0f, listColor);
	}
	DrawTextEx(consoleFont, to_const_char(str), (Vector2){(float)x, (float)(y + ((i -start)*padding))}, size, 2.0f, strColor);
}

void DeveloperConsole::RenderLog(){
	int fontSize=12;
	int zero= 0;
	Color TEAL= (Color){0, 200, 170, 255};
	if(isEnabled== true){
		log(logs, 5, 5, fontSize, WHITE, TEAL, 20, scrollAmounth, input);
		if((int)possibleCommands.size()> 0){
			log(possibleCommands, 1005, 5, fontSize, LIGHTGRAY, WHITE, 70, zero, possibleCommands[possibleCommandIndex]);
		}
		else{
			log(possibleCommands, 1005, 5, fontSize, LIGHTGRAY, WHITE, 70, zero, "");
		}
	}
}

//_______________________________________________________________ EXECUTERS ________________________________________________________________

void DeveloperConsole::Echo_exec(){				//	"Echo (message)"
	std::vector<std::string> parts= split_string(input, ' ');
	std::vector<std::string> result;
	result.push_back("[@]");
	for(int i= 1; i< (int)parts.size(); i++){
		result.push_back(parts[i]);
	}
	logs.push_back(cat_string(result, ' '));
}

void DeveloperConsole::RunScript_exec(){		// "Run (filename)"
	std::vector<std::string> parts= split_string(input, ' ');
	std::vector<std::string> response;
	if((int)parts.size()< 2)
		return;
	response.push_back("[$] Executing script:");
	response.push_back(parts[1]);
	logs.push_back(cat_string(response, ' '));
	parts[0]= "resource/script/";
	parts.push_back(".txt");
	std::string filepath= cat_string(parts, '\0');
	std::ifstream fin(filepath);

	std::string line;
	while(getline(fin, line)){
		isReady= true;
		input= line;
		GetPossibleCommands();
	}
	fin.close();
}

void DeveloperConsole::Clear_exec(){			// "Clear"
	logs.clear();
}

void DeveloperConsole::Quit_exec(){				// "Quit"
	exit(EXIT_SUCCESS);
}

void DeveloperConsole::CreateEntity_exec(){		// "CreateEntity"
	Entity entity= ecs.CreateEntity();
	logs.push_back("Created entity with id: " + to_string(entity.GetId()));
}

void DeveloperConsole::DeleteEntity_exec(){		// "DeleteEntity (int)"
	std::vector<std::string> parts= split_string(input, ' ');
	if((int)parts.size()< 2){
		logs.push_back("[!] Expected format: \"DeleteEntity int\"");
		return;
	}
	else if(!is_number(parts[1])){
		logs.push_back("[!] Expected argument: \"int\"");
		return;
	}
	int id= std::stoi(parts[1]);
	if(ecs.DeleteEntity(id)){
		logs.push_back("Deleted entity with id: " + parts[1]);
	}
	else{
		logs.push_back("[X] Couldn't find entity with id: " + parts[1]);
	}
}

void DeveloperConsole::ListEntities_exec(){		// "ListEntities"
	logs.push_back("List of entities: ");
	for(int i= 0; i< (int)ecs.entities.size(); i++){
		logs.push_back(to_string(ecs.entities[i].GetId()));
	}
}