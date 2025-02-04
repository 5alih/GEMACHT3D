#include "renderer.h"

// auto dd_settings= std::make_shared<DropDown>("Settings", 0, 3);
// auto dd_scenes= std::make_shared<DropDown>("Scenes", 0, 3);
// auto dd_themes= std::make_shared<DropDown>("Themes", 0, 3);

auto drawSceneFunc= [](Camera3D& cam){
	DrawGrid(20, 2.0f);
	DrawCube( (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, (Color){243, 169, 78, 255} );
};

Camera3D playerCamera= {0};

void Renderer::RenderFPS(Color color){
	DrawText(to_const_char(to_string(GetFPS())), GetMonitorWidth(0) -20, 5, 10, color);
}

SwanGui Renderer::InitGui(Font font){
	SwanGui swanGui;

	playerCamera.position= {0.0f, 2.0f, 4.0f};
	playerCamera.target= {0.0f, 2.0f, 0.0f};
	playerCamera.up= {0.0f, 1.0f, 0.0f};
	playerCamera.fovy= 60.0f;
	playerCamera.projection= CAMERA_PERSPECTIVE;

	Vector2 p_settingsPos= {64, 19};
	Vector2 p_settingsSize= {22	, 35};
	auto p_settings= std::make_shared<Panel>("SETTINGS", p_settingsPos, p_settingsSize, 3, font);
	p_settings->addElement(std::make_shared<Button>("Create entity", [](){}, false));
	p_settings->addElement(std::make_shared<Button>("Delete entity", [](){}, false));
	p_settings->addElement(std::make_shared<Button>("Save entities", [](){}, true));
	swanGui.AddPanel(p_settings);

	Vector2 p_listPos= {86, 1};
	Vector2 p_listSize= {10, 52};
	auto p_list= std::make_shared<Panel>("ELEMENT LIST", p_listPos, p_listSize, font);
	swanGui.AddPanel(p_list);

	Vector2 p_bottomPos= {0, 38};
	Vector2 p_bottomSize= {40, 18};
	auto p_bottom= std::make_shared<Panel>("CONTENT MANAGER", p_bottomPos, p_bottomSize, 8, font);
	static Texture2D woodpng= LoadTexture("resource/image/wood.png");
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "select"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "select"));
	p_bottom->addElement(std::make_shared<Thumbnail>("wood", woodpng, [](){}, "select"));
	swanGui.AddPanel(p_bottom);

	Vector2 p_consolePos= {40, 38};
	Vector2 p_consoleSize= {24, 15};
	p_console= std::make_shared<Panel>("CONSOLE", p_consolePos, p_consoleSize, font);
	swanGui.AddPanel(p_console);

	Vector2 p_viewportPos= {0, 1};
	Vector2 p_viewportSize= {64, 37};
	auto p_viewport= std::make_shared<Panel>("VIEWPORT", p_viewportPos, p_viewportSize, false, 1, font);
	p_viewport->addElement(std::make_shared<CameraView3DFill>(playerCamera, drawSceneFunc, ui_panel_body));
	swanGui.AddPanel(p_viewport);

	Vector2 p_previewPos= {64, 1};
	Vector2 p_previewSize= {22, 18};
	auto p_preview= std::make_shared<Panel>("PREVIEW", p_previewPos, p_previewSize, font);
	p_preview->addElement(std::make_shared<CameraView3DFillBorder>(playerCamera, drawSceneFunc, ui_panel_body));
	swanGui.AddPanel(p_preview);

	Vector2 p_topPos= {0, 0};
	Vector2 p_topSize= {96, 1};
	auto p_top= std::make_shared<Panel>("p_top", p_topPos, p_topSize, false, 18, font);
	p_top->addElement(std::make_shared<Comment>("GEMACHT 3D"));

	auto dd_settings= std::make_shared<DropDown>("Settings", 0, 3);
	auto dd_scenes= std::make_shared<DropDown>("Scenes", 0, 2);
	auto dd_themes= std::make_shared<DropDown>("Themes", 0, 1);
	p_top->addElement(dd_settings);
	p_top->addElement(dd_scenes);
	p_top->addElement(dd_themes);

	static auto dd_p_settings= std::make_shared<Panel>("dd_p_settings", (Vector2){5.63, 1}, (Vector2){4.73, 3.55}, false, 1, font);
	dd_p_settings->addElement(std::make_shared<Button>("Overwrite", [](){}, false));
	dd_p_settings->addElement(std::make_shared<Button>("Reset", [](){}, false));
	dd_p_settings->addElement(std::make_shared<Button>("Discard", [](){}, false));
	dd_p_settings->addElement(std::make_shared<Button>("Save", [](){}, false));
	dd_settings->SetPanel(dd_p_settings);

	static auto dd_p_scenes= std::make_shared<Panel>("dd_p_scenes", (Vector2){10.967, 1}, (Vector2){4.73, 1.85}, false, 1, font);
	dd_p_scenes->addElement(std::make_shared<Button>("Scene 1", [](){}, false));
	dd_p_scenes->addElement(std::make_shared<Button>("Scene 2", [](){}, false));
	dd_scenes->SetPanel(dd_p_scenes);

	static auto dd_p_themes= std::make_shared<Panel>("dd_p_themes", (Vector2){16.3, 1}, (Vector2){4.73, 1}, false, 1, font);
	dd_p_themes->addElement(std::make_shared<Button>("Dark Mode", [](){}, false));
	dd_themes->SetPanel(dd_p_themes);

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

	// dd_settings->PrintDimensions();
	// dd_scenes->PrintDimensions();
	// dd_themes->PrintDimensions();

	swanGui.Draw();
}