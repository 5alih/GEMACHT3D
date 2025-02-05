#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "my_functions.h"
#include "ECSwan.h"
#include "console.h"
#include "renderer.h"
#include "input.h"

class CoreEngine{
public:
	ECSwan ecs;
	DeveloperConsole developerConsole;
	Renderer renderer;
	Input input;

	Font engine_font;
	SwanGui swanGui;

	void Initialize();
	void Run();
	void Shutdown();
};

#endif // ENGINE_CORE_H