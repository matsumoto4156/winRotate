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
// ���W������
void RotateComponent::Initialize() {
	mStageLoc = new vector2[4];
	mStageLoc[0] = { 312, 650 };
	mStageLoc[1] = { 712, 650 };
	mStageLoc[2] = { 712, 250 };
	mStageLoc[3] = { 312, 250 };
}

// ��]
void RotateComponent::Rotate(float deltaTime){
	if (mOwner->CanGo()) {

		// �ڕW�n�_�Ȃǂ����߂�i�ŏ������s���j
		if (mSumRotate == 0.0f) {
			int num = mOwner->GetStagenum();
			mToPosition = mOwner->GetPos();
			// (x,y)�𒆐S����̍��W�ɕϊ�
			mToPosition.x -= mStageLoc[num].x;
			mToPosition.y -= mStageLoc[num].y;
			float a = mToPosition.x;
			float b = mToPosition.y;
			// ��]
			mToPosition.x = a * static_cast<float>(cos(0.5 * M_PI)) - b * static_cast<float>(sin(0.5 * M_PI));
			mToPosition.y = b * static_cast<float>(cos(0.5 * M_PI)) + a * static_cast<float>(sin(0.5 * M_PI));
			mToRotation = mOwner->GetRotation() + 0.5f;
			// ���W�����ɖ߂�
			mToPosition.x += mStageLoc[num].x;
			mToPosition.y += mStageLoc[num].y;

			// ��]�ʂ�ݒ�
			mSumRotate = 0.5f;
		}
		// ��]����
		mSumRotate -= Move(deltaTime);
		// ���m�Ȉʒu�Ɉړ�����]���~�߂�
		if (mSumRotate <= 0) {
			mSumRotate = 0.0f;
			mOwner->SetPos(mToPosition);
			mOwner->SetRotation(mToRotation);
			mOwner->Go(false);
		}
	}
}

// ��]�A�j���[�V����
float RotateComponent::Move(float deltaTime) {
	float delta = mDeltaRotate * deltaTime;
	vector2 pos = mOwner->GetPos();
	int num = mOwner->GetStagenum();
	// (x,y)�𒆐S����̍��W�ɕϊ�
	pos.x -= mStageLoc[num].x;
	pos.y -= mStageLoc[num].y;
	float a = pos.x;
	float b = pos.y;
	// ��]
	pos.x = a * static_cast<float>(cos(delta * M_PI)) - b * static_cast<float>(sin(delta * M_PI));
	pos.y = b * static_cast<float>(cos(delta * M_PI)) + a * static_cast<float>(sin(delta * M_PI));
	// ���W�����ɖ߂�
	pos.x += mStageLoc[num].x;
	pos.y += mStageLoc[num].y;
	mOwner->SetPos(pos);
	mOwner->SetRotation(mOwner->GetRotation() + delta);

	return delta;
}

// �X�V�֐�
void RotateComponent::Update(float deltaTime) {
	Rotate(deltaTime);
}