#include "engine_core.h"

Camera3D playerCamera= {0};

void CoreEngine::Initialize(){
	InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "swan engine");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetExitKey(KEY_NULL);
	MaximizeWindow();
	SetTargetFPS(144);
	ecs.Initialize();
	developerConsole.Initialize();

	playerCamera.position= {0.0f, 2.0f, 4.0f};
	playerCamera.target= {0.0f, 2.0f, 0.0f};
	playerCamera.up= {0.0f, 1.0f, 0.0f};
	playerCamera.fovy= 60.0f;
	playerCamera.projection= CAMERA_PERSPECTIVE;

    auto drawSceneFunc= [](Camera3D& cam){
		DrawGrid(20, 2.0f);
		DrawCube( (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, (Color){243, 169, 78, 255} );
    };

    engine_font= LoadFontEx("resource/font/source-sans-pro.bold.ttf", 14, 0, 0);
    swanGui= renderer.InitGui(engine_font, playerCamera, drawSceneFunc);
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
