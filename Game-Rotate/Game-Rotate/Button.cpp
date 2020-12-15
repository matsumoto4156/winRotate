#include "Button.h"
#include "SceneManager.h"
#include <string>



Button::Button(SceneManager* scmana, const char* filename, const char* filename_b) :
	mFilename(filename),
	mTexture(0),
	mNormalTexture(0),
	mPushTexture(0),
	mTextWidth(0),
	mTextHeight(0)
{
	mNormalTexture = scmana->SetTexture(mFilename);
	mPushTexture = scmana->SetTexture(filename_b);
	mTexture = mNormalTexture;
	if (!mTexture) {
		SDL_Log("テクスチャを得られませんでした");
	}
	// 画像の大きさを取得
	SDL_QueryTexture(mTexture, nullptr, nullptr, &mTextWidth, &mTextHeight);
}

Button::~Button() {

}

// 位置を決める
void Button::SetPosition(float x, float y) {
	if (mTextWidth == 0) {
		SDL_Log("Error Please Set Size!");
		return;
	}
	mPosition = { x, y };
	mLeftTop = mPosition - vector2{ static_cast<float>(mTextWidth / 2), static_cast<float>(mTextHeight / 2) };
	mRightDown = mPosition + vector2{ static_cast<float>(mTextWidth / 2), static_cast<float>(mTextHeight / 2) };
}

// ボタンが押されているか
bool Button::IsButton(int x, int y) {
	bool no = x < mLeftTop.x ||
		y < mLeftTop.y ||
		mRightDown.x < x ||
		mRightDown.y < y;

	if (!no) {
		mTexture = mPushTexture;
	}
	return !no;
}

// 描写
void Button::Draw(SDL_Renderer* renderer) {
	SDL_Rect back = { static_cast<int>(mLeftTop.x), static_cast<int>(mLeftTop.y), mTextWidth, mTextHeight };
	SDL_RenderCopyEx(
		renderer,
		mTexture,
		nullptr,
		&back,
		0,
		nullptr,
		SDL_FLIP_NONE
	);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawRect(renderer, &back);
}