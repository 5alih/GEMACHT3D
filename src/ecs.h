#ifndef ECS_H
#define ECS_H

#include "my_functions.h"

//_______________________________________________________________ COMPONENTS ________________________________________________________________

enum componentsEnum{TRANSFORM_COMPONENT, HEALTH_COMPONENT};

struct TransformComponent{
	Vector2 position;
	Vector2 velocity;
};

struct HealthComponent{
	int healthPoints;
	int maxHealth;
	int regeneration;
};

//___________________________________________________________________________________________________________________________________________

class ECS;

class Entity {
public:
	int id;
	ECS* ecs;
	std::vector<int> component_types;
	std::vector<int> component_ids;

	int GetId();
	void SetId(int id);
	std::vector<int> GetComponentTypes();
	int GetComponentType(int index);
	std::vector<int> GetComponentIds();
	int GetComponentId(int index);
    Entity(ECS* ecsInstance) : ecs(ecsInstance) {}

    template <typename T>
    int AddComponent(int componentTypeId, const T &component);
	template <typename T>
    bool SetComponent(int componentTypeId, const T& newComponentData);
	void RemoveComponent(int componentTypeId);
};

class System {
public:
    virtual void Update(ECS& ecs) = 0; // Pure virtual function for updating components
};

class ECS {
public:
	std::vector<Entity> entities;
	int entityId = 0;
	std::unordered_map<int, std::vector<std::shared_ptr<void>>> componentArrays;	// Use an unordered_map to manage different component arrays
	std::vector<std::shared_ptr<System>> systems;  									// List of systems

	void Initialize();
	Entity CreateEntity();
	bool DeleteEntity(int id);
	void Update();
	void Shutdown();

    template <typename T>
    void RegisterComponentType(int componentTypeId);
	void AddSystem(std::shared_ptr<System> system);
};

template <typename T>
int Entity::AddComponent(int componentTypeId, const T& component) {
    if (ecs->componentArrays.find(componentTypeId) != ecs->componentArrays.end()) {
        auto& componentArray = ecs->componentArrays[componentTypeId];
        int componentId = componentArray.size();
        componentArray.push_back(std::make_shared<T>(component));
        this->component_types.push_back(componentTypeId);
        this->component_ids.push_back(componentId);
        return componentId;
    }
    return -1; // Error if component type not found
}

// Set or update the data of a component for an entity
template <typename T>
bool Entity::SetComponent(int componentTypeId, const T& newComponentData) {
    for (size_t i = 0; i < component_types.size(); ++i) {
        if (component_types[i] == componentTypeId) {
            int componentInstanceId = component_ids[i];
            auto& componentArray = ecs->componentArrays[componentTypeId];
            auto componentPtr = std::static_pointer_cast<T>(componentArray[componentInstanceId]);
            if (componentPtr) {
                *componentPtr = newComponentData;
                return true;  // Successfully updated the component
            }
        }
    }
    return false;  // Component not found or update failed
}

// Register a component type by ID
template <typename T>
void ECS::RegisterComponentType(int componentTypeId) {
    if (componentArrays.find(componentTypeId) == componentArrays.end()) {
        componentArrays[componentTypeId] = std::vector<std::shared_ptr<void>>();
    }
}

template <typename T>
std::shared_ptr<T> GetComponent(Entity& entity, int componentTypeId) {
    for (size_t i = 0; i < entity.component_types.size(); ++i) {
        if (entity.component_types[i] == componentTypeId) {
            int componentInstanceId = entity.component_ids[i];
            auto& componentArray = entity.ecs->componentArrays[componentTypeId];
            return std::static_pointer_cast<T>(componentArray[componentInstanceId]);
        }
    }
    return nullptr; // Component not found
}

//_________________________________________________________________ SYSTEMS _________________________________________________________________

class MovementSystem: public System {
public:
    void Update(ECS& ecs) override {
        for (Entity& entity : ecs.entities) {
            auto transformComponent = GetComponent<TransformComponent>(entity, TRANSFORM_COMPONENT);
            if (transformComponent) {
				transformComponent->position.x += transformComponent->velocity.x;
				transformComponent->position.y += transformComponent->velocity.y;
            }
        }
    }
};

class HealthSystem: public System {
public:
    void Update(ECS& ecs) override {
        for (Entity& entity : ecs.entities) {
            auto healthComponent = GetComponent<HealthComponent>(entity, HEALTH_COMPONENT);
            if (healthComponent) {
                if (healthComponent->maxHealth > healthComponent->healthPoints) {
                    healthComponent->healthPoints += healthComponent->regeneration;
                }
                if (healthComponent->healthPoints > healthComponent->maxHealth) {
                    healthComponent->healthPoints = healthComponent->maxHealth;
                }
            }
        }
    }
};

#endif // ECS_H
