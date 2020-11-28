#pragma once
#include "Component.h"
#include "vector2.h"

class BoxCollider : public Component{
public:
	BoxCollider(GameObject* owner, int updateOrder, bool isCollide = true);
	~BoxCollider();
	// �X�V(����͈ʒu���ς�邱�Ƃ����Ȃ��̂ōs��Ȃ�)
	 void Update(float deltaTime);
	// �ʒu���ύX���ꂽ�Ƃ��ɌĂяo��
	void SetLoc();
	// �Ԃ����Ă���Ƃ��Ă΂��
	void OnCollider();
    // �Q�b�^�[
	vector2 GetPos() { return mPos; };
	vector2 GetRightTop() { return mRightTop; };
	vector2 GetLeftBottom() { return mLeftBottom; };
	bool GetIsColl() { return mCollide; };
private:
	vector2 mPos;
	vector2 mRightTop;
	vector2 mLeftBottom;
	// �Փ˂��邩�����邩
	bool mCollide;
};

class PlayerCollider : public Component {
public:
	PlayerCollider(GameObject* owner, int updateOrder);
	~PlayerCollider();
	// �X�V
	void Update(float deltaTime) override;
	// �ʒu���ύX���ꂽ�Ƃ��ɌĂяo��
	void SetLoc();
	// �Q�b�^�[
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