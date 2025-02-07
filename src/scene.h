#ifndef SCENE_H
#define SCENE_H

#include "my_functions.h"
#include "swanGUI.h"
#include "ECSwan.h"

class Scene{
public:
	SwanGui gui;

	Scene(){}
};

class SceneMaster{
public:
	int m_current_scene;
	std::vector<Scene> m_scenes;
	std::shared_ptr<Panel> p_console;
	ECSwan *ecswan;

	SceneMaster(){}

	SwanGui InitGui(Font font);
};

#endif // SCENE_H