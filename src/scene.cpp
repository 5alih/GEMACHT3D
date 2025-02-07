#include "scene.h"

inline ECSwan *g_ecswan;

void SceneMaster::InitGui(Font font){
	SwanGui swanGui;
	g_ecswan= ecswan;

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
	p_list->addElement(std::make_shared<Button>("Create Entity", [](){ g_ecswan->CreateEntity(); }, false));
	static int ent_id;
	p_list->addElement(std::make_shared<Slider>("Selected Entity", ent_id, 1, 0, 100));
	static int ent_posx;
	static int ent_posy;
	static int ent_posz;
	p_list->addElement(std::make_shared<Slider>("Entity pos x", ent_posx, 1, -20, 20));
	p_list->addElement(std::make_shared<Slider>("Entity pos y", ent_posy, 1, -20, 20));
	p_list->addElement(std::make_shared<Slider>("Entity pos z", ent_posz, 1, -20, 20));
	static int ent_size;
	p_list->addElement(std::make_shared<Slider>("Entity size", ent_size, 1, -20, 20));
	static Vector3 ent_vel;
	p_list->addElement(std::make_shared<SliderF>("Entity vel x", ent_vel.x, 0.01f, -20.0f, 20.0f));
	p_list->addElement(std::make_shared<SliderF>("Entity vel y", ent_vel.y, 0.01f, -20.0f, 20.0f));
	p_list->addElement(std::make_shared<SliderF>("Entity vel z", ent_vel.z, 0.01f, -20.0f, 20.0f));
	p_list->addElement(std::make_shared<Button>("Add Transform", [](){ g_ecswan->m_entities[ent_id]->AddComponent(std::make_shared<TransformComponent>( (Vector3){(float)ent_posx, (float)ent_posy, (float)ent_posz}, (float)ent_size, ent_vel )); }));
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

	Scene scene(swanGui);
	m_scenes.push_back(scene);
}

SwanGui SceneMaster::GetGui(std::string scene_name){
	if(scene_name== "level_editor")	return m_scenes[0].m_gui;
	if(scene_name== "block_editor")	return m_scenes[1].m_gui;
	if(scene_name== "actor_editor")	return m_scenes[2].m_gui;
	SwanGui swangui;
	return swangui;
}