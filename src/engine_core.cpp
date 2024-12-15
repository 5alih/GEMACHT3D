#include "engine_core.h"

Camera3D playerCamera= {0};
float deltaTime= GetFrameTime();

void CoreEngine::Initialize() {
	InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "pine Engine");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetExitKey(KEY_NULL);
	MaximizeWindow();
	SetTargetFPS(144);
	ecs.Initialize();
	resourceManager.Initialize();
	developerConsole.Initialize();

	playerCamera.position= {0.0f, 2.0f, 4.0f};
	playerCamera.target= {0.0f, 2.0f, 0.0f};
	playerCamera.up= {0.0f, 1.0f, 0.0f};
	playerCamera.fovy= 60.0f;
	playerCamera.projection= CAMERA_PERSPECTIVE;

	DisableCursor();
}

// Main game loop
void CoreEngine::Run() {
	while(!WindowShouldClose()){
		input.HandleInput();
		ecs.Update();

		developerConsole.UpdateConsole();
		if(developerConsole.isEnabled== false){
			UpdateCamera(&playerCamera, CAMERA_FIRST_PERSON);
		}

		BeginDrawing();
    	ClearBackground(BLACK);
		renderer.RenderPlayerView(playerCamera);
		renderer.RenderFPS(WHITE);
		developerConsole.RenderLog();

		EndDrawing();
	}
}

// Clean up resources and close the window
void CoreEngine::Shutdown() {
	CloseWindow();
}
