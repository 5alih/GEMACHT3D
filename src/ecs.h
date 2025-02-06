#ifndef ECS_H
#define ECS_H

#include "my_functions.h"
#include "ECSwan.h"

class ECS{
public:
	ECSwan ecs;

	ECSwan InitECS(float tick_rate);
	void Update(float deltaTime);
};

#endif // ECS_H