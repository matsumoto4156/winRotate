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

// ���t���[���X�V
bool Make::MainLoop() {
	mGame->MainLoop();
	Input();
	Display();

	return mIsRunning;
}

// ��郂�[�h
void Make::ModeMake() {
	mMode = MAKE;
	delete[] mGame;
	mGame = new Game(mScmana, mStagefile, mWindow, mRenderer, true);
	mIsRunning = mGame->Initialize();
}
// �v���C���[�h
void Make::ModePlay() {
	mMode = PLAY;
	delete[] mGame;
	mGame = new Game(mScmana, mStagefile, mWindow, mRenderer);
	mIsRunning = mGame->Initialize();
}



// ���͂��󂯕t����
void Make::Input() {
	// �C�x���g���擾
	SDL_Event event;
	// �L���[�ɃC�x���g������Ώ������I���܂ł��肩�����i�����̃C�x���g�΍�j
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
}

// ��ʂ�`��
void Make::Display() {

}