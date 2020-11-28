#include "Block.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Collider.h"
#include "RotateComponent.h"


////////////////////// Class Block //////////////////////
Block::Block(Game* Game, vector2 position, int scale) :
	GameObject(Game, position, scale),
	mFilename(0)
{
	BoxCollider* box = new BoxCollider(this, 0);
}
Block::~Block() {

}
// �Ǝ��̍X�V�֐�
void Block::UpdateObject() {
}


/////////////// Class RotateBlock /////////////////
RotateBlock::RotateBlock(Game* Game, vector2 position, int scale) :
	Block(Game, position, scale),
	mFilename(0)
{
	mFilename = "Image/Block.png";
	TextureSprite* text = new TextureSprite(this, 0, mFilename);
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
}
WallBlock::~WallBlock() {

}


/////////////// Class Flag /////////////////
Flag::Flag(Game* game, vector2 position, int scale, int stage) :
	GameObject(game, position, scale),
	mStage(stage),
	mFilename(0),
	mCount(0)
{
	BoxCollider* box = new BoxCollider(this, 0, false);
	mFilename = "Image/Flag.png";
	TextureSprite* text = new TextureSprite(this, 0, mFilename);
}
Flag::~Flag() {

}
// �Ǝ��̍X�V�֐�
void Flag::UpdateObject(float deltaTime) {
	if (mCount < 10) {
		mCount += 1;
	}
}
// �X�e�[�W������]������
void Flag::RotateStage(int stagenum) {
	mGame->Rotate(stagenum);
}
// �����蔻��̂Ƃ��ɌĂ΂��֐�
void Flag::CollideDo() {
	if (mCount == 10) {
		RotateStage(mStage);
		cout << "aa" << endl;
	}
	mCount = 0;
}
