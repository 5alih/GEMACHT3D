#ifndef RENDERER_H
#define RENDERER_H

#include "my_functions.h"
#include "console.h"
#include "swanGUI.h"
#include "level.h"

class Renderer{
public:
	std::shared_ptr<Panel> *p_console;
	LevelMaster *levelMaster;

	void RenderFPS(Color color);
	void RenderGui(SwanGui &swanGui, DeveloperConsole &developerConsole);
};

#endif // RENDERER_H