#ifndef RENDERER_H
#define RENDERER_H

#include "my_functions.h"
#include "console.h"
#include "ecs.h"
#include "swanGUI.h"

class Renderer{
public:
	std::shared_ptr<Panel> p_console;
	ECSwan *ecswan;

	void RenderFPS(Color color);
	SwanGui InitGui(Font font);
	void RenderGui(SwanGui &swanGui, DeveloperConsole &developerConsole);
};

#endif // RENDERER_H