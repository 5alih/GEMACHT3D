#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "my_functions.h"
#include "ecs.h"
#include "console.h"
#include "renderer.h"

class CoreEngine{
public:
	ECS ecs;
	ECSwan ecswan;
	DeveloperConsole developerConsole;
	Renderer renderer;
	SwanGui swanGui;
	Font engine_font;

	void Initialize();
	void Run();
	void Shutdown();
};

#endif // ENGINE_CORE_H