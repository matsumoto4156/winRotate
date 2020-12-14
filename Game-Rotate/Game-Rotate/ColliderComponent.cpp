#include "ColliderComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "PhisicManager.h"

//////////////////// class Collider ///////////////////////////
ColliderComponent::ColliderComponent(class GameObject* owner, int updateOrder) :
	Component(owner, updateOrder)
{
}
ColliderComponent::~ColliderComponent() {

}
// 毎回呼び出す
void ColliderComponent::SetLoc(){
	mPos = mOwner->GetPos();
	mRightTop = mPos - vector2{ -(mOwner->GetWidth() / 2), mOwner->GetHeight() / 2 };
	mLeftBottom = mPos + vector2{ -(mOwner->GetWidth() / 2), mOwner->GetHeight() / 2 };
}



//////////////////// class BoxCollider ///////////////////////////
BoxCollider::BoxCollider(GameObject* owner, int updateOrder, bool isCollide) :
	ColliderComponent(owner, updateOrder),
	mCollide(isCollide)
{
	mOwner->GetGame()->GetPManager()->AddBox(this);
	SetLoc();
}

BoxCollider::~BoxCollider() {
	mOwner->GetGame()->GetPManager()->RemoveBox(this);
}
// 更新
void BoxCollider::Update(float deltaTime) {
	SetLoc();
}





//////////////////// class PlayerCollider ///////////////////////////
PlayerCollider::PlayerCollider(GameObject* owner, int updateOrder) :
	ColliderComponent(owner, updateOrder)
{
	SetLoc();
	Update(0.0f);
	mOwner->GetGame()->GetPManager()->SetPlayerCollider(this);
}

PlayerCollider::~PlayerCollider() {
}
// 更新
void PlayerCollider::Update(float deltaTime) {

	// 位置を取得
	SetLoc();
	// プレイヤーの位置を更新
	mStageFlag = 0;
	vector2 center = mOwner->GetGame()->GetStageLoc(1);
	if (mLeftBottom.x < center.x && center.y < mLeftBottom.y) {
		mStageFlag += 1;
	}
	if (center.x < mRightTop.x && center.y < mLeftBottom.y) {
		mStageFlag += 2;
	}
	if ( center.x < mRightTop.x && mRightTop.y < center.y) {
		mStageFlag += 4;
	}
	if ( center.x < mRightTop.x && mLeftBottom.y < center.y) {
		mStageFlag += 8;
	}

}

