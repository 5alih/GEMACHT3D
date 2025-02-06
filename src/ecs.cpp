#include "ecs.h"

void ECS::InitECS(float tick_rate){
	ecswan= ECSwan(tick_rate);

	auto ent0= ecswan.CreateEntity();
	ent0->AddComponent(std::make_shared<TransformComponent>( (Vector3){0, 0.5f, 0}, 1.0f, (Vector3){0.02f, 0.0f, 0.0f} ));
}

void ECS::Update(float deltaTime){
	ecswan.Update(deltaTime); // returns boolean value
}