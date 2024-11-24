#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "raylib.h"
#include "ecs.h"
#include "renderer.h"
#include "input.h"

class CoreEngine {
public:
	void Initialize();
	void Run();
	void Shutdown();
private:
	Input input;
	ECS ecs;
	Renderer renderer;
};

#endif // ENGINE_CORE_H