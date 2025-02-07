#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "my_functions.h"
#include "ecs.h"
#include "console.h"
#include "renderer.h"
#include "Level.h"
#include "scene.h"

class CoreEngine{
public:
	ECS ecs;
	DeveloperConsole developerConsole;
	Renderer renderer;
	SwanGui swanGui;
	Font engine_font;
	LevelMaster levelMaster;
	SceneMaster sceneMaster;

	void Initialize();
	void Run();
	void Shutdown();
};

#endif // ENGINE_CORE_H