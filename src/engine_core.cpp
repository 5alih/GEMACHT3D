#include "engine_core.h"
#include <iostream>

Camera3D playerCamera= {0};
float deltaTime= GetFrameTime();

// Initialize the window and set up basic configurations
void CoreEngine::Initialize() {
	InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "pine Engine");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	MaximizeWindow();
	SetTargetFPS(144);
	ECS ecs;
	ecs.Initialize();

	// Register the TransformComponent type
	ecs.RegisterComponentType<TransformComponent>(0); // 0 is the type ID for TransformComponent
	Entity entity = ecs.CreateEntity();

	TransformComponent transform;
	transform.position = { 10.0f, 20.0f };
	transform.velocity = { 1.0f, 1.0f };

	// Add TransformComponent to the entity
	int transformId = entity.AddComponent(0, transform);
	if (transformId != -1) {
		std::cout << "TransformComponent added to entity with ID: " << entity.GetId() << std::endl;
	}

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
//		ecs.Update();
//		renderer.Render();
		UpdateCamera(&playerCamera, CAMERA_FIRST_PERSON);
		renderer.RenderPlayerView(playerCamera);
	}
}

// Clean up resources and close the window
void CoreEngine::Shutdown() {
	CloseWindow();
}
