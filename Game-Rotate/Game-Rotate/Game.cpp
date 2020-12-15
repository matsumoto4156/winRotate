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
#include "SceneManager.h"
#include "UI.h"
#include <fstream>
#include <string>




Game::Game(SceneManager* scmana, const char* stageFile, SDL_Window* window, SDL_Renderer* renderer, bool displaymode) :
	mScmana(scmana),
	mStageFile(stageFile),
	mWindow(window),
	mRenderer(renderer),
	mDisplayMode(displaymode),

	mPManager(0),
	mPlayer(0),
	mUI(0),
	mIsRunning(true),
	mPreviousTime(0),
	mUpdatingObjects(false),
	mLeftTops(0),
	mSize(0)
{
	Initialize();
}

Game::~Game() {
	delete[] mScmana;
	delete[] mPManager;
	delete[] mPlayer;
	delete[] mUI;
	delete[] mLeftTops;
	mScmana = 0;
	mPManager = 0;
	mPlayer = 0;
	mUI = 0;
	mLeftTops = 0;
}


// ������
bool Game::Initialize() {
	mUI = new UI(mScmana, mWindow);

	// �f�[�^�ǂݍ���
	LoadData();
	// �f�B�X�v���C���[�h�łȂ���΃v���C���[���o��
	if (!mDisplayMode) {
		SetPlayer();
	}

	return true;
}


// �v���C���[���o��
void Game::SetPlayer() {
	// �v���C���[�𐶐�
	vector2 pos = { 332 , 770 };
	mPlayer = new Player(this, pos, 38);
	mPManager->SetPlayer(mPlayer);
}

// ���[�v�̓��e
bool Game::MainLoop() {

	if (mPlayer) {
		Input();
		UpdateGame();
	}
	Display();
	return mIsRunning;
}

// �Q�[�����I������
void Game::Shutdown() {
	mScmana->Shutdown();
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
	int order = sprite->GetDrawOrder();
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
	// �I�u�W�F�N�g�̍X�V
	mUpdatingObjects = true;
	for (GameObject* object : mObjects) {
		if (object->GetStagenum() == stage){
			object->IsKeynematic(1.5f);
			if (object->GetIsRotate()) {
				object->Go(true);
			}
		}
	}
	mPlayer->IsKeynematic(1.8f);
	mUpdatingObjects = false;
}

// ���C�N���[�h�p
void Game::Draw(SDL_Renderer* renderer) {
	for (auto sp : mSprites) {
		sp->Draw(mRenderer);
	}

	// �O���b�h���̕\��
	if (mDisplayMode) {
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				SDL_SetRenderDrawColor(mRenderer, 112, 112, 112, 112);
				SDL_Rect back{ static_cast<int>(mLeftTops[0].x) + x * 40, static_cast<int>(mLeftTops[2].y) + y * 40, 40, 40 };
				SDL_RenderDrawRect(mRenderer, &back);
			}
		}
	}
}







// �ŏ��̃��[�h���s��
void Game::LoadData() {
	LoadStage();
	MakeBack();
	mPManager = new PhisicManager();

	// �X�e�[�W���W���쐬
	mStage.SetCCC(GetStageLoc(7), 40);
	mStage.SetCoord(0, GetStageLoc(4), 40); 
	mStage.SetCoord(1, GetStageLoc(5), 40);
	mStage.SetCoord(2, GetStageLoc(6), 40);
	mStage.SetCoord(3, GetStageLoc(7), 40);

	vector2 pos;
	int target = 0;
	// ���ꂼ��̃X�e�[�W�ɂ��čs��
	for (int stage = 0; stage < 4; ++stage) {
		// �ꏊ����肷�邽�߂Ɉ�����o��
		for (int y = 0; y < mStage.GetY(); ++y) {
			for (int x = 0; x < mStage.GetX(); ++x) {

				// �������g�������
				if (-4 <= (target = mStage(x, y, stage))) {
					pos = mStage.GetCoord(x, y, stage);
					// �X�e�[�W�֌W(5�܂�)
					if (target < 0) {
						WallBlock* wBlock = new WallBlock(this, pos, mSize);
						if (target == -3) wBlock->SetRotation(1.0f);
						else if (target == -2) wBlock->SetRotation(0.5f);
						else if (target == -1) wBlock->SetRotation(1.5f);
					}
					// ���u���b�N
					else if (target == 6) {
						RotateBlock* rBlock = new RotateBlock(this, pos, mSize);
						rBlock->SetIsRotate(true);
					}
					// �������u���b�N
					else if (target == 7) {
						StickBlock* sBlock = new StickBlock(this, pos, mSize);
					}
					// �ؔ��u���b�N
					else if (target == 8) {
						CrateBlock* cBlock = new CrateBlock(this, pos, mSize);
					}
					// Flag
					else if (1 <= target && target <= 5) {
						Flag* flag = nullptr;
						if (target == 1) flag = new Flag(this, pos, mSize, 1, "Image/Flag0.png");
						else if (target == 2) flag = new Flag(this, pos, mSize, 2, "Image/Flag1.png");
						else if (target == 3) flag = new Flag(this, pos, 50, 3, "Image/Flag2.png");
						else if (target == 4) flag = new Flag(this, pos, mSize, 4, "Image/Flag3.png");
						if (mStage(x, y+1, stage) == 6) flag->SetIsRotate(true);
					}
				}
				// �z��O
				else {
					SDL_Log("Error!!(LoadStage)");
					return;
				}

			}
		}
	}
}



