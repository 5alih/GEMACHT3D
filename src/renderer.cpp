#include "renderer.h"

void Renderer::RenderFPS(Color color){
	DrawText(to_const_char(to_string(GetFPS())), GetMonitorWidth(0) -20, 5, 10, color);
}

void Renderer::RenderGui(SwanGui &swanGui, DeveloperConsole &developerConsole){
	swanGui.Update();
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (*p_console)->IsMouseOver()){
		developerConsole.Start();
	}
	if(IsKeyPressed(KEY_ESCAPE) && developerConsole.GetIsEnabled()){
		developerConsole.Exit();
	}
	swanGui.Draw();
}