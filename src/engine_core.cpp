#include "engine_core.h"

Camera3D playerCamera= {0};

void CoreEngine::Initialize(){
	InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "pine Engine");
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

    auto drawSceneFunc = [](Camera3D& cam) {
        Vector3 WorldCenter = {0.0f, 0.0f, 0.0f};
        Vector2 TestPlaneSize = {20, 20};
        DrawPlane(WorldCenter, TestPlaneSize, GOLD);
    };

    engine_font= LoadFontEx("resource/font/source-sans-pro.bold.ttf", 14, 0, 0);
    swanGui= renderer.InitGui(engine_font, playerCamera, drawSceneFunc);
}

// Main game loop
void CoreEngine::Run(){
	bool cursor= true;
	while(!WindowShouldClose()){
		input.HandleInput();
		ecs.Update();

		developerConsole.UpdateConsole();
		if(IsKeyPressed(KEY_F1)){
			if(cursor){
				DisableCursor();
				cursor= false;
			}
			else{
				EnableCursor();
				cursor= true;
			}
		}

		BeginDrawing();
    	ClearBackground(BLACK);
		renderer.RenderGui(swanGui);
		renderer.RenderFPS(WHITE);
		developerConsole.RenderLog();

		EndDrawing();
	}
}

// Clean up resources and close the window
void CoreEngine::Shutdown(){
	UnloadFont(engine_font);
	CloseWindow();
}
