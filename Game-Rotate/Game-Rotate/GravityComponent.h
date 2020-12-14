#pragma once
#include "Component.h"

class GravityComponent : public Component {
public:
	GravityComponent(class GameObject* owner, int updateOrder);
	~GravityComponent();
	void Update(float deltaTime);
	float GetGravity() { return mGravity; };
	// �d�͂��Ƃ߂��肷��
	void Stop() { mOK = false; };
	void Start() { mOK = true; };
	// �d�͂̃}�b�N�X��ύX����
	void SetGravity(float gravity) { mMaxGravity = gravity; };
private:
	float mGravity;
	float mMaxGravity;
	bool mGround;
	bool mOK;
};