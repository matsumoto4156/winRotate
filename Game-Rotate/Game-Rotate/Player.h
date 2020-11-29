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
	// 独自の更新関数
	void UpdateObject(float deltaTime);
	// 入力に応じてオブジェクトを動かす
	void InputMove(const uint8_t* keyState);
	// 動きを止める
	void IsKeynematic(float time);
	// 地面についているか判断
	void SetCencer(unsigned char cencer) { mCencer = cencer; };
	bool GetGround() { return mCencer & FOOT; };
	// プレイヤーの方向(1か-1か)
	int GetDir() { return mDirection; };
	void SetPos(vector2 position);
	void ResetSwitchTime() { mSwitchTime = 10.0f; };
	void Stop() { mCencer |= 2; };
private:
	// テクスチャーを作る
	void InitializeTexture();
	// スプライトでアニメーション
	void SwitchText(float time);

	// 画像ファイル名
	const char* mFilename;
	// 移動のためのキーコード
	int mRightKey;
	int mLeftKey;
	int mJumpKey;
	// 移動スピードと上限
	float mMoveSpeed;
	float mMaxSpeed;
	float mJumpForce;
	// 方向
	int mDirection;
	// テクスチャーの配列
	vector<class TextureSprite*> mTexts;
	// テクスチャーの交換たいみんぐ
	float mSwitchTime;
	// テクスチャーの番号
	int mTextNum;
	// 前のフレームでジャンプキーが押されていたか
	bool mIsJump;
	// センサー
	unsigned char mCencer;
	class PlayerCollider* mPlayerCollider;
	// 止める時間
	float mWaitTime;
};