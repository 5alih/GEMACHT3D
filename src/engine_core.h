#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "raylib.h"
#include "ecs.h"
#include "console.h"
#include "renderer.h"
#include "input.h"

class CoreEngine {
public:
	Input input;
	ECS ecs;
	Renderer renderer;
	DeveloperConsole developerConsole;

	void Initialize();
	void Run();
	void Shutdown();
};

#endif // ENGINE_CORE_H