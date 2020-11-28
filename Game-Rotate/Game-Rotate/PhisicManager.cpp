#include "PhisicManager.h"
#include "Collider.h"
#include "Player.h"
#include <vector>
#include <algorithm>

#include <iostream>

PhisicManager::PhisicManager() :
	mPlayerCollider(0),
	mPlayer(0)
{
}
PhisicManager::~PhisicManager() {

}
// �ł��߂����̂Ɠ����蔻��E�v���C���[�̈ʒu�𒲐�
void PhisicManager::ManagePlayer() {

	// �ł��߂����̂Ɠ����蔻����s��
	float dist1 = 1000.0f;
	float dist2 = 1100.0f;
	BoxCollider* target1 = nullptr;
	BoxCollider* target2 = nullptr;
	vector2 pos = mPlayerCollider->GetPos();

	unsigned char flag = mPlayerCollider->GetPlayerStage();
	for (auto b : mBoxes) {
		if ((flag & static_cast<unsigned char>(pow(2,(b->GetOwner()->GetStagenum())))) != 0) {
			float a = mPlayer->GetPos().distance(b->GetPos());
			if (a < dist2) {
				if (a < dist1) {
					dist2 = dist1;
					dist1 = a;
					target2 = target1;
					target1 = b;
				}
				else {
					dist2 = a;
					target2 = b;
				}
			}
		}
	}
	if (target1 == nullptr && target2 == nullptr) {
		SDL_Log("No Block in Player Stage");
		return;
	}
	// �����蔻��̌��ʂ�n�ʔ���Ƃ��Ď󂯎��
	unsigned char cencer = Adjust(target1) | Adjust(target2);
	mPlayer->SetCencer(cencer);
}

// �����蔻��
unsigned char PhisicManager::Adjust(class BoxCollider* target){

	// �Z���T�[�t���b�O
	unsigned char cencer = 0;
	// �������Ă��邩����
	vector2 head;
	head.x = mPlayerCollider->GetPos().x;
	head.y = mPlayerCollider->GetRightTop().y - 0.3f;
	cencer |= target->GetLeftBottom().x <= head.x &&
		head.x <= target->GetRightTop().x &&
		target->GetRightTop().y <= head.y &&
		head.y <= target->GetLeftBottom().y;
	// �n�ʂɂ��Ă��邩����
	vector2 forward;
	forward.x = mPlayerCollider->GetPos().x + ((mPlayer->GetScale() / 2 + 0.1f) * mPlayer->GetDir());
	forward.y = mPlayerCollider->GetPos().y;
	cencer |= ((target->GetLeftBottom().x <= forward.x &&
		forward.x <= target->GetRightTop().x &&
		target->GetRightTop().y <= forward.y &&
		forward.y <= target->GetLeftBottom().y) << 1);
	// �n�ʂɂ��Ă��邩����
	vector2 foot;
	foot.x = mPlayerCollider->GetPos().x;
	foot.y = mPlayerCollider->GetLeftBottom().y + 0.5f;
	cencer |= ((target->GetLeftBottom().x <= foot.x &&
		foot.x <= target->GetRightTop().x &&
		target->GetRightTop().y <= foot.y &&
		foot.y <= target->GetLeftBottom().y) << 2);

	PlayerCollider* p = mPlayerCollider;
	//bool no = p->GetRightTop().y < b->GetLeftBottom().y;
	bool no = p->GetRightTop().x < target->GetLeftBottom().x ||
		target->GetRightTop().x < p->GetLeftBottom().x ||
		p->GetRightTop().y > target->GetLeftBottom().y ||
		target->GetRightTop().y > p->GetLeftBottom().y;

	// �������Ă��Ȃ���ΏI��
	if (no) {
		return cencer;
	}
	// �������Ă���Ƃ��֐�
	target->OnCollider();
	if (!target->GetIsColl()) {
		cencer = 0;
		return cencer;
	}
	// �������Ă�����ʒu�𒲐�
	float dx1 = mPlayerCollider->GetRightTop().x - target->GetLeftBottom().x;
	float dx2 = mPlayerCollider->GetLeftBottom().x - target->GetRightTop().x;
	float dy1 = mPlayerCollider->GetRightTop().y - target->GetLeftBottom().y;
	float dy2 = mPlayerCollider->GetLeftBottom().y - target->GetRightTop().y;
	// �ŏ��̋����𑪒�
	float dx = (std::abs(dx2) > std::abs(dx1)) ? dx1 : dx2; int a = 5;
	float dy;
	bool check = false;
	if (std::abs(dy2) < std::abs(dy1)) {
		dy = dy2;
		check = true;
	}
	else { dy = dy1; };
	if (std::abs(dy) > std::abs(dx)) {
		vector2 pos = mPlayer->GetPos();
		pos.x -= dx;
		mPlayer->SetPos(pos);
	}
	else {
		if (check) {
			cencer |= check << 2;
		}
		vector2 pos = mPlayer->GetPos();
		pos.y -= dy;
		mPlayer->SetPos(pos);
	}
	// �v���C���[�̃R���_�[���X�V
	mPlayerCollider->SetLoc();
	return cencer;
}

// �R���C�_�[��ǉ�
void PhisicManager::AddBox(class BoxCollider* box) {
	mBoxes.emplace_back(box);
}
// �R���C�_�[������
void PhisicManager::RemoveBox(class BoxCollider* box) { 
	auto iter = std::find(mBoxes.begin(), mBoxes.end(), box);
	if (iter != mBoxes.end()) {
		mBoxes.erase(iter);
	}
};