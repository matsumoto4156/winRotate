#pragma once
#include "GameObject.h"

// ブロックの基底クラス
class Block : public GameObject {
public:
	Block(Game* game, vector2 position, int scale);
	virtual ~Block();
	// 独自の更新関数
	virtual void UpdateObject(float deltaTime) {};
	// 動きを止める
	virtual void IsKeynematic(float time) {};
	// 地面判定用（ORしてね）
	virtual bool GetGround() { return false; };
	// ぶつかった用（ORしてね）
	virtual void CollideDo(GameObject* target, int from) {};
	// センサーに引っかかるか
	virtual bool IsCencer() { return true; };
private:
	const char* mFilename;
};




//　回転するブロック
class RotateBlock : public Block {
public:
	RotateBlock(Game* Game, vector2 position, int scale);
	~RotateBlock();
private:
	const char* mFilename;
};


// 壁のブロック
class WallBlock : public Block {
public:
	WallBlock(Game* Game, vector2 position, int scale);
	~WallBlock();
private:
	const char* mFilename;
};


// くっつくブロック
class StickBlock : public Block {
public:
	StickBlock(Game* Game, vector2 position, int scale);
	~StickBlock();
	// 独自の更新関数
	void UpdateObject(float deltaTime);
	// 動きを止める
	void IsKeynematic(float time);
	// 地面判定
	bool GetGround() { return mGround; };
	void SetGround(bool ground) { mGround = ground; };

private:
	// テクスチャー
	class TextureSprite* mText;
	// 重力コンポ
	class GravityComponent* mGra;
	// 重力コンポ
	class BoxCollider* mBox;
	// 動きを止める時間
	float mWaitTime;
	// 地面についているか
	bool mGround;
	// ファイルメイ
	const char* mFilename;
	// 前のy
	float mPreY;
	// くっつくか
	bool mStick;
};

// 木箱ブロック
class CrateBlock : public Block {
public:
	CrateBlock(Game* Game, vector2 position, int scale);
	~CrateBlock();
	// 独自の更新関数
	void UpdateObject(float deltaTime);
	// 動きを止める
	void IsKeynematic(float time);
	// 地面判定
	bool GetGround() { return mGround; };
	void SetGround(bool ground) { mGround = ground; };
	// ぶつかったとき
	void CollideDo(GameObject* target, int from);
	// センサーに引っかかるか
	bool IsCencer() { return false; };
	
private:
	// 重力コンポ
	class GravityComponent* mGra;
	// 重力コンポ
	class BoxCollider* mBox;
	// 動きを止める時間
	float mWaitTime;
	// 地面についているか
	bool mGround;
	// ファイルメイ
	const char* mFilename;
	// 移動スピードと上限
	float mMoveSpeed;
	float mMaxSpeed;
};

// フラッグ
class Flag : public GameObject {
public:
	Flag(Game* game, vector2 position, int scale, int stage, const char* filename);
	~Flag();
	// 独自の更新関数
	void UpdateObject(float deltaTime);
	// ステージ時を回転させる
	void RotateStage(int stagenum);
	// 当たり判定のときに呼ばれる関数
	void CollideDo(GameObject* go, int from);
	// センサーに引っかかるか
	bool IsCencer() { return false; };
private:
	// どのステージを回転させるか
	int mStage;
	const char* mFilename;
	// 何フレーム待つか
	int mCount;
};
