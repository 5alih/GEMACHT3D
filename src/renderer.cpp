#include "renderer.h"

void Renderer::RenderPlayerView(Camera3D playerCamera){
	Vector3 WorldCenter= {0.0f, 0.0f, 0.0f};
	Vector2 TestPlaneSize= {20, 20};

	BeginMode3D(playerCamera);
		DrawPlane(WorldCenter, TestPlaneSize, DARKGRAY);
	EndMode3D();
}

void Renderer::RenderFPS(Color color){
	DrawText(to_const_char(to_string(GetFPS())), GetMonitorWidth(0) -20, 5, 10, color);
}

SwanGui Renderer::InitGui(Font font){
	SwanGui swanGui;

	Vector2 p_testPos= {0, 20};
	Vector2 p_testSize= {10, 14};
	auto p_test= std::make_shared<Panel>("TEST", p_testPos, p_testSize, font);
	p_test->addElement(std::make_shared<Button>("Create entity", [](){}, false));
	p_test->addElement(std::make_shared<Button>("Delete entity", [](){}, false));
	p_test->addElement(std::make_shared<Button>("Save entities", [](){}, true));
	swanGui.AddPanel(p_test);

	return swanGui;
}

void Renderer::RenderGui(SwanGui &swanGui){
	swanGui.Update();
	swanGui.Draw();
}