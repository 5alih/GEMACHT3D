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

    engine_font= LoadFontEx("resource/font/source-sans-pro.bold.ttf", 14, 0, 0);
    swanGui= renderer.InitGui(engine_font);

	playerCamera.position= {0.0f, 2.0f, 4.0f};
	playerCamera.target= {0.0f, 2.0f, 0.0f};
	playerCamera.up= {0.0f, 1.0f, 0.0f};
	playerCamera.fovy= 60.0f;
	playerCamera.projection= CAMERA_PERSPECTIVE;
}

// Main game loop
void CoreEngine::Run(){
	bool cursor= true;
	while(!WindowShouldClose()){
		input.HandleInput();
		ecs.Update();

		developerConsole.UpdateConsole();
		if(developerConsole.isEnabled== false){
			UpdateCamera(&playerCamera, CAMERA_FIRST_PERSON);
		}

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
		renderer.RenderPlayerView(playerCamera);
		renderer.RenderFPS(WHITE);
		renderer.RenderGui(swanGui);
		developerConsole.RenderLog();

		EndDrawing();
	}
}

// Clean up resources and close the window
void CoreEngine::Shutdown(){
	UnloadFont(engine_font);
	CloseWindow();
}
