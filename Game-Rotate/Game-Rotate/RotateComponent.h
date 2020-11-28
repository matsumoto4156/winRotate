#pragma once
#include "Component.h"
#include "vector2.h"

class RotateComponent :Component {
public:
	RotateComponent(class GameObject* owner, int updateOrder);
	~RotateComponent();
	// 座標を入れる
	void Initialize();
	// 回転
	void Rotate(float deltaTime);
	// 更新関数
	void Update(float deltaTime);
private:
	// 回転アニメーション
	float Move(float deltaTime);

	// ステージの座標
	vector2* mStageLoc;
	// 回転の度合い
	float mDeltaRotate;
	// 回転済みの量
	float mSumRotate;
	// 回転目標地点
	vector2 mToPosition;
	float mToRotation;
};