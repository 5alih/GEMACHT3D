#include "engine_core.h"

#define FOR_ONCE(x) static bool is= true; if(is){ x; is= false; }

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

	// static Level lvl(20, 20, 20);
	// for(int x= 0; x< lvl.m_width; x++){
	// 	for(int y= 0; y< lvl.m_height; y++){
	// 		for(int z= 0; z< lvl.m_depth; z++){
	// 			if(y< 2){
	// 				lvl.m_blocks[x][y][z].m_texture_id= 1;
	// 			}
	// 		}
	// 	}
	// }
	// levelMaster.m_levels.push_back(lvl);

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
		// FOR_ONCE( levelMaster.SaveLevel(0) )

		BeginDrawing();
    	ClearBackground(BLACK);
		renderer.RenderGui(swanGui, developerConsole);
		renderer.RenderFPS(WHITE);
		developerConsole.RenderLog();
		levelEditor.Update();
		EndDrawing();
	}
}

void CoreEngine::Shutdown(){
	UnloadFont(engine_font);
	CloseWindow();
}

// TODO
// X level grid
// X block placing/removing
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
// X scene system
// X move swangui initilization to scene master
// scene for block editor
// block editor
// behavior trees
// scene for behavior tree editor
// behavior tree editor
// behavior tree component for ECS
// some basic AI behaviors
// ECS and Behavior tree connection
// scene for actor editor 
// actor editor