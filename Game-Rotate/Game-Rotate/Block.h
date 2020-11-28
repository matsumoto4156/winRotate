#pragma once
#include "GameObject.h"

class Block : public GameObject {
public:
	Block(Game* game, vector2 position, int scale);
	~Block();
	// 独自の更新関数
	virtual void UpdateObject();
private:
	const char* mFilename;
};

class RotateBlock : public Block {
public:
	RotateBlock(Game* Game, vector2 position, int scale);
	~RotateBlock();

private:
	const char* mFilename;
};

class WallBlock : public Block {
public:
	WallBlock(Game* Game, vector2 position, int scale);
	~WallBlock();
private:
	const char* mFilename;
};


class Flag : GameObject {
public:
	Flag(Game* game, vector2 position, int scale, int stage);
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