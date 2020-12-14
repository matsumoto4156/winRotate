#pragma once
#include "Component.h"
#include "vector2.h"


// �R���C�_�[�̊��N���X
class ColliderComponent :public Component {
public:
	ColliderComponent(class GameObject* owner, int updateOrder);
	virtual ~ColliderComponent();
	virtual void Update(float deltaTime) {};
	// ����Ăяo��
	void SetLoc();
	// �Ԃ��邩�ǂ���
	virtual bool GetIsColl() { return true; };
	// �Q�b�^�[
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
	// �X�V
	void Update(float deltaTime);
	// ���������ǂ���
	bool GetIsColl() { return mCollide; };
private:
	// �Փ˂��邩�����邩
	bool mCollide;
};

class PlayerCollider : public ColliderComponent {
public:
	PlayerCollider(GameObject* owner, int updateOrder);
	~PlayerCollider();
	// �X�V
	void Update(float deltaTime);
	unsigned char GetPlayerStage() { return mStageFlag; };
private:
	unsigned char mStageFlag;
};