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

SwanGui Renderer::InitGui(Font font, Camera3D& playerCamera){
	SwanGui swanGui;

	Vector2 p_settingsPos= {64, 20};
	Vector2 p_settingsSize= {16	, 32};
	auto p_settings= std::make_shared<Panel>("SETTINGS", p_settingsPos, p_settingsSize, font);
	p_settings->addElement(std::make_shared<Button>("Create entity", [](){}, false));
	p_settings->addElement(std::make_shared<Button>("Delete entity", [](){}, false));
	p_settings->addElement(std::make_shared<Button>("Save entities", [](){}, true));
	swanGui.AddPanel(p_settings);

	Vector2 p_previewPos= {64, 0};
	Vector2 p_previewSize= {32, 20};
	auto p_preview= std::make_shared<Panel>("PREVIEW", p_previewPos, p_previewSize, font);
	p_preview->addElement(std::make_shared<Comment>("this will be an image"));
	swanGui.AddPanel(p_preview);

	Vector2 p_listPos= {80, 20};
	auto p_list= std::make_shared<Panel>("ELEMENT LIST", p_listPos, p_settingsSize, font);
	swanGui.AddPanel(p_list);

	Vector2 p_bottomPos= {0, 36};
	Vector2 p_bottomSize= {64, 16};
	auto p_bottom= std::make_shared<Panel>("CONTENT MANAGER", p_bottomPos, p_bottomSize, font);
	swanGui.AddPanel(p_bottom);

    Vector2 p_viewportPos= {0, 0};
    Vector2 p_viewportSize= {64, 36};
    auto p_viewport= std::make_shared<Panel>("VIEWPORT", p_viewportPos, p_viewportSize, font);
    
    auto drawSceneFunc = [](Camera3D& cam) {
        Vector3 WorldCenter = {0.0f, 0.0f, 0.0f};
        Vector2 TestPlaneSize = {20, 20};
        DrawPlane(WorldCenter, TestPlaneSize, GOLD);
    };
    
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    p_viewport->addElement(std::make_shared<CameraView3DFill>(camera, drawSceneFunc));
    
    swanGui.AddPanel(p_viewport);

	return swanGui;
}

void Renderer::RenderGui(SwanGui &swanGui){
	swanGui.Update();
	swanGui.Draw();
}