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
	developerConsole.ecswan= &ecs.ecswan;
	sceneMaster.ecswan= &ecs.ecswan;
	ecs.InitECS(20.0f);
	sceneMaster.InitGui(engine_font);
	developerConsole.Initialize();
	levelMaster.developerConsole= &developerConsole;
	levelMaster.InitLvl();
	sceneMaster.levelMaster= &levelMaster;
	levelEditor.levelMaster= &levelMaster;

	renderer.p_console= &sceneMaster.p_console;
	levelEditor.sceneMaster= &sceneMaster;
	levelEditor.ecswan= &ecs.ecswan;
	
	levelEditor.InitEditor(engine_font);
	swanGui= sceneMaster.GetGui("level_editor");
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
// level grid
// block placing/removing
// textures using GPU texture arrays
// mesh creation
// player movement
// aplha shader
// greedy meshing
// enabling/disabling editor ui
// dynamic blocks with ECS
// ambient occulision
// basic lighting
// dynamic lighting
// wavy foliage
// scene system
// move swangui initilization to scene master
// block editor
// scene for block editor
// behavior trees
// behavior tree editor
// scene for behavior tree editor
// behavior tree component for ECS
// some basic AI behaviors
// ECS and Behavior tree connection
// actor editor
// scene for actor editor 