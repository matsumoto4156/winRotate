#pragma once
#include "SDL.h"
#include "vector2.h"


// オブジェクトを配置するツール
class Tool {
public:
	Tool(class Make* make, int objectnum);
	~Tool();
	// 位置を決める
	void SetPosition(float x, float y);
	// サイズを決める
	void SetSize(int width, int height) { mTextWidth = width; mTextHeight = height; };
	// ボタンが押されているか
	bool IsButton(int x, int y);
	// テクスチャーを渡す
	SDL_Texture* GetTexture() { return mTexture; };
	// 描写
	void Draw(SDL_Renderer* renderer);
	// 下どれくらい使ったか
	int GetUsuY() { return mTextHeight / 2; };
	// 横どれくらい使ったか
	int GetUsuX() { return mTextWidth / 2; };
private:
	// 初期化
	void Initialize();

	// メイククラス
	class Make* mMake;
	// テクスチャの大きさ
	int mTextWidth;
	int mTextHeight;
	// どのオブジェクトか
	int mObjectNumber;
	// 選択されているか
	bool mOnThis;
	// テクスチャー
	SDL_Texture* mTexture;
	SDL_Texture* mFrameTexture;
	SDL_Texture* mOnTexture;
	// 位置
	vector2 mPosition;
	vector2 mLeftTop;
	vector2 mRightDown;
	// ファイル名のリスト
	const char** mFilenames;
};

