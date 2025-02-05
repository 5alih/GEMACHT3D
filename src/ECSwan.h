#ifndef ECSWAN_H
#define ECSWAN_H

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <sstream>
#include <iostream>
#include <cmath>
#include "raylib.h"

class Component{
public:
	virtual void Update()= 0;
	virtual ~Component()= default;
};

class TransformComponent: public Component{
public:
	Vector3 m_position;
	float m_size;
	Vector3 m_velocity;
	const float m_min_velocity= 0.001f;

	TransformComponent(Vector3 position, float size, Vector3 velocity){
		m_position= position;
		m_size= size;
		m_velocity= velocity;
	}

	float CalculateVelocity(){
		return std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y*m_velocity.y + m_velocity.z*m_velocity.z);
	}

	void Update() override{
		if(CalculateVelocity()> m_min_velocity){
			m_position.x+= m_velocity.x;
			m_position.y+= m_velocity.y;
			m_position.z+= m_velocity.z;
		}
	}
};

class Entity{
public:
	int m_id;
	std::vector<std::shared_ptr<Component>> m_components;

	Entity(int id){
		m_id= id;
	}

	void RemoveComponent(std::shared_ptr<Component> component){
		m_components.erase(
			std::remove(m_components.begin(), m_components.end(), component),
			m_components.end()
		);
	}

	void Update(){
		for(auto component: m_components){
			component->Update();
		}
	}

	template <typename T>
	void AddComponent(std::shared_ptr<T> component){
		static_assert(std::is_base_of<Component, T>::value, "Element must derive from Component");

		auto it= std::find(m_components.begin(), m_components.end(), component);
		if(it== m_components.end()){
			m_components.push_back(component);
		}
	}

	template <typename T>
	std::shared_ptr<T> GetComponent() {
		for (auto& component : m_components) {
			auto derived = std::dynamic_pointer_cast<T>(component);
			if (derived) {
				return derived;
			}
		}
		return nullptr;
	}
};

class ECSwan{
public:
	std::vector<std::shared_ptr<Entity>> m_entities;
	int m_entity_id= 0;

	ECSwan(){}

	std::shared_ptr<Entity> CreateEntity(){
		auto entity= std::make_shared<Entity>(m_entity_id++);
		m_entities.push_back(entity);
		return entity;
	}

	void RemoveEntity(std::shared_ptr<Entity> entity){
		m_entities.erase(
			std::remove(m_entities.begin(), m_entities.end(), entity),
			m_entities.end()
		);
	}

	void Update(){
		for(auto &entity: m_entities){
			entity->Update();
		}
	}
};

#endif // ECSWAN_H