#include <raylib.h>

int main() 
{
    const Color darkGreen = {20, 160, 133, 255};
    
	InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "pine Engine");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	MaximizeWindow();
	SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(darkGreen);
        EndDrawing();
    }
    
    CloseWindow();
}