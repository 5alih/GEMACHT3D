#ifndef EDITOR_LEVEL_H
#define EDITOR_LEVEL_H

#include "scene.h"
#include "raymath.h"

inline ECSwan *g_ecswan;
inline Camera3D viewportCamera= {0};
inline Camera3D previewCamera= {0};
inline LevelMaster *g_levelMaster;
inline Vector3 hitBlock;
inline std::shared_ptr<Panel> g_panel;

inline auto drawSceneFunc= [](Camera3D& cam){
	DrawGrid(20, 2.0f);

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
	static Level *lvl= &g_levelMaster->m_levels[g_levelMaster->m_current_level];
	for(int x= 0; x< lvl->m_width; x++){
		for(int y= 0; y< lvl->m_height; y++){
			for(int z= 0; z< lvl->m_depth; z++){
				if(lvl->m_blocks[x][y][z].m_texture_id!= 0){
					DrawCube( (Vector3){(float)x +0.5f, (float)y +0.5f, (float)z +0.5f}, 1.0f, 1.0f, 1.0f, (Color){221,221,221,255} );
					DrawCubeWires( (Vector3){(float)x +0.5f, (float)y +0.5f, (float)z +0.5f}, 1.0f, 1.0f, 1.0f, BLACK );
				}
			}
		}
	}
	DrawCube(viewportCamera.position, 0.1f, 0.1f, 0.1f, WHITE);
	DrawCube(previewCamera.position, 0.1f, 0.1f, 0.1f, WHITE);

	if(hitBlock.x!= -1 && hitBlock.y!= -1 && hitBlock.z!= -1)
		DrawCubeWires( (Vector3){hitBlock.x +0.5f, hitBlock.y +0.5f, hitBlock.z +0.5f} , 1, 1, 1, WHITE);
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
		p_viewport->addElement(std::make_shared<CameraView3DFill>(viewportCamera, drawSceneFunc, (Color){100, 100, 100, 255} ));
		swanGui->AddPanel(p_viewport);
	
		Vector2 p_previewPos= {64, 1};
		Vector2 p_previewSize= {22, 18};
		auto p_preview= std::make_shared<Panel>("PREVIEW", p_previewPos, p_previewSize, font);
		p_preview->addElement(std::make_shared<CameraView3DFillBorder>(previewCamera, drawSceneFunc, (Color){100, 100, 100, 255}));
		swanGui->AddPanel(p_preview);

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
		std::cout<< dd_p_settings->m_position.x<< std::endl;
		std::cout<< dd_p_settings->m_position.y<< std::endl;
		
		static auto dd_p_scenes= std::make_shared<Panel>("dd_p_scenes", (Vector2){10.967, 1}, (Vector2){4.73, 1.85}, false, 1, font);
		dd_p_scenes->addElement(std::make_shared<Button>("Scene 1", [](){}, false));
		dd_p_scenes->addElement(std::make_shared<Button>("Scene 2", [](){}, false));
		dd_scenes->SetPanel(dd_p_scenes);
		
		static auto dd_p_themes= std::make_shared<Panel>("dd_p_themes", (Vector2){16.3, 1}, (Vector2){4.73, 1}, false, 1, font);
		dd_p_themes->addElement(std::make_shared<Button>("Dark Mode", [](){}, false));
		dd_themes->SetPanel(dd_p_themes);
	
		swanGui->AddPanel(p_top);

		g_panel= p_viewport;
	}
	
	Vector3 Raycast(Ray ray, int maxCalc, Vector3 &previous_block){
		Vector3 deltaDist;
		Vector3 step;
		Vector3 tMax;
	
		Level* lvl= &g_levelMaster->m_levels[g_levelMaster->m_current_level];
		int count= 0;
	
		step.x= (ray.direction.x> 0) ? 1 : -1;
		step.y= (ray.direction.y> 0) ? 1 : -1;
		step.z= (ray.direction.z> 0) ? 1 : -1;
	
		deltaDist.x= (ray.direction.x!= 0) ? fabs(1.0f/ray.direction.x) : FLT_MAX;
		deltaDist.y= (ray.direction.y!= 0) ? fabs(1.0f/ray.direction.y) : FLT_MAX;
		deltaDist.z= (ray.direction.z!= 0) ? fabs(1.0f/ray.direction.z) : FLT_MAX;
	
		if(step.x> 0)	tMax.x= (ceil(ray.position.x) -ray.position.x) *deltaDist.x;
		else			tMax.x= (ray.position.x -floor(ray.position.x)) *deltaDist.x;
	
		if(step.y> 0)	tMax.y= (ceil(ray.position.y) -ray.position.y) *deltaDist.y;
		else			tMax.y= (ray.position.y -floor(ray.position.y)) *deltaDist.y;
	
		if(step.z> 0)	tMax.z= (ceil(ray.position.z) -ray.position.z) *deltaDist.z;
		else			tMax.z= (ray.position.z -floor(ray.position.z)) *deltaDist.z;
	
		while(count< maxCalc){
			int x= static_cast<int>(ray.position.x);
			int y= static_cast<int>(ray.position.y);
			int z= static_cast<int>(ray.position.z);
	
			if(x< 0 || x>= lvl->m_width || y< 0 || y>= lvl->m_height || z< 0 || z>= lvl->m_depth)
				return Vector3{-1, -1, -1};
	
			if(lvl->m_blocks[x][y][z].m_texture_id!= 0)
				return Vector3{(float)x, (float)y, (float)z};
	
			previous_block.x= x;
			previous_block.y= y;
			previous_block.z= z;

			if(tMax.x< tMax.y && tMax.x< tMax.z){
				ray.position.x+= step.x;
				tMax.x+= deltaDist.x;
			}
			else if(tMax.y< tMax.z){
				ray.position.y+= step.y;
				tMax.y+= deltaDist.y;
			}
			else{
				ray.position.z+= step.z;
				tMax.z+= deltaDist.z;
			}
	
			count++;
		}
		return Vector3{-1, -1, -1};
	}

	void Update(){
		Ray ray;
		ray.position= viewportCamera.position;
		ray.direction= Vector3Normalize(Vector3Subtract(viewportCamera.target, viewportCamera.position));

		Vector3 preBlock= {-1, -1, -1};
		hitBlock= Raycast(ray, 100, preBlock);

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && hitBlock.x!= -1 && hitBlock.y!= -1 && hitBlock.z!= -1){
			levelMaster->GetCurrentLevel().m_blocks[hitBlock.x][hitBlock.y][hitBlock.z].m_texture_id= 0;
		}
		else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && preBlock.x!= -1 && preBlock.y!= -1 && preBlock.z!= -1){
			levelMaster->GetCurrentLevel().m_blocks[preBlock.x][preBlock.y][preBlock.z].m_texture_id= 1;
		}

		DrawRectangle((g_panel->m_position.x + g_panel->m_size.x/2.0f) -6, (g_panel->m_position.y + g_panel->m_size.y/2.0f) -1, 4, 2, WHITE);
		DrawRectangle((g_panel->m_position.x + g_panel->m_size.x/2.0f) +2, (g_panel->m_position.y + g_panel->m_size.y/2.0f) -1, 4, 2, WHITE);
		DrawRectangle((g_panel->m_position.x + g_panel->m_size.x/2.0f) -1, (g_panel->m_position.y + g_panel->m_size.y/2.0f) -6, 2, 4, WHITE);
		DrawRectangle((g_panel->m_position.x + g_panel->m_size.x/2.0f) -1, (g_panel->m_position.y + g_panel->m_size.y/2.0f) +2, 2, 4, WHITE);
	}
};

#endif // EDITOR_LEVEL_H