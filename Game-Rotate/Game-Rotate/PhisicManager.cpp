#include "PhisicManager.h"
#include "ColliderComponent.h"
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
	float dist[4] = { 1000.0f, 1100.0f,1200.0f,1300.0f };
	ColliderComponent* target[4] = { nullptr, nullptr, nullptr, nullptr };
	vector2 pos = mPlayerCollider->GetPos();

	for (auto b : mBoxes) {
		float a = mPlayer->GetPos().distance(b->GetPos());
		if (a < dist[3]) {
			int k = 3;
			while (dist[k-1] > a && k > 0) {
				dist[k] = dist[k - 1];
				target[k] = target[k - 1];
				k -= 1;
			}
			dist[k] = a;
			target[k] = b;
		}
	}
	if (target[1] == nullptr && target[2] == nullptr) {
		SDL_Log("No Block in Player Stage");
		return;
	}
	// �����蔻��Z���T�[�𓮂���
	unsigned char cencer = 0;
	for (int i = 0; i < 4; ++i) {
		int on = Adjust(mPlayerCollider, target[i]);
		if (on != 0) target[i]->GetOwner()->CollideDo(mPlayer, on);
		cencer |= Cencer(target[i]);
	}
	mPlayer->SetCencer(cencer);

	
	for (ColliderComponent* move : mMoves) {
		move->GetOwner()->SetGround(false);

		// �ł��߂����̂Ɠ����蔻����s��
		float dist[4] = { 1000.0f, 1100.0f,1200.0f,1300.0f };
		ColliderComponent* target[4] = { nullptr, nullptr, nullptr, nullptr };
		vector2 pos = move->GetPos();

		for (auto b : mBoxes) {
			float a = move->GetPos().distance(b->GetPos());
			if (a < dist[3] && a != 0) {
				int k = 3;
				while (dist[k - 1] > a && k > 0) {
					dist[k] = dist[k - 1];
					target[k] = target[k - 1];
					k -= 1;
				}
				dist[k] = a;
				target[k] = b;
			}
		}
		if (target[0] == nullptr && target[1] == nullptr) {
			SDL_Log("No Block in Block Stage");
			return;
		}
		// �����蔻��
		for (int i = 0; i < 4; ++i) {
			int on = Adjust(move, target[i]);
		}
	}

}



// �����蔻��(0�������ĂȂ��A1������A2�c����)
int PhisicManager::Adjust(ColliderComponent* move, ColliderComponent* target){
	// �n�ʔ���
	vector2 foot = move->GetPos();
	foot.y = move->GetLeftBottom().y + 2.0f;
	bool ground = target->GetLeftBottom().x <= foot.x &&
		foot.x <= target->GetRightTop().x &&
		target->GetRightTop().y <= foot.y &&
		foot.y <= target->GetLeftBottom().y;
	if (!move->GetOwner()->GetGround()) move->GetOwner()->SetGround(ground);


	bool no = move->GetRightTop().x < target->GetLeftBottom().x ||
		target->GetRightTop().x < move->GetLeftBottom().x ||
		move->GetRightTop().y > target->GetLeftBottom().y ||
		target->GetRightTop().y > move->GetLeftBottom().y;

	// �������Ă��Ȃ���ΏI��
	if (no) {
		return 0;
	}

	vector2 pos = move->GetOwner()->GetPos();
	// �������Ă�����ʒu�𒲐�
	float dx1 = move->GetRightTop().x - target->GetLeftBottom().x;
	float dx2 = move->GetLeftBottom().x - target->GetRightTop().x;
	float dy1 = move->GetRightTop().y - target->GetLeftBottom().y;
	float dy2 = move->GetLeftBottom().y - target->GetRightTop().y;
	// �ŏ��̋����𑪒�
	float dx = (std::abs(dx2) > std::abs(dx1)) ? dx1 : dx2; int a = 5;
	float dy;
	if (std::abs(dy2) < std::abs(dy1)) {
		dy = dy2;
	}
	else { dy = dy1; };


	int k = 0;
	// ������Փ�
	if (std::abs(dy) > std::abs(dx)) {
		pos.x -= dx;
		k = 1;
	}
	// �㉺����Փ�
	else {
		pos.y -= dy;
		k = 2;
	}

	// �Փ˂��Ȃ��Ƃ�cencer����Ȃ�
	if (!target->GetIsColl()) {
		return k;
	}
	move->GetOwner()->SetPos(pos);
	//�R���_�[���X�V
	move->SetLoc();
	return k;
}

