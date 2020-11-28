#pragma once
#include "Component.h"
#include "vector2.h"

class RotateComponent :Component {
public:
	RotateComponent(class GameObject* owner, int updateOrder);
	~RotateComponent();
	// ���W������
	void Initialize();
	// ��]
	void Rotate(float deltaTime);
	// �X�V�֐�
	void Update(float deltaTime);
private:
	// ��]�A�j���[�V����
	float Move(float deltaTime);

	// �X�e�[�W�̍��W
	vector2* mStageLoc;
	// ��]�̓x����
	float mDeltaRotate;
	// ��]�ς݂̗�
	float mSumRotate;
	// ��]�ڕW�n�_
	vector2 mToPosition;
	float mToRotation;
};