#pragma once
#include "Component.h"

class GravityComponent : public Component {
public:
	GravityComponent(class GameObject* owner, int updateOrder);
	~GravityComponent();
	void Update(float deltaTime);
	float GetGravity() { return mGravity; };
	// 重力をとめたりする
	void Stop() { mOK = false; };
	void Start() { mOK = true; };
	// 重力のマックスを変更する
	void SetGravity(float gravity) { mMaxGravity = gravity; };
private:
	float mGravity;
	float mMaxGravity;
	bool mGround;
	bool mOK;
};