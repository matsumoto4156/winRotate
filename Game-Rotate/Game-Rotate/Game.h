#pragma once
#include "SDL.h"
#include "Stage.h"
#include <vector>
#include <unordered_map>

#include <iostream>


class Game {
public:
	Game(class SceneManager* scmana, const char* stagefile, SDL_Window* window, SDL_Renderer* renderer, bool displayMode = false);
	~Game();
	// ������
	bool Initialize();
	// ���[�v�̓��e
	bool MainLoop();
	// �Q�[�����I������
	void Shutdown();
	// �Q�[���I�u�W�F�N�g��ǉ�/����
	void AddObject(class GameObject* object);
	void RemoveObject(class GameObject* object);
	// �����_�[��n��
	SDL_Renderer* GetRenderer() { return mRenderer; };
	// �e�N�X�`���[��n��
	SDL_Texture* GetTexture(const char* filename);
	// �X�v���C�g��ǉ�
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	// �Q�b�^�[
	class UI* GetUI() { return mUI; };
	class Stage* GetStage() { return &mStage; };
	vector2 GetStageLoc(int stageNumber);
	class PhisicManager* GetPManager() { return mPManager; };
	// ��]���s��
	void Rotate(int stage);
	// ���C�N���[�h�p
	void Draw(SDL_Renderer* renderer);
	

private:
	// �ŏ��̃��[�h���s��
	void LoadData();
	// �X�e�[�W�̓ǂݎ��
	void LoadStage();
	// �X�e�[�W���W�̓ǂݎ��
	void InitStageLoc();
	// �w�i��`�ʂ���
	void MakeBack();
	// �v���C���[���o��
	void SetPlayer();
	// ���[�v�̃w���p�[�֐��Q
	void Input();
	void UpdateGame();
	void Display();
	// �摜�ǂݎ��̊֐�
	SDL_Texture* LoadTexture(const char* filename);

	// �V�[���}�l�[�W���[
	class SceneManager* mScmana;
	// ���������̃N���X
	class PhisicManager* mPManager;
	// �v���C���[�͂����Ă�����
	class Player* mPlayer;
	// UI�͎����ŊǗ�����
	class UI* mUI;

	// SDL�̃E�B���h�E
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	// �e�N�X�`���[�̃}�b�v
	std::unordered_map<const char*, SDL_Texture*> mTextures;
	// �I�u�W�F�g�̔z��
	std::vector<class GameObject*> mObjects;	  // �����g
	std::vector<class GameObject*> mWaitObjects;  // �ҋ@�g
	// �X�v���C�g�̔z��
	std::vector<class SpriteComponent*> mSprites;
	// �X�e�[�W�z��
	class Stage mStage;

	// �����Ă��邩
	bool mIsRunning;
	// �O��̎���
	Uint32 mPreviousTime;
	// �f�B�X�v���C���[�h���ǂ���
	bool mDisplayMode;
	// �X�V������Ԃ�
	bool mUpdatingObjects;
	// �X�e�[�W�̍��W
	vector2* mLeftTops;
	// �X�e�[�W�t�@�C���̖��O
	const char* mStageFile;
	// �l�}�X������̑傫��
	int mSize;
};