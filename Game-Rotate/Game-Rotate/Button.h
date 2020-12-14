#pragma once
#include "SDL.h"
#include "vector2.h"

class Button {
public:
	Button(class SceneManager* scmana, const char* filename, const char* filename_b);
	~Button();
	// 位置を決める
	void SetPosition(float x, float y);
	// サイズを決める
	void SetSize(int width, int height) { mTextWidth = width; mTextHeight = height; };
	// ボタンが押されているか
	bool IsButton(int x, int y);
	// ボタンが押されているか
	void ReButton() { mText = mNormalText; };
	// 描写
	void Draw(SDL_Renderer* renderer);
	// 下どれくらい使ったか
	int GetUsuY() { return mTextHeight / 2; };
	// 横どれくらい使ったか
	int GetUsuX() { return mTextWidth / 2; };
private:
	// テクスチャ
	SDL_Texture* mText;
	// 普通のテクスチャ
	SDL_Texture* mNormalText;
	// 押された時のテクスチャ
	SDL_Texture* mPushText;
	// ファイル名
	const char* mFilename;
	// テクスチャの大きさ
	int mTextWidth;
	int mTextHeight;
	// 座標情報
	vector2 mLeftTop;
	vector2 mRightDown;
	// 真ん中
	vector2 mPosition;
};