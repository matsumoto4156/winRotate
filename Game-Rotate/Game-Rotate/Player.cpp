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
	mMaxSpeed(500.0f),
	mRightKey(SDL_SCANCODE_RIGHT),
	mLeftKey(SDL_SCANCODE_LEFT),
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
// 独自の更新関数
void Player::UpdateObject(float deltaTime) {
	// ウゴキヲトメル
	if (mWaitTime != 0.0f) {
		mWaitTime -= deltaTime;
		if (mWaitTime <= 0.0f) {
			mWaitTime = 0.0f;
			mCencer |= 4;
		}
		else return;
	}

	if (mMoveSpeed != 0.0f) {
		// 前にぶつかるとスピード大幅減
		if (mCencer & FORWARD) {
			mMoveSpeed = 0.0f;
			mJumpForce *= 0.2f;
		}
		else {
			// 移動とそのスピードに応じてスプライトを交換
			mPosition.x += mDirection * mMoveSpeed * deltaTime;
			SwitchText(mMoveSpeed * deltaTime);
			mMoveSpeed *= 0.95f;
		}

		// 0に近いとき0にする
		if (mMoveSpeed < 5.0f) {
			mMoveSpeed = 0.0f;
			ResetSwitchTime();
		}
	}
	if (mJumpForce != 0.0f) {
		if(mCencer & HEAD){
			mJumpForce *= 0.2f;
		}
		else {
			mPosition.y -= mJumpForce * deltaTime;
			mJumpForce -= 40.0f;
		}

		if (mJumpForce < 1.0f) {
			mJumpForce = 0.0f;
		}
	}

	// 方向を変える
	mTexts[mTextNum]->SetFlip(mDirection);
}
// 入力に応じてオブジェクトを動かす
void Player::InputMove(const uint8_t* keyState) {
	
	// ジャンプ (地面かつ前のフレームで押されていない)
	if (keyState[mJumpKey]){
		if ((mCencer & FOOT) && !mIsJump) {
			mJumpForce = 1000.0f;
		}
		mIsJump = true;
	}
	else {
		mIsJump = false;
	}

	// 地面についているとき横移動
	if (mCencer & FOOT){
		if (keyState[mRightKey]) {
			// 方向転換
			if (mDirection != 1) {
				mMoveSpeed = 0;
				mDirection = 1;
			}
			if (mMaxSpeed > mMoveSpeed) {
				mMoveSpeed += 50;
			}
		}
		else if (keyState[mLeftKey]) {
			// 方向転換
			if (mDirection != -1) {
				mMoveSpeed = 0;
				mDirection = -1;
			}
			if (mMaxSpeed > mMoveSpeed) {
				mMoveSpeed += 50;
			}
		}
	}
}

// 動きを止める
void Player::IsKeynematic(float time) {
	mWaitTime = time;
}

void Player::SetPos(vector2 position){
	mPlayerCollider->SetLoc();
	mPosition = position;
}


// テクスチャーを作る
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
// スプライトでアニメーション
void Player::SwitchText(float time) {
	mSwitchTime -= time;
	if (mSwitchTime < 0) {
		mTexts[mTextNum]->SetState(false);
		mTextNum = (mTextNum + 1) % 4;
		mTexts[mTextNum]->SetState(true);
		ResetSwitchTime();
	}
}