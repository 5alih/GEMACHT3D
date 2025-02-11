#include "scene.h"

inline ECSwan *g_ecswan;
inline LevelMaster *g_levelMaster;

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
	static Vector3 ent_pos;
	p_list->addElement(std::make_shared<SliderF>("Entity pos x", ent_pos.x, 0.1f, -20.0f, 20.0f));
	p_list->addElement(std::make_shared<SliderF>("Entity pos y", ent_pos.y, 0.1f, -20.0f, 20.0f));
	p_list->addElement(std::make_shared<SliderF>("Entity pos z", ent_pos.z, 0.1f, -20.0f, 20.0f));
	static int ent_size;
	p_list->addElement(std::make_shared<Slider>("Entity size", ent_size, 1, -20, 20));
	static Vector3 ent_vel;
	p_list->addElement(std::make_shared<SliderF>("Entity vel x", ent_vel.x, 0.01f, -20.0f, 20.0f));
	p_list->addElement(std::make_shared<SliderF>("Entity vel y", ent_vel.y, 0.01f, -20.0f, 20.0f));
	p_list->addElement(std::make_shared<SliderF>("Entity vel z", ent_vel.z, 0.01f, -20.0f, 20.0f));
	p_list->addElement(std::make_shared<Button>("Add Transform", [](){ g_ecswan->m_entities[ent_id]->AddComponent(std::make_shared<TransformComponent>(ent_pos, (float)ent_size, ent_vel)); }));
	p_list->addElement(std::make_shared<Button>("Save Level", [](){ g_levelMaster->SaveLevel(0); }, true));
	p_list->addElement(std::make_shared<Slider>("Current Level", levelMaster->m_current_level, 1, 0, 20));
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