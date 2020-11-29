#pragma once

#include "SDL.h"
#include "Component.h"
#include "vector2.h"

class SpriteComponent : public Component {
public:
	struct Color {
		Uint8 red = 0;
		Uint8 blue = 0;
		Uint8 green = 0;
		Uint8 alpha = 0;
	};
	SpriteComponent(class GameObject* owner, int updateOrder);
	virtual ~SpriteComponent();
	void Update(float delataTime) {};
	// 描写の順番を決める（デフォは1）
	void SetDrawOrder(int order) { mDrawOrder = order; };
	int GetDrawOrder() { return mDrawOrder; };
	// それぞれの描写（ORしてね）
	virtual void Draw(SDL_Renderer* renderer);
private:
	int mDrawOrder;
};

class RectSprite : public SpriteComponent {
public:
	RectSprite(class GameObject* owner, int updateOrder);
	~RectSprite();
	// 正方形を描写
	void Draw(SDL_Renderer* renderer);
	// 色を設定・返す
	void SetColor(Color color) { mColor = color; };
	Color GetColor() { return mColor; };
private:
	// 描写に必要な変数を確定
	void SetLoc();
	Color mColor;
	vector2 mLeftTop;
	int mLendth;
};

class TextureSprite : public SpriteComponent {
public:
	TextureSprite(class GameObject* owner, int updateOrder, const char* filename, bool state = true);
	~TextureSprite();
	// 画像を描写
	void Draw(SDL_Renderer* renderer);
	// 画像の向きを変える
	void SetFlip(int right);
	// 描写するかへんこう
	void SetState(bool state) { mState = state; };
private:
	// 画像サイズをセット
	void SetTexture();
	SDL_Texture* mTexture;
	int mTextWidth;
	int mTextHeight;
	SDL_RendererFlip mFlip;
	// 描写するかどうか
	bool mState;
};