// �Z���T�[����
unsigned char PhisicManager::Cencer(ColliderComponent* target) {
	if (!target->GetIsColl()) return 0;

	// �Z���T�[�t���b�O
	unsigned char cencer = 0;
	float height = (mPlayerCollider->GetLeftBottom().y - mPlayerCollider->GetRightTop().y) / 2;
	float width = (mPlayerCollider->GetRightTop().x - mPlayerCollider->GetLeftBottom().x) / 2;
	// �������Ă��邩����
	vector2 head;
	head.x = mPlayerCollider->GetPos().x;
	head.y = mPlayerCollider->GetRightTop().y - 3.0f;
	cencer |= target->GetLeftBottom().x <= head.x &&
		head.x <= target->GetRightTop().x &&
		target->GetRightTop().y <= head.y &&
		head.y <= target->GetLeftBottom().y;
	// �������Ă��邩����
	if (!target->GetOwner()->IsCencer()) cencer |= 0<<1;
	else {
		vector2 forward;
		float h = height - 4.0f;
		for (int i = 0; i < 3; ++i) {
			forward.x = mPlayerCollider->GetPos().x + (width + 0.1f) * mPlayer->GetDir();
			forward.y = mPlayerCollider->GetRightTop().y + 4.0f + h * i;
			cencer |= ((target->GetLeftBottom().x <= forward.x &&
				forward.x <= target->GetRightTop().x &&
				target->GetRightTop().y <= forward.y &&
				forward.y <= target->GetLeftBottom().y) << 1);
		}
	}
	// �n�ʂɂ��Ă��邩����
	vector2 foot;
	float w = width - 4.0f;
	for (int i = 0; i < 3; ++i) {
		foot.x = mPlayerCollider->GetLeftBottom().x + 4.0f + w*i;
		foot.y = mPlayerCollider->GetLeftBottom().y + 1.0f;
		cencer |= ((target->GetLeftBottom().x <= foot.x &&
			foot.x <= target->GetRightTop().x &&
			target->GetRightTop().y <= foot.y &&
			foot.y <= target->GetLeftBottom().y) << 2);
	}
	// ����������
	vector2 bottom;
	bottom.x = mPlayerCollider->GetPos().x;
	bottom.y = mPlayerCollider->GetLeftBottom().y + 2.0f;
	cencer |= ((target->GetLeftBottom().x <= bottom.x &&
		bottom.x <= target->GetRightTop().x &&
		target->GetRightTop().y <= bottom.y &&
		bottom.y <= target->GetLeftBottom().y) << 3);
	// �����O����
	if (!target->GetOwner()->IsCencer()) cencer |= 0 << 4;
	else {
		vector2 forwall;
		forwall.x = mPlayerCollider->GetPos().x + (width + 0.5f) * mPlayer->GetDir();
		forwall.y = mPlayerCollider->GetPos().y;
		cencer |= ((target->GetLeftBottom().x <= forwall.x &&
			forwall.x <= target->GetRightTop().x &&
			target->GetRightTop().y <= forwall.y &&
			forwall.y <= target->GetLeftBottom().y) << 4);
	}
	cencer |= 0 << 4;
	return cencer;
}

// �R���C�_�[��ǉ�
void PhisicManager::AddBox(ColliderComponent* box) {
	mBoxes.emplace_back(box);
}
// �R���C�_�[������
void PhisicManager::RemoveBox(ColliderComponent* box) { 
	auto iter = std::find(mBoxes.begin(), mBoxes.end(), box);
	if (iter != mBoxes.end()) {
		mBoxes.erase(iter);
	}
};

// �R���C�_�[��ǉ�
void PhisicManager::AddMove(ColliderComponent* box) {
	mMoves.emplace_back(box);
}
// �R���C�_�[������
void PhisicManager::RemoveMove(ColliderComponent* box) {
	auto iter = std::find(mMoves.begin(), mMoves.end(), box);
	if (iter != mMoves.end()) {
		mMoves.erase(iter);
	}
};