// �X�e�[�W�̓ǂݎ��
void Game::LoadStage() {
	char* buffa;
	int lendth;

	using namespace std;
	const char* filename = mStageFile;
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
	file.close();
	// �������J��
	delete[] buffa;
	mStage.Show();
	mSize = 800 / (lendth - 2);
	// �X�e�[�W�������W���m��
	InitStageLoc();
}

// �X�e�[�W���W�̓ǂݎ��
void Game::InitStageLoc() {

	float size = static_cast<float>(mSize);
	// ������
	mLeftTops = new vector2[8];
	mLeftTops[0] = { 75, 500 };
	mLeftTops[1] = { 475, 500 };
	mLeftTops[2] = { 475, 100 };
	mLeftTops[3] = { 75, 100 };
	mLeftTops[4] = mLeftTops[0] - vector2{size, 0};
	mLeftTops[5] = mLeftTops[1];
	mLeftTops[6] = mLeftTops[2] - vector2{ 0, size };
	mLeftTops[7] = mLeftTops[3] - vector2{ size, size };
}

// �w�i�`��
void Game::MakeBack() {
	vector2 pos;
	SpriteComponent::Color color;

	pos = { mLeftTops[0].x + 200, mLeftTops[0].y + 200 };
	Background* back1 = new Background(this, pos, 400, "Image/Stage0.png");
	back1->SetIsRotate(true);

	pos = { mLeftTops[1].x + 200, mLeftTops[0].y + 200 };
	Background* back2 = new Background(this, pos, 400, "Image/Stage1.png");
	back2->SetIsRotate(true);

	pos = { mLeftTops[0].x + 200, mLeftTops[2].y + 200 };
	Background* back3 = new Background(this, pos, 400, "Image/Stage2.png");
	back3->SetIsRotate(true);

	pos = { mLeftTops[1].x + 200, mLeftTops[2].y + 200 };
	Background* back4 = new Background(this, pos, 400, "Image/Stage3.png");
	back4->SetIsRotate(true);
}

// ���͊֌W
void Game::Input() {

	// �C�x���g���擾
	SDL_Event event;
	// �L���[�ɃC�x���g������Ώ������I���܂ł��肩�����i�����̃C�x���g�΍�j
	while (SDL_PollEvent(&event)) {
		mUI->Input(event);
		switch (event.type) {
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}

	// �L�[���擾���ăv���C���[�ɓn��
	const Uint8* state = SDL_GetKeyboardState(NULL);
	/*if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}*/
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

// �`��
void Game::Display() {

	SDL_SetRenderDrawColor(mRenderer, 118, 118, 118, 255);
	SDL_RenderClear(mRenderer);

	for (auto sp : mSprites) {
		sp->Draw(mRenderer);
	}
	mUI->Draw(mRenderer);

	// �O���b�h���̕\��
	if (mDisplayMode) {
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				SDL_SetRenderDrawColor(mRenderer, 112, 112, 112, 112);
				SDL_Rect back{ static_cast<int>(mLeftTops[0].x) + x * 40, static_cast<int>(mLeftTops[2].y) + y * 40, 40, 40 };
				SDL_RenderDrawRect(mRenderer, &back);
			}
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