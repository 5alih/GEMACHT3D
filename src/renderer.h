#ifndef RENDERER_H
#define RENDERER_H

#include "raylib.h"

class Renderer {
public:
    void Render();
	void RenderPlayerView(Camera3D playerCamera);
};

#endif // RENDERER_H