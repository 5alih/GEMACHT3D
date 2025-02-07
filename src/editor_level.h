#ifndef EDITOR_LEVEL_H
#define EDITOR_LEVEL_H

#include "scene.h"

inline ECSwan *g_ecswan;
inline Camera3D playerCamera= {0};
inline LevelMaster *g_levelMaster;

inline auto drawSceneFunc= [](Camera3D& cam){
	DrawGrid(20, 2.0f);
	DrawCube( (Vector3){0.0f, 0.5f, 0.0f}, 1.0f, 1.0f, 1.0f, (Color){243, 169, 78, 255} );

	static bool is_up= true;
	static unsigned char a= 0;
	if(a>= 255) is_up= false;
	if(a<= 0)	is_up= true;
	if(is_up) a++;
	else	  a--;

	for(auto entity: g_ecswan->m_entities){
		if(entity->GetComponent<TransformComponent>()){
			float s= entity->GetComponent<TransformComponent>()->m_size;
			DrawCube(entity->GetComponent<TransformComponent>()->m_position, s, s, s, (Color){ (unsigned char)(255 -a), 255, a, 255} );
		}
	}
	static bool is= true;
	if(is){
		Level lvl(10, 10, 10);
		for(int x= 0; x< lvl.m_width; x++){
			for(int y= 0; y< lvl.m_height; y++){
				for(int z= 0; z< lvl.m_depth; z++){
					if(x%2== 0 && y%5== 0 && z%3== 0)
						lvl.m_blocks[x][y][z].m_texture_id= 1;
				}
			}
		}
		g_levelMaster->AddLevel(lvl);
		is= false;
	}

	static Level *lvl= &g_levelMaster->m_levels[0];
	for(int x= 0; x< lvl->m_width; x++){
		for(int y= 0; y< lvl->m_height; y++){
			for(int z= 0; z< lvl->m_depth; z++){
				if(lvl->m_blocks[x][y][z].m_texture_id!= 0){
					DrawCube( (Vector3){(float)x, (float)y, (float)z}, 1.0f, 1.0f, 1.0f, RED );
				}
			}
		}
	}
};

class LevelEditor{
public:
	SceneMaster *sceneMaster;
	LevelMaster *levelMaster;
	SwanGui *swanGui;
	ECSwan *ecswan;

	LevelEditor(){}

	void InitEditor(Font font){
		g_ecswan= ecswan;
		g_levelMaster= levelMaster;

		playerCamera.position= {0.0f, 2.0f, 4.0f};
		playerCamera.target= {0.0f, 2.0f, 0.0f};
		playerCamera.up= {0.0f, 1.0f, 0.0f};
		playerCamera.fovy= 60.0f;
		playerCamera.projection= CAMERA_PERSPECTIVE;

		swanGui= &(sceneMaster->m_scenes[0].m_gui);

		Vector2 p_viewportPos= {0, 1};
		Vector2 p_viewportSize= {64, 37};
		auto p_viewport= std::make_shared<Panel>("VIEWPORT", p_viewportPos, p_viewportSize, false, 1, font);
		p_viewport->addElement(std::make_shared<CameraView3DFill>(playerCamera, drawSceneFunc, ui_panel_body));
		swanGui->AddPanel(p_viewport);
	
		Vector2 p_previewPos= {64, 1};
		Vector2 p_previewSize= {22, 18};
		auto p_preview= std::make_shared<Panel>("PREVIEW", p_previewPos, p_previewSize, font);
		p_preview->addElement(std::make_shared<CameraView3DFillBorder>(playerCamera, drawSceneFunc, ui_panel_body));
		swanGui->AddPanel(p_preview);
	}
};

#endif // EDITOR_LEVEL_H