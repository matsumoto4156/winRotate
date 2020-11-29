#pragma once
#include "SDL.h"
#include "Stage.h"
#include <vector>
#include <unordered_map>

#include <iostream>


class Game {
public:
	Game();
	~Game();
	// ������
	bool Initialize();
	// ���[�v�̓��e
	void MainLoop();
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
	vector2 GetStageLoc(int stageNumber);
	class PhisicManager* GetPManager() { return mPManager; };
	// ��]���s��
	void Rotate(int stage);
	

private:
	// �ŏ��̃��[�h���s��
	void LoadData();
	// �X�e�[�W�̓ǂݎ��
	void LoadStage();
	// �X�e�[�W���W�̓ǂݎ��
	void InitStageLoc();
	// �w�i��`�ʂ���
	void MakeBack();
	// ���[�v�̃w���p�[�֐��Q
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	// �摜�ǂݎ��̊֐�
	SDL_Texture* LoadTexture(const char* filename);

	// �v���C���[�͂����Ă�����
	class Player* mPlayer;

	// SDL�̃E�B���h�E
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	Uint32 mPreviousTime;

	// �e�N�X�`���[�̃}�b�v
	std::unordered_map<const char*, SDL_Texture*> mTextures;

	// �I�u�W�F�g�̔z��
	std::vector<class GameObject*> mObjects;	  // �����g
	std::vector<class GameObject*> mWaitObjects;  // �ҋ@�g
	// �X�v���C�g�̔z��
	std::vector<class SpriteComponent*> mSprites;
	// �X�e�[�W�z��
	class Stage mStage;
	// �X�V������Ԃ�
	bool mUpdatingObjects;
	// �X�e�[�W�̍��W
	vector2* mLeftTops;
	// ���������̃N���X
	class PhisicManager* mPManager;
	// �l�}�X������̑傫��
	int mSize;
};