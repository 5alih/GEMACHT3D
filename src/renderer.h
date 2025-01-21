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
	SwanGui InitGui(Font font, Camera3D &camera, std::function<void(Camera3D&)> function);
	void RenderGui(SwanGui &swanGui);
};

#endif // RENDERER_H