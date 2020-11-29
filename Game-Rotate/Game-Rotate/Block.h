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
	// 動きを止める時間
	float mWaitTime;
	// 地面についているか
	bool mGround;
	// ファイルメイ
	const char* mFilename;
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
	void CollideDo();
private:
	// どのステージを回転させるか
	int mStage;
	const char* mFilename;
	// 何フレーム待つか
	int mCount;
};
