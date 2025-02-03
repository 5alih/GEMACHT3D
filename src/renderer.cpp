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

	Vector2 p_settingsPos= {64, 19};
	Vector2 p_settingsSize= {22	, 35};
	auto p_settings= std::make_shared<Panel>("SETTINGS", p_settingsPos, p_settingsSize, 2, font);
	p_settings->addElement(std::make_shared<Button>("Create entity", [](){}, false));
	p_settings->addElement(std::make_shared<Button>("Delete entity", [](){}, false));
	p_settings->addElement(std::make_shared<Button>("Save entities", [](){}, true));
	swanGui.AddPanel(p_settings);

	Vector2 p_previewPos= {64, 1};
	Vector2 p_previewSize= {22, 18};
	auto p_preview= std::make_shared<Panel>("PREVIEW", p_previewPos, p_previewSize, font);
	p_preview->addElement(std::make_shared<CameraView3DFillBorder>(camera, function, (Color){9, 12, 15, 255} ));
	swanGui.AddPanel(p_preview);

	Vector2 p_listPos= {86, 1};
	Vector2 p_listSize= {10, 52};
	auto p_list= std::make_shared<Panel>("ELEMENT LIST", p_listPos, p_listSize, font);
	swanGui.AddPanel(p_list);

	Vector2 p_bottomPos= {0, 38};
	Vector2 p_bottomSize= {40, 18};
	auto p_bottom= std::make_shared<Panel>("CONTENT MANAGER", p_bottomPos, p_bottomSize, 8, font);
	static Texture2D woodpng= LoadTexture("resource/image/wood.png");
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "selam"));
	swanGui.AddPanel(p_bottom);

	Vector2 p_consolePos= {40, 38};
	Vector2 p_consoleSize= {24, 15};
	p_console= std::make_shared<Panel>("CONSOLE", p_consolePos, p_consoleSize, font);
	swanGui.AddPanel(p_console);

	Vector2 p_viewportPos= {0, 1};
	Vector2 p_viewportSize= {64, 37};
	auto p_viewport= std::make_shared<Panel>("VIEWPORT", p_viewportPos, p_viewportSize, false, 1, font);
	p_viewport->addElement(std::make_shared<CameraView3DFill>(camera, function, ui_panel_body));
	swanGui.AddPanel(p_viewport);

	Vector2 p_topPos= {0, 0};
	Vector2 p_topSize= {96, 1};
	auto p_top= std::make_shared<Panel>("p_top", p_topPos, p_topSize, false, 20, font);
	p_top->addElement(std::make_shared<Comment>("PINE ENGINE"));
	p_top->addElement(std::make_shared<Button>("Setting", [](){}, false));
	p_top->addElement(std::make_shared<Button>("Scenes", [](){}, false));
	p_top->addElement(std::make_shared<Button>("Themes", [](){}, false));
	swanGui.AddPanel(p_top);

	return swanGui;
}

void Renderer::RenderGui(SwanGui &swanGui, DeveloperConsole &developerConsole){
	swanGui.Update();
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && p_console->IsMouseOver()){
		developerConsole.Start();
	}
	if(IsKeyPressed(KEY_ESCAPE) && developerConsole.GetIsEnabled()){
		developerConsole.Exit();
	}
	swanGui.Draw();
}