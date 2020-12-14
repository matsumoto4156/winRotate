#pragma once
#include "Component.h"
#include "vector2.h"


// コライダーの基底クラス
class ColliderComponent :public Component {
public:
	ColliderComponent(class GameObject* owner, int updateOrder);
	virtual ~ColliderComponent();
	virtual void Update(float deltaTime) {};
	// 毎回呼び出す
	void SetLoc();
	// ぶつかるかどうか
	virtual bool GetIsColl() { return true; };
	// ゲッター
	vector2 GetPos() { return mPos; };
	vector2 GetRightTop() { return mRightTop; };
	vector2 GetLeftBottom() { return mLeftBottom; };
protected:
	vector2 mPos;
	vector2 mRightTop;
	vector2 mLeftBottom;
};

class BoxCollider : public ColliderComponent{
public:
	BoxCollider(GameObject* owner, int updateOrder, bool isCollide = true);
	~BoxCollider();
	// 更新
	void Update(float deltaTime);
	// すかすかどうか
	bool GetIsColl() { return mCollide; };
private:
	// 衝突するか透けるか
	bool mCollide;
};

class PlayerCollider : public ColliderComponent {
public:
	PlayerCollider(GameObject* owner, int updateOrder);
	~PlayerCollider();
	// 更新
	void Update(float deltaTime);
	unsigned char GetPlayerStage() { return mStageFlag; };
private:
	unsigned char mStageFlag;
};