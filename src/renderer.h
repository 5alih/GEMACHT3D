#ifndef RENDERER_H
#define RENDERER_H

#include "raylib.h"
#include "ecs.h"
#include "console.h"
#include "raylib.h"

class Renderer {
public:
    void Render();
	void RenderPlayerView(Camera3D playerCamera);
	void RenderFPS(Color color);
};

#endif // RENDERER_H