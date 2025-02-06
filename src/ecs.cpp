#include "ecs.h"

ECSwan ECS::InitECS(float tick_rate){
	ecs= ECSwan(tick_rate);

	auto ent0= ecs.CreateEntity();
	ent0->AddComponent(std::make_shared<TransformComponent>( (Vector3){0, 0, 0}, 1.0f, (Vector3){0.5f, 1.0f, 0} ));

	return ecs;
}

void ECS::Update(float deltaTime){
	if(ecs.Update(deltaTime)){
		std::cout<<"pos x: " << ecs.m_entities[0]->GetComponent<TransformComponent>()->m_position.x<< std::endl;
		std::cout<<"pos y: " << ecs.m_entities[0]->GetComponent<TransformComponent>()->m_position.y<< std::endl;
		std::cout<<"pos z: " << ecs.m_entities[0]->GetComponent<TransformComponent>()->m_position.z<< std::endl<< std::endl;
	}
}