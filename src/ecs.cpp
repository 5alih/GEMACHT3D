#include "ecs.h"

void ECS::InitECS(float tick_rate){
	ecswan= ECSwan(tick_rate);

	auto ent0= ecswan.CreateEntity();
	ent0->AddComponent(std::make_shared<TransformComponent>( (Vector3){0, 0, 0}, 1.0f, (Vector3){0.01f, 0.0f, 0.015f} ));
}

void ECS::Update(float deltaTime){
	if(ecswan.Update(deltaTime)){
		for(auto ent: ecswan.m_entities){
			if(!ent->GetComponent<TransformComponent>()){
				ent->AddComponent(std::make_shared<TransformComponent>( (Vector3){0, 0, 0}, 1.0f, (Vector3){0.01f, 0.0f, 0.015f} ));
			}
		}
	}
}