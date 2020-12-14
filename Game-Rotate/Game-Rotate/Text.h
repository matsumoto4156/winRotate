#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "vector2.h"

class Text {
public:
	Text(const char* str, SDL_Renderer* renderer, int size);
	~Text();
	// 位置を決める
	void SetPosition(float x, float y);
	// 描写
	void Draw(SDL_Renderer* renderer);
private:
	// テクスチャ
	const char* mStr;
	// テクスチャ
	SDL_Texture* mText;
	// テクスチャの大きさ
	int mTextWidth;
	int mTextHeight;
	// 座標情報
	vector2 mLeftTop;
	vector2 mRightDown;
	// 真ん中
	vector2 mPosition;
};