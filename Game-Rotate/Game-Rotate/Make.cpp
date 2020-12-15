#include "Make.h"
#include "SceneManager.h"
#include "Game.h"
#include "UI.h"
#include "Tool.h"
#include "Stage.h"


Make::Make(SceneManager* scmana, SDL_Window* window, SDL_Renderer* renderer):
	mScmana(scmana),
	mWindow(window),
	mRenderer(renderer),

	mInputX(0),
	mInputY(0),
	mWindowHeight(0),
	mWindowWidth(0),
	mButtonNum(-1),
	mStagefile(0),
	mIsRunning(true),
	mPreClick(false),
	mOnMass(false),
	mMouseTexture(0),
	mMode(MAKE), 
	mGame(0),
	mUI(0),
	mLoc(0)
{
	Initialize();
}

Make::~Make() {
	SDL_DestroyTexture(mMouseTexture);
	delete[] mGame;
	delete[] mUI;
	mMouseTexture = 0;
	mGame = 0;
	mUI = 0;
}

// ���t���[���X�V
bool Make::MainLoop() {
	bool is = Input();
	IsButton(is);
	SetState();
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




// ������
void Make::Initialize() {
	// �����Ƃ����Ђ傤�Ƃ�
	SDL_GetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);
	mLoc = new vec2<int>[8];
	mLoc[0] = { 75, 500 };
	mLoc[1] = { 475, 500 };
	mLoc[2] = { 475, 100 };
	mLoc[3] = { 75, 100 };

	mStagefile = "StageData/InitStage.txt";
	ModeMake();
	mUI = mGame->GetUI();

	float w = 1000;
	float h = 50;
	for (int i = 0; i < 9; ++i) {
		Tool* tool = new Tool(this, i);
		tool->SetSize(70, 70);
		h += tool->GetUsuY();
		tool->SetPosition(w, h);
		mTools.push_back(tool);
		h += tool->GetUsuY() + 30;
	}
}
// ���͂��󂯕t����
bool Make::Input() {
	static bool isDown = false;

	// �}�E�X�̈ʒu���擾
	SDL_GetMouseState(&mMousePos.x, &mMousePos.y);

	// �C�x���g���擾
	SDL_Event event;
	// �L���[�ɃC�x���g������Ώ������I���܂ł��肩�����i�����̃C�x���g�΍�j
	while (SDL_PollEvent(&event)) {
		mUI->Input(event);
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mInputX, &mInputY);
			isDown = true;
			break;
		case SDL_MOUSEBUTTONUP:
			isDown = false;
			break;
		}
	}
	return isDown;
}

// �{�^����������Ă��邩���f
void Make::IsButton(bool isDown) {
	if (isDown) {
		int k = 0;
		for (auto tool : mTools) {
			if (tool->IsButton(mInputX, mInputY)) {
				mButtonNum = k;
			}
			k += 1;
		}
		if (mButtonNum >= 0) {
			mPreClick = true;
		}
	}
}

// �}�E�X�̏��
void Make::SetState() {
	if (mButtonNum >= 0) {
		mMouseTexture = mTools[mButtonNum]->GetTexture();
	}
	else {
		mMouseTexture = nullptr;
	}


	bool no = mMousePos.x < mLoc[3].x ||
		mMousePos.y < mLoc[3]. y ||
		mLoc[1].x+400 < mMousePos.x ||
		mLoc[1].y+400 < mMousePos.y;
	mOnMass = !no;
	// �͈͊O�Ȃ�ΏI��
	if (no) {
		return;
	}

	// �}�E�X�̃}�X�ڂ𓾂�
	mMousePos = mMousePos - mLoc[3];
	int x = mMousePos.x / 40 + 1;
	int y = mMousePos.y / 40 + 1;
	mSetLoc = mGame->GetStage()->GetCCC(22*y + x);
}

// ��ʂ�`��
void Make::Display() {
	SDL_SetRenderDrawColor(mRenderer, 100, 160, 180, 255);
	SDL_RenderClear(mRenderer);

	// �c�[����\��
	for (auto tool : mTools) {
		tool->Draw(mRenderer);
	}
	mGame->Draw(mRenderer);
	mUI->Draw(mRenderer);

	// �}�E�X�̉��ɃA�C�R���\��
	if (mOnMass) {
		SDL_Rect back = { static_cast<int>(mSetLoc.x) - 15, static_cast<int>(mSetLoc.y) - 15, 30, 30 };
		SDL_RenderCopyEx(
			mRenderer,
			mMouseTexture,
			nullptr,
			&back,
			0,
			nullptr,
			SDL_FLIP_NONE
		);
	}
	
	SDL_RenderPresent(mRenderer);
}