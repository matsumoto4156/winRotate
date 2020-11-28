#pragma once
#include "Component.h"

class GravityComponent : public Component {
public:
	GravityComponent(class GameObject* owner, int updateOrder);
	~GravityComponent();
	void Update(float deltaTime);
private:
	float mGravity;
	float mMaxGravity;
	bool mGround;
};