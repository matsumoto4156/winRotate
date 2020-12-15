#include "Player.h"
#include "SpriteComponent.h"
#include "SDL.h"
#include "PhisicManager.h"
#include "GravityComponent.h"
#include "ColliderComponent.h"
#include <algorithm>

#include <iostream>

Player::Player(Game* Game, vector2 position, int scale) :
	GameObject(Game, position, scale),
	mMoveSpeed(0.0f),
	mMaxSpeed(450.0f),
	mRightKey(SDL_SCANCODE_RIGHT),
	mRightKey2(SDL_SCANCODE_D),
	mLeftKey(SDL_SCANCODE_LEFT),
	mLeftKey2(SDL_SCANCODE_A),
	mJumpKey(SDL_SCANCODE_SPACE),
	mDirection(1),
	mFilename(0),
	mCencer(0),
	mIsJump(true),
	mPlayerCollider(0),
	mWaitTime(0.0f)
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

		// �E�S�L���g����
	if (mWaitTime != 0.0f) {
		mWaitTime -= deltaTime;
		if (mWaitTime <= 0.0f) {
			mWaitTime = 0.0f;
			mCencer |= 4;
		}
		else return;
	}

	if (mMoveSpeed != 0.0f) {
		// �O�ɂԂ���ƃX�s�[�h�啝��
		if (((mCencer & FORWARD) && !(mCencer & BOTTOM)) || (mCencer & FORWALL)){
			mMoveSpeed -= 50.0f;
			//mJumpForce *= 0.3f;
		}

		// �ړ��Ƃ��̃X�s�[�h�ɉ����ăX�v���C�g������
		else {
			mPosition.x += mDirection * mMoveSpeed * deltaTime;
			SwitchText(mMoveSpeed * deltaTime);
			mMoveSpeed *= 0.94f;
		}

		// 0�ɋ߂��Ƃ�0�ɂ���
		if (mMoveSpeed < 5.0f) {
			mMoveSpeed = 0.0f;
			ResetSwitchTime();
		}
	}
	if (mJumpForce != 0.0f) {
		if(mCencer & HEAD){
			mJumpForce = 0.0f;
		}
		else {
			mPosition.y -= mJumpForce * deltaTime;
			mJumpForce -= 50.0f;
		}

		if (mJumpForce < 1.0f) {
			mJumpForce = 0.0f;
		}
	}

	// ������ς���
	mTexts[mTextNum]->SetFlip(mDirection);
}
// ���͂ɉ����ăI�u�W�F�N�g�𓮂���
void Player::InputMove(const uint8_t* keyState) {
	// �҂��̎��͎󂯕t���Ȃ�
	if (mWaitTime == 0.0f) {

		// �W�����v (�n�ʂ��O�̃t���[���ŉ�����Ă��Ȃ�)
		if (keyState[mJumpKey]) {
			if ((mCencer & BOTTOM) && !mIsJump) {
				mJumpForce = 1000.0f;
			}
			mIsJump = true;
		}
		else {
			mIsJump = false;
		}

		// ���ړ�
		if (keyState[mRightKey] || keyState[mLeftKey] || keyState[mRightKey2] || keyState[mLeftKey2]) {
			// �����]��
			if ((keyState[mRightKey] || keyState[mRightKey2]) && mDirection != 1) {
				mMoveSpeed = 0;
				mDirection = 1;
			}
			else if ((keyState[mLeftKey] || keyState[mLeftKey2]) && mDirection != -1) {
				mMoveSpeed = 0;
				mDirection = -1;
			}

			if (mMaxSpeed > mMoveSpeed) {
				if (mCencer & FOOT) {
					mMoveSpeed += 40.0f;
				}
				else {
					mMoveSpeed += 20.0f;
				}
			}
		}
	}
}

// �������~�߂�
void Player::IsKeynematic(float time) {
	mWaitTime = time;
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

	for (auto text : mTexts) {
		text->SetDrawOrder(5);
	}
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