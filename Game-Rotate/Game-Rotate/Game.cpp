#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"
#include "Background.h"
#include "Block.h"
#include "Player.h"
#include "PhisicManager.h"
#include "SpriteComponent.h"
#include "RotateComponent.h"
#include <fstream>
#include <string>

#include <iostream>



Game::Game() :
	mWindow(0),
	mRenderer(0),
	mIsRunning(true),
	mPreviousTime(0),
	mUpdatingObjects(false),
	mPlayer(0),
	mLeftTops(0),
	mPManager(0),
	mIsInput(true)
{

}

Game::~Game() {
	delete[] mPlayer;
	delete[] mLeftTops;
	delete[] mPManager;
	mWindow = 0;
	mRenderer = 0;
	mPlayer = 0;
	mLeftTops = 0;
	mPManager = 0;
}


// ������
bool Game::Initialize() {
	// SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("SDL���������ł��܂��� : %s", SDL_GetError());
		return false;
	}
	//�E�B���h�E
	mWindow = SDL_CreateWindow(
		"Game",
		100,
		100,
		1024,
		900,
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
	//�摜
	IMG_Init(IMG_INIT_PNG);

	// �X�e�[�W�n
	// ������
	mLeftTops = new vector2[8];
	mLeftTops[0] = { 112, 450 };
	mLeftTops[1] = { 512, 450 };
	mLeftTops[2] = { 512, 50 };
	mLeftTops[3] = { 112, 50 };
	mLeftTops[4] = { 87, 475 };
	mLeftTops[5] = { 537, 475 };
	mLeftTops[6] = { 537, 25 };
	mLeftTops[7] = { 87, 25 };

	LoadData();


	return true;
}


// ���[�v�̓��e
void Game::MainLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

// �Q�[�����I������
void Game::Shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

// �Q�[���I�u�W�F�N�g��ǉ�
void Game::AddObject(GameObject* object) {
	if (mUpdatingObjects) {
		mWaitObjects.emplace_back(object);
	}
	else {
		mObjects.emplace_back(object);
	}
}
// �Q�[���I�u�W�F�N�g��r��
void Game::RemoveObject(GameObject* object) {

	auto iter = std::find(mObjects.begin(), mObjects.end(), object);
	// erase�ɂ���ʃR�s�[�h�~�̂��߁A����ւ����g��
	if (iter != mObjects.end()) {
		std::iter_swap(iter, mObjects.end() - 1);
		mObjects.pop_back();
	}
	iter = std::find(mWaitObjects.begin(), mWaitObjects.end(), object);
	if (iter != mWaitObjects.end()) {
		std::iter_swap(iter, mWaitObjects.end());
		mWaitObjects.pop_back();
	}
}

// �e�N�X�`���[��n��
SDL_Texture* Game::GetTexture(const char* filename) {
	SDL_Texture* text = nullptr;
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end()) {
		text = iter->second;
	}
	else {
		text = LoadTexture(filename);
		mTextures.emplace(filename, text);
	}
	return text;
}

// �X�v���C�g��ǉ�
void Game::AddSprite(SpriteComponent* sprite) {
	int order = sprite->GetUpdateOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter) {
		if (order < (*iter)->GetDrawOrder()) {
			break;
		}
	}
	mSprites.insert(iter, sprite);
}
void Game::RemoveSprite(SpriteComponent* sprite) {
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	if (iter != mSprites.end()) {
		mSprites.erase(iter);
	}
}

// �Q�b�^�[
vector2 Game::GetStageLoc(int stageNumber) {
	if (stageNumber > 7) {
		SDL_Log("Access Error::(Stage Location)");
		vector2 vec;
		return vec;
	}
	return mLeftTops[stageNumber];
};

// ��]���s��
void Game::Rotate(int stage) {
	// ���͂��~�߂�
	mIsInput = false;
	mPlayer ->Stop();
	// �I�u�W�F�N�g�̍X�V
	mUpdatingObjects = true;
	for (GameObject* object : mObjects) {
		if (object->GetStagenum() == stage) {
			object->Go(true);
		}
	}
	mUpdatingObjects = false;
}






// �ŏ��̃��[�h���s��
void Game::LoadData() {
	MakeBack();
	LoadStage();
	mPManager = new PhisicManager();

	vector2 pos;

	for (int i = 0; i < 4; ++i) {
		float x = GetStageLoc(4 + i).x;
		float y = GetStageLoc(4 + i).y;
		for (int k = 0; k < mStage.GetY(); ++k) {
			for (int l = 0; l < mStage.GetX(); ++l) {
				if (0 < mStage(l, k, i) ) {
					// �X�e�[�W�֌W(5�܂�)
					if (mStage(l, k, i) <= 5) {
						pos.x = x + 50 * l;
						pos.y = y + 50 * k;
						WallBlock* wBlock = new WallBlock(this, pos, 50);
						if (mStage(l, k, i) == 2) wBlock->SetRotation(1.0f);
						else if (mStage(l, k, i) == 3) wBlock->SetRotation(0.5f);
						else if (mStage(l, k, i) == 4) wBlock->SetRotation(1.5f);
					}
					// Flag
					else if (mStage(l, k, i) == 6) {
						pos.x = x + 50 * l;
						pos.y = y + 50 * k;
						Flag* flag = new Flag(this, pos, 50, 0);
					}
					// �u���b�N
					else if (mStage(l, k, i) == 7) {
						pos.x = x + 50 * l;
						pos.y = y + 50 * k;
						RotateBlock* rBlock = new RotateBlock(this, pos, 50);
						rBlock->SetIsRotate(true);
					}
				}
			}
		}
	}

	// �v���C���[�𐶐�
	pos = {450, 520 };
	mPlayer = new Player(this, pos, 50);
	mPManager->SetPlayer(mPlayer);
}

