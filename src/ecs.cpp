#include "ecs.h"

int Entity::GetId(){
	return this->id;
}

void Entity::SetId(int id){
	this->id= id;
}

std::vector<int> Entity::GetComponentTypes(){
	return this->component_types;
}

int Entity::GetComponentType(int index){
	return this->component_types[index];
}

std::vector<int> Entity::GetComponentIds(){
	return this->component_ids;
}

int Entity::GetComponentId(int index){
	return this->component_ids[index];
}


void Entity::RemoveComponent(int componentTypeId) {
    auto typeIt = std::find(component_types.begin(), component_types.end(), componentTypeId);
    if (typeIt != component_types.end()) {
        int index = std::distance(component_types.begin(), typeIt);
        int componentInstanceId = component_ids[index];
        if (ecs->componentArrays.find(componentTypeId) != ecs->componentArrays.end()) {
            auto& componentArray = ecs->componentArrays[componentTypeId];

            if ((size_t)componentInstanceId < componentArray.size()) {
                componentArray[componentInstanceId] = nullptr; // Avoid erasing to prevent index changes
            }
        }
        component_types.erase(typeIt);
        component_ids.erase(component_ids.begin() + index);
    }
}

void ECS::Initialize() {
    entities.reserve(32);

	this->RegisterComponentType<TransformComponent>(TRANSFORM_COMPONENT); // 0 is the type ID for TransformComponent

	this->AddSystem(std::make_shared<MovementSystem>());
	
	TransformComponent transform;
	transform.position = { 0.0f, 0.0f };
	transform.velocity = { 1.0f, 1.0f };
}

Entity ECS::CreateEntity() {
    Entity entity(this);  // Pass a pointer to the current ECS instance
    entity.SetId(entityId++);
    entities.push_back(entity);
    return entity;
}

void ECS::DeleteEntity(int id) {
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i].GetId() == id) {
            entities.erase(entities.begin() + i);
            return;
        }
    }
}

void ECS::Update() {
    for (auto& system : systems) {
        system->Update(*this);
    }
}

void ECS::Shutdown(){
	entities.clear();
}

void ECS::AddSystem(std::shared_ptr<System> system) {
    systems.push_back(system);
}
