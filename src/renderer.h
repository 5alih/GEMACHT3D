#ifndef RENDERER_H
#define RENDERER_H

#include "my_functions.h"
#include "ecs.h"
#include "console.h"
#include "swanGUI.h"

class Renderer {
public:
	void RenderPlayerView(Camera3D playerCamera);
	void RenderFPS(Color color);
	SwanGui InitGui(Font font);
	void RenderGui(SwanGui &swanGui);
};

#endif // RENDERER_H