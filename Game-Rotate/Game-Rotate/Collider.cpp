#include "Collider.h"
#include "GameObject.h"
#include "Game.h"
#include "PhisicManager.h"


//////////////////// class BoxCollider ///////////////////////////
BoxCollider::BoxCollider(GameObject* owner, int updateOrder, bool isCollide) :
	Component(owner, updateOrder),
	mCollide(isCollide)
{
	mOwner->GetGame()->GetPManager()->AddBox(this);
}

BoxCollider::~BoxCollider() {
	mOwner->GetGame()->GetPManager()->RemoveBox(this);
}
// 更新
void BoxCollider::Update(float deltaTime) {
	SetLoc();
}
// 位置が変更されたときに呼び出す
void BoxCollider::SetLoc() {
	mPos = mOwner->GetPos();
	float scale = static_cast<float>(mOwner->GetScale());
	mRightTop = mPos - vector2{ -(scale / 2), scale / 2 };
	mLeftBottom = mPos + vector2{ -(scale / 2), scale / 2 };
}
// ぶつかっているとき呼ばれる
void BoxCollider::OnCollider() {
	mOwner->CollideDo();
}





//////////////////// class PlayerCollider ///////////////////////////
PlayerCollider::PlayerCollider(GameObject* owner, int updateOrder) :
	Component(owner, updateOrder)
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
// 位置が変更されたときに呼び出す
void PlayerCollider::SetLoc() {
	mPos = mOwner->GetPos();
	float scale = static_cast<float>(mOwner->GetScale());
	mRightTop = mPos - vector2{ -(scale / 2 - 5), scale / 2 - 10};
	mLeftBottom = mPos + vector2{ -(scale / 2 - 5), scale / 2 };
}

