#include "SpriteComponent.h"
#include "Game.h"
#include "GameObject.h"
#include <Math.h>


///////////////////////////// Sprite /////////////////////////////
SpriteComponent::SpriteComponent(class GameObject* owner, int updateOrder):
	Component(owner, updateOrder),
	mDrawOrder(1)
{
	mOwner->GetGame()->AddSprite(this);
}
SpriteComponent::~SpriteComponent() 
{
	mOwner->GetGame()->RemoveSprite(this);
}
void SpriteComponent::Draw(SDL_Renderer* renderer) {
}





///////////////////////////// Rect //////////////////////////////
RectSprite::RectSprite(class GameObject* owner, int updateOrder) :
	SpriteComponent(owner, updateOrder),
	mLendth(1)
{
	SetLoc();
}
RectSprite::~RectSprite() {
}
void RectSprite::Draw(SDL_Renderer* renderer) {
	// 色関係
	SDL_SetRenderDrawColor(renderer, mColor.red, mColor.blue, mColor.green, mColor.alpha);
	// 描写
	SDL_Rect back = { static_cast<int>(mLeftTop.x), static_cast<int>(mLeftTop.y), mLendth, mLendth };
	SDL_RenderFillRect(renderer, &back);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawRect(renderer, &back);
}
// 描写に必要な変数を確定
void RectSprite::SetLoc(){
	// ゲームオブジェクトからいろいろ取得
	vector2 pos = mOwner->GetPos();
	int scale = mOwner->GetScale();
	// 場所（標準スケールで座標1）
	mLeftTop.x = pos.x - scale / 2;
	mLeftTop.y = pos.y - scale / 2;
	mLendth = scale;
}


///////////////////////////// Texture //////////////////////////////
TextureSprite::TextureSprite(class GameObject* owner, int updateOrder, const char* filename, bool state):
	SpriteComponent(owner, updateOrder),
	mTexture(0),
	mTextWidth(0),
	mTextHeight(0),
	mState(state)
{
	mTexture = mOwner->GetGame()->GetTexture(filename);
	SetTexture();
}
TextureSprite::~TextureSprite() {
}
void TextureSprite::Draw(SDL_Renderer* renderer) {
	float ratio = mTextWidth*1.0f / mTextHeight;
	if (!mState) return;
	vector2 pos = mOwner->GetPos();
	vector2 leftTop;
	int scale = mOwner->GetScale();
	// 場所（標準スケールは1）
	leftTop.x = pos.x - (scale * ratio) / 2;
	leftTop.y = pos.y - scale / 2;
	SDL_Rect back = { static_cast<int>(leftTop.x), static_cast<int>(leftTop.y), static_cast<int>(scale*ratio), static_cast<int>(scale) };
	float deg = 180 * mOwner->GetRotation();
	SDL_RenderCopyEx(
		renderer,
		mTexture,
		nullptr,
		&back,
		deg,
		nullptr,
		mFlip
	);
	mOwner->SetWidth(scale * ratio);
	mOwner->SetHeight(scale * 1.0f);
}

// 画像の向きを変える
void TextureSprite::SetFlip(int dir) {
	if (dir == 1) {
		mFlip = SDL_FLIP_NONE;
	}
	else if (dir == -1){
		mFlip = SDL_FLIP_HORIZONTAL;
	}
	else {
		SDL_Log("DirectionError");
	}
}

// 画像サイズをセット
void TextureSprite::SetTexture() {
	SDL_QueryTexture(mTexture, nullptr, nullptr, &mTextWidth, &mTextHeight);
}