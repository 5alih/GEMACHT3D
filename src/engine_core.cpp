#include "engine_core.h"

void CoreEngine::Initialize(){
	InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "GEMACHT 3D");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowState(FLAG_INTERLACED_HINT);
	SetExitKey(KEY_NULL);
	SetTargetFPS(144);
	static Image iconpng= LoadImage("resource/image/gelbox.png");
	SetWindowIcon(iconpng);

    engine_font= LoadFontEx("resource/font/source-sans-pro.bold.ttf", 14, 0, 0);
	renderer.ecswan= &ecs.ecswan;
	developerConsole.ecswan= &ecs.ecswan;

	ecs.InitECS(20.0f);
    swanGui= renderer.InitGui(engine_font);
	developerConsole.Initialize();
}

void CoreEngine::Run(){
	while(!WindowShouldClose()){
		float deltaTime= GetFrameTime();
		ecs.Update(deltaTime);
		developerConsole.UpdateConsole();

		BeginDrawing();
    	ClearBackground(BLACK);
		renderer.RenderGui(swanGui, developerConsole);
		renderer.RenderFPS(WHITE);
		developerConsole.RenderLog();

		EndDrawing();
	}
}

void CoreEngine::Shutdown(){
	UnloadFont(engine_font);
	CloseWindow();
}

// TODO
// add level grid
// add block placing/removing
// add textures using GPU texture arrays
// add mesh creation
// add aplha shader
// add greedy meshing
// add enabling/disabling editor ui
// add dynamic blocks with ECS
// add ambient occulision
// add basic lighting
// add dynamic lighting
// add wavy foliage
// implement scene system
// implement block editor
// add scene for block editor
// add behavior trees
// add behavior tree editor
// add scene for behavior tree editor
// add behavior tree component for ECS
// add some basic AI behaviors
// connect ECS and Behavior tree
// add actor editor
// add scene for actor editor 