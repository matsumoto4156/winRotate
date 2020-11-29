#include "RotateComponent.h"
#include "GameObject.h"
#include "Game.h"
#include <cmath>


RotateComponent::RotateComponent(class GameObject* owner, int updateOrder) :
	Component(owner, updateOrder),
	mStageLoc(0),
	mDeltaRotate(70 / 180.0f),
	mSumRotate(0.0f),
	mToRotation(0.0f)
{
	Initialize();
}

RotateComponent::~RotateComponent() {

}
// 座標を入れる
void RotateComponent::Initialize() {
	mStageLoc = new vector2[4];
	mStageLoc[0] = { 312, 650 };
	mStageLoc[1] = { 712, 650 };
	mStageLoc[2] = { 712, 250 };
	mStageLoc[3] = { 312, 250 };
}

// 回転
void RotateComponent::Rotate(float deltaTime){
	if (mOwner->CanGo()) {

		// 目標地点などを決める（最初だけ行う）
		if (mSumRotate == 0.0f) {
			int num = mOwner->GetStagenum();
			mToPosition = mOwner->GetPos();
			// (x,y)を中心からの座標に変換
			mToPosition.x -= mStageLoc[num].x;
			mToPosition.y -= mStageLoc[num].y;
			float a = mToPosition.x;
			float b = mToPosition.y;
			// 回転
			mToPosition.x = a * static_cast<float>(cos(0.5 * M_PI)) - b * static_cast<float>(sin(0.5 * M_PI));
			mToPosition.y = b * static_cast<float>(cos(0.5 * M_PI)) + a * static_cast<float>(sin(0.5 * M_PI));
			mToRotation = mOwner->GetRotation() + 0.5f;
			// 座標を元に戻す
			mToPosition.x += mStageLoc[num].x;
			mToPosition.y += mStageLoc[num].y;

			// 回転量を設定
			mSumRotate = 0.5f;
		}
		// 回転する
		mSumRotate -= Move(deltaTime);
		// 正確な位置に移動し回転を止める
		if (mSumRotate <= 0) {
			mSumRotate = 0.0f;
			mOwner->SetPos(mToPosition);
			mOwner->SetRotation(mToRotation);
			mOwner->Go(false);
		}
	}
}

// 回転アニメーション
float RotateComponent::Move(float deltaTime) {
	float delta = mDeltaRotate * deltaTime;
	vector2 pos = mOwner->GetPos();
	int num = mOwner->GetStagenum();
	// (x,y)を中心からの座標に変換
	pos.x -= mStageLoc[num].x;
	pos.y -= mStageLoc[num].y;
	float a = pos.x;
	float b = pos.y;
	// 回転
	pos.x = a * static_cast<float>(cos(delta * M_PI)) - b * static_cast<float>(sin(delta * M_PI));
	pos.y = b * static_cast<float>(cos(delta * M_PI)) + a * static_cast<float>(sin(delta * M_PI));
	// 座標を元に戻す
	pos.x += mStageLoc[num].x;
	pos.y += mStageLoc[num].y;
	mOwner->SetPos(pos);
	mOwner->SetRotation(mOwner->GetRotation() + delta);

	return delta;
}

// 更新関数
void RotateComponent::Update(float deltaTime) {
	Rotate(deltaTime);
}