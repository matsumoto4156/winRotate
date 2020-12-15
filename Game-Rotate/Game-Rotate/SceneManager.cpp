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

// �V�[����ύX
void SceneManager::ChangeScene(Scene scene) {
	mScene = scene;
}

// �Q�[�����I������
void SceneManager::Shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

// �e�N�X�`���[�̔z�u
SDL_Texture* SceneManager::SetTexture(const char* filename) {
	// png��ǂݎ��
	SDL_Surface* surf = IMG_Load(filename);
	if (!surf) {
		SDL_Log("Could not load image file!(surface)");
		mSuccess = false;
		return nullptr;
	}
	// �e�N�X�`�����쐬
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surf);
	SDL_FreeSurface(surf);
	if (!texture) {
		SDL_Log("Couldn not load image file!(texture)");
		mSuccess = false;
		return nullptr;
	}

	return texture;
}





// �e�V�[���𓮂���
void SceneManager::MainLoop() {
	mSuccess = MakeWindow();
	Title* title = new Title(this, mWindow, mRenderer);

	while (mSuccess) {

		switch (mScene) {
		// ���j���[���
		case TITLE:
			mSuccess = title->MainLoop();
			break;
		// �f�[�^�̓ǂݍ���
		case LOAD_DATA:
			mSelect = new Select(this, mWindow, mRenderer);
			mScene = SELECT;
		// �X�e�[�W�Z���N�g���
		case SELECT:
			mSuccess = mSelect->MainLoop();
			break;
		// �Q�[�����쐬
		case RESET_GAME:
			mGame = new Game(this, mStageFile.c_str(), mWindow, mRenderer);
			mScene = GAME;
			break;
		// �v���C
		case GAME:
			mSuccess = mGame->MainLoop();
			break;
		// �Q�[���I��
		case END_GAME:
			delete[] mGame;
			mGame = 0;
			mScene = TITLE;
			break;
		// �v���C���
		case RESET_MAKE:
			SDL_SetWindowSize(mWindow, 1075, 950);
			mMake = new Make(this, mWindow, mRenderer);
			mScene = MAKE;
			break;
		// �X�e�[�W�쐬
		case MAKE:
			mSuccess = mMake->MainLoop();
			break;
		// ���C�N�I��
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
		SDL_Log("SDL���������ł��܂��� : %s", SDL_GetError());
		return false;
	}
	//�E�B���h�E
	mWindow = SDL_CreateWindow(
		"Game",
		50,
		50,
		950,
		950,
		0
	);
	if (!mWindow) {
		SDL_Log("�E�B���h�E�̍쐬�Ɏ��s : %s", SDL_GetError());
		return false;
	}
	//�����_���[
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	return true;
}