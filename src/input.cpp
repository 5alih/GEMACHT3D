#include "input.h"
#include "raylib.h"

void Input::HandleInput() {
    if (IsKeyDown(KEY_W)) { /* Move forward */ }
    if (IsKeyDown(KEY_A)) { /* Move left */ }
    if (IsKeyDown(KEY_S)) { /* Move back */ }
    if (IsKeyDown(KEY_D)) { /* Move right */ }
}