#pragma once
#include "Component.h"
#include "vector2.h"

class BoxCollider : public Component{
public:
	BoxCollider(GameObject* owner, int updateOrder, bool isCollide = true);
	~BoxCollider();
	// 更新(今回は位置が変わることが少ないので行わない)
	 void Update(float deltaTime);
	// 位置が変更されたときに呼び出す
	void SetLoc();
	// ぶつかっているとき呼ばれる
	void OnCollider();
    // ゲッター
	vector2 GetPos() { return mPos; };
	vector2 GetRightTop() { return mRightTop; };
	vector2 GetLeftBottom() { return mLeftBottom; };
	bool GetIsColl() { return mCollide; };
private:
	vector2 mPos;
	vector2 mRightTop;
	vector2 mLeftBottom;
	// 衝突するか透けるか
	bool mCollide;
};

class PlayerCollider : public Component {
public:
	PlayerCollider(GameObject* owner, int updateOrder);
	~PlayerCollider();
	// 更新
	void Update(float deltaTime) override;
	// 位置が変更されたときに呼び出す
	void SetLoc();
	// ゲッター
	vector2 GetPos() { return mPos; };
	vector2 GetRightTop() { return mRightTop; };
	vector2 GetLeftBottom() { return mLeftBottom; };
	unsigned char GetPlayerStage() { return mStageFlag; };
private:
	vector2 mPos;
	vector2 mRightTop;
	vector2 mLeftBottom;
	unsigned char mStageFlag;
};