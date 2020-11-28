#pragma once
#include <vector>
#include "vector2.h"
#include "SDL.h"

class GameObject {
public:
	enum State {
		Active,
		Unactive
	};
	GameObject(class Game* game, vector2 position, int scale);
	virtual ~GameObject();

	// �Q�[������Ăяo�����X�V�֐��iOR�s�j
	void Update(float deltaTime);
	// �R���|�[�l���g���X�V�iOR�s�j
	void UpdateComponent(float deltaTime);
	// �Ǝ��̍X�V�֐��iOR�\)
	virtual void UpdateObject(float deltaTime);
	// ����������X�e�[�W�𔻒f
	void SetStagenum();
	// �����蔻��̂Ƃ��ɌĂ΂��֐�
	virtual void CollideDo();

	// �Q�b�^�[�E�Z�b�^�[
	void SetState(State state) { mState = state; };
	void SetPos(vector2 position) { mPosition = position; };
	void SetScale(int scale) { mScale = scale; };
	void SetRotation(float radian) { mRotation = radian; };
	void SetIsRotate(bool isRotate ) { mIsRotate = isRotate; };
	bool GetIsRotate() { return mIsRotate;  };
	State GetState() { return mState; };
	vector2 GetPos() { return mPosition; };
	int GetScale() { return mScale; };
	float GetRotation() { return mRotation; };
	Game* GetGame() { return mGame; };
	int GetStagenum() { return mStagenum; };
	// ���ۂɂ܂킷�̊֐�
	void Go(bool go) { if (mIsRotate)  mGo = go; };
	bool CanGo() { return mGo; }
	// �R���|�[�l���g�ǉ�����
	void AddComponent(class Component* Component);
	void RemoveComponent(class Component* Component);

	// �v���C���[�p�iOR���Ăˁj
	virtual bool GetGround() { return false; };
protected:
	// �I�u�W�F�N�g�̏��
	State mState;
	// ���W
	vector2 mPosition; // ���S
	int mScale;
	float mRotation; // ���W�A��
	// �I�u�W�F�N�g�����R���|�[�l���g
	std::vector<class Component*> mComponents;
	class Game* mGame;
	// ����������X�e�[�W
	int mStagenum;
	// ��邩
	bool mIsRotate;
	// ���ۂɉ�
	bool mGo;
};