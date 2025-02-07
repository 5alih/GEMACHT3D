#ifndef EDITOR_LEVEL_H
#define EDITOR_LEVEL_H

#include "scene.h"

inline ECSwan *g_ecswan;
inline Camera3D viewportCamera= {0};
inline Camera3D previewCamera= {0};
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
	static Level *lvl= &g_levelMaster->m_levels[0];
	for(int x= 0; x< lvl->m_width; x++){
		for(int y= 0; y< lvl->m_height; y++){
			for(int z= 0; z< lvl->m_depth; z++){
				DrawCube( (Vector3){(float)x, (float)y, (float)z}, 0.5f, 0.5f, 0.5f, BLUE );
			}
		}
	}
	DrawCube(viewportCamera.position, 1.0f, 1.0f, 1.0f, BLACK);
	DrawCube(previewCamera.position, 1.0f, 1.0f, 1.0f, WHITE);
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

		viewportCamera.position= {0.0f, 2.0f, 4.0f};
		viewportCamera.target= {0.0f, 2.0f, 0.0f};
		viewportCamera.up= {0.0f, 1.0f, 0.0f};
		viewportCamera.fovy= 60.0f;
		viewportCamera.projection= CAMERA_PERSPECTIVE;

		previewCamera.position= {0.0f, 2.0f, 4.0f};
		previewCamera.target= {0.0f, 2.0f, 0.0f};
		previewCamera.up= {0.0f, 1.0f, 0.0f};
		previewCamera.fovy= 60.0f;
		previewCamera.projection= CAMERA_PERSPECTIVE;

		swanGui= &(sceneMaster->m_scenes[0].m_gui);

		Vector2 p_viewportPos= {0, 1};
		Vector2 p_viewportSize= {64, 37};
		auto p_viewport= std::make_shared<Panel>("VIEWPORT", p_viewportPos, p_viewportSize, false, 1, font);
		p_viewport->addElement(std::make_shared<CameraView3DFill>(viewportCamera, drawSceneFunc, ui_panel_body));
		swanGui->AddPanel(p_viewport);
	
		Vector2 p_previewPos= {64, 1};
		Vector2 p_previewSize= {22, 18};
		auto p_preview= std::make_shared<Panel>("PREVIEW", p_previewPos, p_previewSize, font);
		p_preview->addElement(std::make_shared<CameraView3DFillBorder>(previewCamera, drawSceneFunc, ui_panel_body));
		swanGui->AddPanel(p_preview);
	}

	void Update(){
		
	}
};

#endif // EDITOR_LEVEL_H