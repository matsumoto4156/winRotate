#pragma once
#include "SDL.h"


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
private:
	// 入力を受け付ける
	void Input();
	// 画面を描写
	void Display();

	// ファイル名
	const char* mStagefile;
	// 現在のモード
	Mode mMode;
	// ゲームインスタンス
	class Game* mGame;
	// シーンマネージャー
	class SceneManager* mScmana;
	// 今動いているか
	bool mIsRunning;
	// SDL関係
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
};