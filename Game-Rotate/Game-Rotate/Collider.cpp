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
// �X�V
void BoxCollider::Update(float deltaTime) {
	SetLoc();
}
// �ʒu���ύX���ꂽ�Ƃ��ɌĂяo��
void BoxCollider::SetLoc() {
	mPos = mOwner->GetPos();
	float scale = static_cast<float>(mOwner->GetScale());
	mRightTop = mPos - vector2{ -(scale / 2), scale / 2 };
	mLeftBottom = mPos + vector2{ -(scale / 2), scale / 2 };
}
// �Ԃ����Ă���Ƃ��Ă΂��
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
// �X�V
void PlayerCollider::Update(float deltaTime) {
	// �ʒu���擾
	SetLoc();
	// �v���C���[�̈ʒu���X�V
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
// �ʒu���ύX���ꂽ�Ƃ��ɌĂяo��
void PlayerCollider::SetLoc() {
	mPos = mOwner->GetPos();
	float scale = static_cast<float>(mOwner->GetScale());
	mRightTop = mPos - vector2{ -(scale / 2 - 5), scale / 2 - 10};
	mLeftBottom = mPos + vector2{ -(scale / 2 - 5), scale / 2 };
}

