#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "my_functions.h"
#include "resource.h"
#include "ecs.h"
#include "console.h"
#include "renderer.h"
#include "input.h"

class CoreEngine {
public:
	ECS ecs;
	ResourceManager resourceManager;
	DeveloperConsole developerConsole;
	Renderer renderer;
	Input input;

	void Initialize();
	void Run();
	void Shutdown();
};

#endif // ENGINE_CORE_H