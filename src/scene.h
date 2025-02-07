#ifndef SCENE_H
#define SCENE_H

#include "my_functions.h"
#include "swanGUI.h"
#include "ECSwan.h"
#include "level.h"

class Scene{
public:
	SwanGui m_gui;

	Scene(){}

	Scene(SwanGui gui){
		m_gui= gui;
	}
};

class SceneMaster{
public:
	int m_current_scene= 0;
	std::vector<Scene> m_scenes;
	std::shared_ptr<Panel> p_console;
	ECSwan *ecswan;

	SceneMaster(){}

	void InitGui(Font font);

	SwanGui GetGui(std::string scene_name);
};

#endif // SCENE_H