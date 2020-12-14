#include "Make.h"
#include "SceneManager.h"
#include "Game.h"


Make::Make(SceneManager* scmana, SDL_Window* window, SDL_Renderer* renderer):
	mScmana(scmana),
	mWindow(window),
	mRenderer(renderer),
	mStagefile(0),
	mIsRunning(0),
	mMode(MAKE), 
	mGame(0)
{
	mStagefile = "StageData/InitStage.txt";
	ModeMake();
}

Make::~Make() {
	delete[] mGame;
	mGame = 0;
}

// 毎フレーム更新
bool Make::MainLoop() {
	mGame->MainLoop();
	Input();
	Display();

	return mIsRunning;
}

// 作るモード
void Make::ModeMake() {
	mMode = MAKE;
	delete[] mGame;
	mGame = new Game(mScmana, mStagefile, mWindow, mRenderer, true);
	mIsRunning = mGame->Initialize();
}
// プレイモード
void Make::ModePlay() {
	mMode = PLAY;
	delete[] mGame;
	mGame = new Game(mScmana, mStagefile, mWindow, mRenderer);
	mIsRunning = mGame->Initialize();
}



// 入力を受け付ける
void Make::Input() {
	// イベントを取得
	SDL_Event event;
	// キューにイベントがあれば処理し終わるまでくりかえす（複数のイベント対策）
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
}

// 画面を描写
void Make::Display() {

}