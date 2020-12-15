#include "SceneManager.h"
#include "Game.h"
#include "SDL_image.h"
#include "vector2.h"
#include "Menu.h"
#include "Make.h"


SceneManager::SceneManager() :
	mWindow(0),
	mRenderer(0),
	mScene(TITLE),
	mTitle(0),
	mSelect(0),
	mGame(0),
	mMake(0),
	mSuccess(true)
{
}

SceneManager::~SceneManager() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();

	delete[] mTitle;
	delete[] mSelect;
	delete[] mGame;
	delete[] mMake;
	mTitle = 0;
	mSelect = 0;
	mGame = 0;
	mMake = 0;
}

// シーンを変更
void SceneManager::ChangeScene(Scene scene) {
	mScene = scene;
}

// ゲームを終了する
void SceneManager::Shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

// テクスチャーの配置
SDL_Texture* SceneManager::SetTexture(const char* filename) {
	// pngを読み取る
	SDL_Surface* surf = IMG_Load(filename);
	if (!surf) {
		SDL_Log("Could not load image file!(surface)");
		mSuccess = false;
		return nullptr;
	}
	// テクスチャを作成
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surf);
	SDL_FreeSurface(surf);
	if (!texture) {
		SDL_Log("Couldn not load image file!(texture)");
		mSuccess = false;
		return nullptr;
	}

	return texture;
}





// 各シーンを動かす
void SceneManager::MainLoop() {
	mSuccess = MakeWindow();
	Title* title = new Title(this, mWindow, mRenderer);

	while (mSuccess) {

		switch (mScene) {
		// メニュー画面
		case TITLE:
			mSuccess = title->MainLoop();
			break;
		// データの読み込み
		case LOAD_DATA:
			mSelect = new Select(this, mWindow, mRenderer);
			mScene = SELECT;
		// ステージセレクト画面
		case SELECT:
			mSuccess = mSelect->MainLoop();
			break;
		// ゲーム情報作成
		case RESET_GAME:
			mGame = new Game(this, mStageFile.c_str(), mWindow, mRenderer);
			mScene = GAME;
			break;
		// プレイ
		case GAME:
			mSuccess = mGame->MainLoop();
			break;
		// ゲーム終了
		case END_GAME:
			delete[] mGame;
			mGame = 0;
			mScene = TITLE;
			break;
		// プレイ画面
		case RESET_MAKE:
			SDL_SetWindowSize(mWindow, 1075, 950);
			mMake = new Make(this, mWindow, mRenderer);
			mScene = MAKE;
			break;
		// ステージ作成
		case MAKE:
			mSuccess = mMake->MainLoop();
			break;
		// メイク終了
		case END_MAKE:
			SDL_SetWindowSize(mWindow, 950, 950);
			delete[] mMake;
			mMake = 0;
			mScene = TITLE;
			break;
		}
	}
	if (!mSuccess) {
		Shutdown();
	}
}
bool SceneManager::MakeWindow() {
	// SDL
	SDL_Init(IMG_INIT_PNG);

	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("SDLを初期化できません : %s", SDL_GetError());
		return false;
	}
	//ウィンドウ
	mWindow = SDL_CreateWindow(
		"Game",
		50,
		50,
		950,
		950,
		0
	);
	if (!mWindow) {
		SDL_Log("ウィンドウの作成に失敗 : %s", SDL_GetError());
		return false;
	}
	//レンダラー
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	return true;
}