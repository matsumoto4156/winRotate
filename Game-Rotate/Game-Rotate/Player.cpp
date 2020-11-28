#include "Player.h"
#include "SpriteComponent.h"
#include "SDL.h"
#include "PhisicManager.h"
#include "GravityComponent.h"
#include "Collider.h"
#include <algorithm>

Player::Player(Game* Game, vector2 position, int scale) :
	GameObject(Game, position, scale),
	mMoveSpeed(0.0f),
	mMaxSpeed(15.0f),
	mRightKey(SDL_SCANCODE_RIGHT),
	mLeftKey(SDL_SCANCODE_LEFT),
	mJumpKey(SDL_SCANCODE_SPACE),
	mDirection(1),
	mFilename(0),
	mCencer(0),
	mIsJump(true),
	mPlayerCollider(0)
{
	ResetSwitchTime();
	InitializeTexture();
	mPlayerCollider = new PlayerCollider(this, 0);
	GravityComponent* gr = new GravityComponent(this, 0);
}

Player::~Player() {

}
// �Ǝ��̍X�V�֐�
void Player::UpdateObject(float deltaTime) {
	//SDL_Log("%d", mCencer);

	if (mMoveSpeed != 0.0f) {
		// �O�ɂԂ���ƃX�s�[�h�啝��
		if (mCencer & FORWARD) {
			mMoveSpeed *= 0.5f;
		}
		else {
			// ������ς���
			mTexts[mTextNum]->SetFlip(mDirection);
			// �ړ��Ƃ��̃X�s�[�h�ɉ����ăX�v���C�g������
			mPosition.x += mDirection * mMoveSpeed * deltaTime;
			SwitchText(mMoveSpeed * deltaTime);
			mMoveSpeed *= 0.96f;
		}

		// 0�ɋ߂��Ƃ�0�ɂ���
		if (mMoveSpeed < 1.0f) {
			mMoveSpeed = 0.0f;
			ResetSwitchTime();
		}
	}
	if (mJumpForce != 0.0f) {
		if(mCencer & HEAD){
			mJumpForce *= 0.3f;
		}
		else {
			mPosition.y -= mJumpForce * deltaTime;
			mJumpForce -= 1.2f;
		}

		if (mJumpForce < 0.3f) {
			mJumpForce = 0.0f;
		}
	}


	// �O�ɂԂ���ƃX�s�[�h�啝��
	if (mCencer & FORWARD) {
		mMoveSpeed = 3.0f;
	}
}
// ���͂ɉ����ăI�u�W�F�N�g�𓮂���
void Player::InputMove(const uint8_t* keyState) {
	
	// �W�����v (�n�ʂ��O�̃t���[���ŉ�����Ă��Ȃ�)
	if (keyState[mJumpKey]){
		if ((mCencer & FOOT) && !mIsJump) {
			mJumpForce = 30.0f;
		}
		mIsJump = true;
	}
	else {
		mIsJump = false;
	}

	// �n�ʂɂ��Ă���Ƃ����ړ�
	if (mCencer & FOOT){
		if (keyState[mRightKey]) {
			// �����]��
			if (mDirection != 1) {
				mMoveSpeed = 0;
				mDirection = 1;
			}
			if (mMaxSpeed > mMoveSpeed) {
				mMoveSpeed += 3;
			}
		}
		else if (keyState[mLeftKey]) {
			// �����]��
			if (mDirection != -1) {
				mMoveSpeed = 0;
				mDirection = -1;
			}
			if (mMaxSpeed > mMoveSpeed) {
				mMoveSpeed += 5;
			}
		}
	}
}

void Player::SetPos(vector2 position){
	mPlayerCollider->SetLoc();
	mPosition = position;
}


// �e�N�X�`���[�����
void Player::InitializeTexture() {
	mFilename = "Image/Cat0.png";
	mTexts.emplace_back(new TextureSprite(this, 0, mFilename, false));
	mFilename = "Image/Cat1.png";
	mTexts.emplace_back(new TextureSprite(this, 0, mFilename, false));
	mFilename = "Image/Cat2.png";
	mTexts.emplace_back(new TextureSprite(this, 0, mFilename, false));
	mFilename = "Image/Cat3.png";
	mTexts.emplace_back(new TextureSprite(this, 0, mFilename, false));
	mTexts[mTextNum]->SetState(true);
}
// �X�v���C�g�ŃA�j���[�V����
void Player::SwitchText(float time) {
	mSwitchTime -= time;
	if (mSwitchTime < 0) {
		mTexts[mTextNum]->SetState(false);
		mTextNum = (mTextNum + 1) % 4;
		mTexts[mTextNum]->SetState(true);
		ResetSwitchTime();
	}
}