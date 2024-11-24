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

std::vector<int> Entity::GetComponentIds(){
	return this->component_ids;
}

	//find the component type by id
	//clone the component to type's array
	//save the newly generated component clone's id

void Entity::RemoveComponent(int ComponentTypeId){
	//remove component by id
	return;
}

//_______________________________________________________________________________________________//

// Initialize ECS
void ECS::Initialize() {
    entities.reserve(32);
}

// Create an entity and associate it with the ECS instance
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

void ECS::Update(){
	//update components
}

void ECS::Shutdown(){
	entities.clear();
}
