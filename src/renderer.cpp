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

SwanGui Renderer::InitGui(Font font, Camera3D &camera, std::function<void(Camera3D&)> function){
	SwanGui swanGui;

	Vector2 p_settingsPos= {64, 18};
	Vector2 p_settingsSize= {22	, 33};
	auto p_settings= std::make_shared<Panel>("SETTINGS", p_settingsPos, p_settingsSize, 2, font);
	p_settings->addElement(std::make_shared<Button>("Create entity", [](){}, false));
	p_settings->addElement(std::make_shared<Button>("Delete entity", [](){}, false));
	p_settings->addElement(std::make_shared<Button>("Save entities", [](){}, true));
	swanGui.AddPanel(p_settings);

	Vector2 p_previewPos= {64, 0};
	Vector2 p_previewSize= {22, 18};
	auto p_preview= std::make_shared<Panel>("PREVIEW", p_previewPos, p_previewSize, font);
    p_preview->addElement(std::make_shared<CameraView3DFillBorder>(camera, function, (Color){9, 12, 15, 255} ));
	swanGui.AddPanel(p_preview);

	Vector2 p_listPos= {86, 0};
	Vector2 p_listSize= {10, 52};
	auto p_list= std::make_shared<Panel>("ELEMENT LIST", p_listPos, p_listSize, font);
	swanGui.AddPanel(p_list);

	Vector2 p_bottomPos= {0, 37};
	Vector2 p_bottomSize= {64, 15};
	auto p_bottom= std::make_shared<Panel>("CONTENT MANAGER", p_bottomPos, p_bottomSize, font);
	swanGui.AddPanel(p_bottom);

    Vector2 p_viewportPos= {0, 0};
    Vector2 p_viewportSize= {64, 37};
    auto p_viewport= std::make_shared<Panel>("VIEWPORT", p_viewportPos, p_viewportSize, font);
    
    p_viewport->addElement(std::make_shared<CameraView3DFill>(camera, function, (Color){9, 12, 15, 255} ));
    
    swanGui.AddPanel(p_viewport);

	return swanGui;
}

void Renderer::RenderGui(SwanGui &swanGui){
	swanGui.Update();
	swanGui.Draw();
}