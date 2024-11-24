#include "renderer.h"
#include "ecs.h"
#include "raylib.h"

void Renderer::RenderPlayerView(Camera3D playerCamera){
	Vector3 WorldCenter= {0.0f, 0.0f, 0.0f};
	Vector2 TestPlaneSize= {20, 20};

    BeginDrawing();
    ClearBackground(DARKBLUE);
	BeginMode3D(playerCamera);
		DrawPlane(WorldCenter, TestPlaneSize, YELLOW);
	EndMode3D();
	DrawFPS(0, 0);
    EndDrawing();
}

void Renderer::Render(){
    BeginDrawing();
    ClearBackground(DARKBLUE);
	DrawFPS(0, 0);
    EndDrawing();
}