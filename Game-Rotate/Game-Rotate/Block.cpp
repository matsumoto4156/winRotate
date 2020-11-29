#include "Block.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "PhisicManager.h"
#include "ColliderComponent.h"
#include "RotateComponent.h"
#include "GravityComponent.h"


////////////////////// Class Block //////////////////////
Block::Block(Game* Game, vector2 position, int scale) :
	GameObject(Game, position, scale),
	mFilename(0)
{
}
Block::~Block() {

}


/////////////// Class RotateBlock /////////////////
RotateBlock::RotateBlock(Game* Game, vector2 position, int scale) :
	Block(Game, position, scale),
	mFilename(0)
{
	mFilename = "Image/Block.png";
	TextureSprite* text = new TextureSprite(this, 0, mFilename);
	BoxCollider* box = new BoxCollider(this, 0);
}
RotateBlock::~RotateBlock() {

}



/////////////// Class WallBlock /////////////////
WallBlock::WallBlock(Game* Game, vector2 position, int scale) :
	Block(Game, position, scale),
	mFilename(0)
{
	mFilename = "Image/Wall.png";
	TextureSprite* text = new TextureSprite(this, 0, mFilename);
	BoxCollider* box = new BoxCollider(this, 0);
}
WallBlock::~WallBlock() {

}



////////////// Class StickBlock /////////////////////
StickBlock::StickBlock(Game* Game, vector2 position, int scale) :
	Block(Game, position, scale) ,
	mWaitTime(0.0f),
	mFilename(0),
	mGround(0)
{
	mFilename = "Image/Stick.png";
	TextureSprite* text = new TextureSprite(this, 0, mFilename);
	GravityComponent* gra = new GravityComponent(this, 0);
	BoxCollider* box = new BoxCollider(this, 0);
	GetGame()->GetPManager()->AddMove(box);
}
StickBlock::~StickBlock() {

}

// 独自の更新関数
void StickBlock::UpdateObject(float deltaTime) {
	if (mWaitTime != 0.0f) {
		mWaitTime -= deltaTime;
		SetGround(true);
		//　時間がたったら 重力を戻す
		if (mWaitTime <= 0.0f) {
			mWaitTime = 0.0f;
			SetGround(false);
		}
	}
}
// 動きを止める
void StickBlock::IsKeynematic(float time) {
	mWaitTime = time;
}








/////////////// Class Flag /////////////////
Flag::Flag(Game* game, vector2 position, int scale, int stage, const char* filename) :
	GameObject(game, position, scale),
	mStage(stage),
	mFilename(filename),
	mCount(0)
{
	BoxCollider* box = new BoxCollider(this, 0, false);
	TextureSprite* text = new TextureSprite(this, 0, mFilename);
}
Flag::~Flag() {

}
// 独自の更新関数
void Flag::UpdateObject(float deltaTime) {
	if (mCount < 10) {
		mCount += 1;
	}
}
// ステージ時を回転させる
void Flag::RotateStage(int stagenum) {
	mGame->Rotate(stagenum);
}
// 当たり判定のときに呼ばれる関数
void Flag::CollideDo() {
	if (mCount == 10) {
		RotateStage(mStage);
	}
	mCount = 0;
}
