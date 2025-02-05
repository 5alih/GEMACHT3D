#include "engine_core.h"

void CoreEngine::Initialize(){
	InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "GEMACHT 3D");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowState(FLAG_INTERLACED_HINT);
	SetExitKey(KEY_NULL);
	SetTargetFPS(144);
	static Image iconpng= LoadImage("resource/image/gelbox.png");
	SetWindowIcon(iconpng);
	ecs.Initialize();
	developerConsole.Initialize();

    engine_font= LoadFontEx("resource/font/source-sans-pro.bold.ttf", 14, 0, 0);
    swanGui= renderer.InitGui(engine_font);
}

void CoreEngine::Run(){
	while(!WindowShouldClose()){
		input.HandleInput(); //imposter
		ecs.Update();
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

// test and see if ECS really works
// connect ECS with renderer
// change CameraView3D to use level data instead