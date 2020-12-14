
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
	virtual void CollideDo(GameObject* go, int from) {};
	// �������~�߂�
	virtual void IsKeynematic(float time) {};


	// �Q�b�^�[�E�Z�b�^�[
	void SetState(State state) { mState = state; };
	void SetPos(vector2 position) { mPosition = position; };
	void SetScale(int scale) { mScale = scale; };
	void SetRotation(float radian) { mRotation = radian; };
	void SetIsRotate(bool isRotate ) { mIsRotate = isRotate; };
	void SetWidth(float width) { mWidth = width; };
	void SetHeight(float height) { mHeight = height; };
	float GetWidth() { return mWidth; };
	float GetHeight() { return mHeight; };
	bool GetIsRotate() { return mIsRotate;  };
	State GetState() { return mState; };
	vector2 GetPos() { return mPosition; };
	int GetScale() { return mScale; };
	float GetRotation() { return mRotation; };
	class Game* GetGame() { return mGame; };
	int GetStagenum() { return mStagenum; };
	// ���ۂɂ܂킷�̊֐�
	void Go(bool go) { mGo = go; };
	bool CanGo() { return mGo; }
	// �R���|�[�l���g�ǉ�����
	void AddComponent(class Component* Component);
	void RemoveComponent(class Component* Component);

	// �Z���T�[�Ɉ��������邩
	virtual bool IsCencer() { return true; };

	// �n�ʔ���p�iOR���Ăˁj
	virtual void SetGround(bool yes) {  };
	virtual bool GetGround() { return false; };
	// ���ҁ[��
	virtual float GetSpeed() { return 0.0f; };
protected:
	// �I�u�W�F�N�g�̏��
	State mState;
	// ���W
	vector2 mPosition; // ���S
	int mScale;
	//���E����
	float mWidth;
	float mHeight;
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