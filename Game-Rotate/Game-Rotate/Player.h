#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
	enum Cencer {
		HEAD = 1,
		FORWARD = 2,
		FOOT = 4
	};
	Player(class Game* Game, vector2 position, int scale);
	~Player();
	// �Ǝ��̍X�V�֐�
	void UpdateObject(float deltaTime);
	// ���͂ɉ����ăI�u�W�F�N�g�𓮂���
	void InputMove(const uint8_t* keyState);
	// �������~�߂�
	void IsKeynematic(float time);
	// �n�ʂɂ��Ă��邩���f
	void SetCencer(unsigned char cencer) { mCencer = cencer; };
	bool GetGround() { return mCencer & FOOT; };
	// �v���C���[�̕���(1��-1��)
	int GetDir() { return mDirection; };
	void SetPos(vector2 position);
	void ResetSwitchTime() { mSwitchTime = 10.0f; };
	void Stop() { mCencer |= 2; };
private:
	// �e�N�X�`���[�����
	void InitializeTexture();
	// �X�v���C�g�ŃA�j���[�V����
	void SwitchText(float time);

	// �摜�t�@�C����
	const char* mFilename;
	// �ړ��̂��߂̃L�[�R�[�h
	int mRightKey;
	int mLeftKey;
	int mJumpKey;
	// �ړ��X�s�[�h�Ə��
	float mMoveSpeed;
	float mMaxSpeed;
	float mJumpForce;
	// ����
	int mDirection;
	// �e�N�X�`���[�̔z��
	vector<class TextureSprite*> mTexts;
	// �e�N�X�`���[�̌��������݂�
	float mSwitchTime;
	// �e�N�X�`���[�̔ԍ�
	int mTextNum;
	// �O�̃t���[���ŃW�����v�L�[��������Ă�����
	bool mIsJump;
	// �Z���T�[
	unsigned char mCencer;
	class PlayerCollider* mPlayerCollider;
	// �~�߂鎞��
	float mWaitTime;
};