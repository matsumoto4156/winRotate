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
	mGround(false),
	mGra(0),
	mBox(0),
	mText(0),
	mPreY(0),
	mStick(false)
{
	mFilename = "Image/Stick.png";
	mText = new TextureSprite(this, 0, mFilename);
	mText->SetDrawOrder(2);
	mGra = new GravityComponent(this, 0);
	mBox = new BoxCollider(this, 0);
	GetGame()->GetPManager()->AddMove(mBox);
	mPreY = GetPos().y;
}
StickBlock::~StickBlock() {
	delete[] mGra;
	mGra = 0;
	delete[] mBox;
	mBox = 0;
}

// 独自の更新関数
void StickBlock::UpdateObject(float deltaTime) {
	if (mWaitTime != 0.0f) {
		mWaitTime -= deltaTime;
		//　時間がたったら 重力を戻す
		if (mWaitTime <= 0.0f) {
			mWaitTime = 0.0f;
			mGra->Start();
			mStick = true;
		}
	}
	// くっつく
	else if (mStick &&  mGround) {
		mGame->RemoveSprite(mText);
		mFilename = "Image/Block.png";
		mText = new TextureSprite(this, 0, mFilename);
		mText->SetDrawOrder(2);

		RemoveComponent(mGra);
		GetGame()->GetPManager()->RemoveMove(mBox);
		SetStagenum();
		SetIsRotate(true);
		mStick = false;
	}
}
// 動きを止める
void StickBlock::IsKeynematic(float time) {
	mGra->Stop();
	mWaitTime = time;
}



////////////// Class CrateBlock /////////////////////
CrateBlock::CrateBlock(Game* Game, vector2 position, int scale) :
	Block(Game, position, scale),
	mWaitTime(0.0f),
	mFilename(0),
	mGround(false),
	mMoveSpeed(0),
	mMaxSpeed(50.0f),
	mGra(0),
	mBox(0)
{
	mFilename = "Image/Crate.png";
	TextureSprite* text = new TextureSprite(this, 0, mFilename);
	text->SetDrawOrder(2);
	mGra = new GravityComponent(this, 0);
	BoxCollider* box = new BoxCollider(this, 0);
	GetGame()->GetPManager()->AddMove(box);
}
CrateBlock::~CrateBlock() {
	delete[] mGra;
	mGra = 0;
	delete[] mBox;
	mBox = 0;
}

// 独自の更新関数
void CrateBlock::UpdateObject(float deltaTime) {
	if (mWaitTime != 0.0f) {
		mWaitTime -= deltaTime;
		//　時間がたったら 重力を戻す
		if (mWaitTime <= 0.0f) {
			mWaitTime = 0.0f;
			mGra->Start();
		}
	}
}

// 動きを止める
void CrateBlock::IsKeynematic(float time) {
	mGra->Stop();
	mWaitTime = time;
}
 
// 衝突したときうごく
void CrateBlock::CollideDo(GameObject* target, int from) {
	if (from == 1) {
		float a = target->GetSpeed() / 200;
		if (std::abs(a) > 1) mPosition.x += a;
	}
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
void Flag::CollideDo(GameObject* go, int from) {
	if (mCount == 10) {
		RotateStage(mStage);
	}
	mCount = 0;
}