// �X�e�[�W�̓ǂݎ��
void Game::LoadStage() {
	char* buffa;
	int lendth;

	using namespace std;
	const char* filename = "StageData.txt";
	ifstream file(filename, ifstream::binary);
	if (!file) { SDL_Log("Could not load StageData.txt!"); return; };
	string str;
	getline(file, str);
	lendth = str.length() - 1;
	if (lendth % 2 != 0) { SDL_Log("Please input even width!"); return; };
	// SDL_Log("lendth : %d", lendth);
	file.seekg(0, ifstream::end);
	int size = static_cast<int>(file.tellg());
	if (size != (lendth + 2) * (lendth)-2) { SDL_Log("Error! Please input same height!"); };
	// SDL_Log("size : %d", size);
	buffa = new char[size];
	file.seekg(0, ifstream::beg);
	file.read(buffa, size);

	mStage.SetSize(lendth / 2, lendth / 2, 4);
	int start[4] = { (lendth + 2) * lendth / 2, (lendth + 3) * lendth / 2, lendth / 2, 0 };
	for (int i = 0; i < 4; ++i) {
		for (int k = 0; k < lendth / 2; ++k) {
			for (int l = 0; l < lendth / 2; ++l) {
				mStage(l, k, i) = static_cast<int>(buffa[start[i] + l + (lendth + 2) * k] - 48);
			}
		}
	}
	// �������J��
	delete[] buffa;
	mStage.Show();
}

// �w�i�`��
void Game::MakeBack() {
	vector2 pos;
	SpriteComponent::Color color;

	pos = { 312, 650 };
	Background* back1 = new Background(this, pos, 400);
	color = { 200, 0, 0, 0 };
	back1->SetColor(color);
	back1->SetIsRotate(true);

	pos = { 712, 650 };
	Background* back2 = new Background(this, pos, 400);
	color = { 0, 200, 0, 0 };
	back2->SetColor(color);
	back1->SetIsRotate(true);

	pos = { 712, 250 };
	Background* back3 = new Background(this, pos, 400);
	color = { 0, 0, 200, 0 };
	back3->SetColor(color);
	back1->SetIsRotate(true);

	pos = { 312, 250 };
	Background* back4 = new Background(this, pos, 400);
	color = { 255, 255, 0, 0 };
	back4->SetColor(color);
	back1->SetIsRotate(true);
}

// ���͊֌W
void Game::ProcessInput() {
	// ���͂��󂯕t���邩���f
	if (!mIsInput) return;


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

	// �L�[���擾���ăv���C���[�ɓn��
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
	mPlayer->InputMove(state);
}

// �Q�[���{��
void Game::UpdateGame() {

	// �f���^�^�C���̌v�Z
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mPreviousTime + 16));
	float deltaTime = (SDL_GetTicks() - mPreviousTime) / 1000.0f;
	mPreviousTime = SDL_GetTicks();
	if (deltaTime > 0.5f) {
		deltaTime = 0.5f;
	}

	// �I�u�W�F�N�g�̍X�V
	mUpdatingObjects = true;
	for (GameObject* object : mObjects) {
		object->Update(deltaTime);
	}
	mUpdatingObjects = false;

	for (GameObject* object : mWaitObjects) {
		mObjects.emplace_back(object);
	}
	mWaitObjects.clear();

	mPManager->ManagePlayer();
}

// ���ʂȕ`��
void Game::GenerateOutput() {

	SDL_SetRenderDrawColor(mRenderer, 118, 118, 118, 255);
	SDL_RenderClear(mRenderer);

	for (auto sp : mSprites) {
		sp->Draw(mRenderer);
	}
	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 16; x++) {
			SDL_SetRenderDrawColor(mRenderer, 112, 112, 112, 112);
			SDL_Rect back{ 112+x*50, 50+y*50, 50, 50 };
			SDL_RenderDrawRect(mRenderer, &back);
		}
	}
	SDL_RenderPresent(mRenderer);
	
}

// �摜�ǂݎ��̊֐�
SDL_Texture* Game::LoadTexture(const char* filename) {
	// png��ǂݎ��
	SDL_Surface* surf = IMG_Load(filename);
	if (!surf) {
		SDL_Log("Could not load image file!(surface)");
		return nullptr;
	}
	// �e�N�X�`�����쐬
	SDL_Texture* text = SDL_CreateTextureFromSurface(mRenderer, surf);
	SDL_FreeSurface(surf);
	if (!text) {
		SDL_Log("Couldn not load image file!(texture)");
		return nullptr;
	}
	return text;
}