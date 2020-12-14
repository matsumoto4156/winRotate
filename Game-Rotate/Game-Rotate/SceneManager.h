#pragma once
#include "SDL.h"
#include <string>

#include <iostream>
using namespace std;

class SceneManager {
public:
	enum Scene {
		TITLE,
		LOAD_DATA,
		SELECT,
		RESET_GAME,
		GAME,
		END_GAME,
		RESET_MAKE,
		MAKE,
		END_MAKE
	};

	SceneManager();
	~SceneManager();
	// 各シーンを動かす
	void MainLoop();
	// シーンを変更
	void ChangeScene(Scene scene);
	// ゲームを終了する
	void Shutdown();
	// テクスチャーを取得
	SDL_Texture* SetTexture(const char* filename);
	// すってーじファイル
	void SetStagefile(std::string filetext) { mStageFile = filetext; };
private:
	// ウィンドウを作成
	bool MakeWindow();
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	// 現在のシーン
	Scene mScene;
	// ステージデータ
	string mStageFile;
	// シーンの遷移で使う
	class Title* mTitle;
	class Select* mSelect;
	class Game* mGame;
	class Make* mMake;
	// うまくいっているか
	bool mSuccess;
};