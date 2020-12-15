#pragma once
#include "SDL.h"
#include <vector>
#include "vector2.h"


class Make {
public:
	enum Mode {
		MAKE,
		PLAY
	};

	Make(class SceneManager* scmana, SDL_Window* window, SDL_Renderer* renderer);
	~Make();
	// 毎フレーム更新
	bool MainLoop();
	// 作るモード
	void ModeMake();
	// プレイモード
	void ModePlay();
	// ゲッター
	class SceneManager* GetScmana() { return mScmana; };
private:
	// 初期化
	void Initialize();
	// 入力を受け付ける
	bool Input();
	// ボタンの判断
	void IsButton(bool isDown);
	// マウスの状態
	void SetState();
	// 画面を描写
	void Display();


	// 現在のモード
	Mode mMode;
	// UI
	class UI* mUI;
	// ゲームインスタンス
	class Game* mGame;
	// シーンマネージャー
	class SceneManager* mScmana;

	// SDL関係
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	// 常のマウスの座標
	vec2<int> mMousePos;
	// 押されたマウスの座標
	int mInputX;
	int mInputY;
	// 貼り付ける場所
	vector2 mSetLoc;
	// ウィンドウの大きさ
	int mWindowWidth;
	int mWindowHeight;
	// 押されたボタン
	int mButtonNum;
	// ファイル名
	const char* mStagefile;
	// 今動いているか
	bool mIsRunning;
	// マウスがクリックされている
	bool mPreClick;
	// マス内にいるか
	bool mOnMass;
	// テクスチャー
	SDL_Texture* mMouseTexture;

	// 主要な座標
	vec2<int>* mLoc;
	// ツールのリスト
	std::vector<class Tool*> mTools;
};