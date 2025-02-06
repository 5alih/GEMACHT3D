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
    swanGui= renderer.InitGui(engine_font);
	ecswan= ecs.InitECS(1.0f); 
	developerConsole.Initialize(ecswan);
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

// connect ECS with renderer
// change CameraView3D to use level data instead