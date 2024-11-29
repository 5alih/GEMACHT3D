#include "engine_core.h"
#include <iostream>

Camera3D playerCamera= {0};
float deltaTime= GetFrameTime();

void CoreEngine::Initialize() {
	InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "pine Engine");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	MaximizeWindow();
	SetTargetFPS(0);
	ecs.Initialize();

	playerCamera.position= {0.0f, 2.0f, 4.0f};
	playerCamera.target= {0.0f, 2.0f, 0.0f};
	playerCamera.up= {0.0f, 1.0f, 0.0f};
	playerCamera.fovy= 60.0f;
	playerCamera.projection= CAMERA_PERSPECTIVE;

	DisableCursor();
}

// Main game loop
void CoreEngine::Run() {
	while (!WindowShouldClose()) {
		input.HandleInput();
		ecs.Update();
		UpdateCamera(&playerCamera, CAMERA_FIRST_PERSON);

		/* if(IsKeyPressed(KEY_P)){
			developerConsole.CreateEntity_exec();
		} */

		BeginDrawing();
    	ClearBackground(DARKBLUE);
		renderer.RenderPlayerView(playerCamera);
		DrawFPS(5, 5);
		developerConsole.log();
		EndDrawing();
	}
}

// Clean up resources and close the window
void CoreEngine::Shutdown() {
	CloseWindow();
}
