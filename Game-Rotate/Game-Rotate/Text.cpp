#include "Text.h"

#include <iostream>


Text::Text(const char* str, SDL_Renderer* renderer, int size):
	mStr(str),
	mText(0),
	mTextWidth(0),
	mTextHeight(0)
{
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("Font/meiryo.ttc", size);
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, str, SDL_Color{ 0, 0, 0 });
	// エラー処理
	if (surface == nullptr) {
		SDL_Log("Surface Error");
	}
	mText = SDL_CreateTextureFromSurface(renderer, surface);
	// エラー処理
	if (mText == nullptr) {
		SDL_Log("Texture Error");
	}
	if (surface == nullptr) SDL_Log("Surface Error");
	SDL_QueryTexture(mText, NULL, NULL, &mTextWidth, &mTextHeight);

	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

Text::~Text() {

}
// 位置を決める
void Text::SetPosition(float x, float y) {
	if (mTextWidth == 0) {
		SDL_Log("Error Please Set Size!");
		return;
	}
	mPosition = { x, y };
	mLeftTop = mPosition - vector2{ static_cast<float>(mTextWidth / 2), static_cast<float>(mTextHeight / 2) };
	mRightDown = mPosition + vector2{ static_cast<float>(mTextWidth / 2), static_cast<float>(mTextHeight / 2) };
}

// 描写
void Text::Draw(SDL_Renderer* renderer) {
	SDL_Rect txtRect = SDL_Rect{ static_cast<int>(mLeftTop.x), static_cast<int>(mLeftTop.y), mTextWidth, mTextHeight };
	SDL_RenderCopy(renderer, mText, NULL, &txtRect);
}
