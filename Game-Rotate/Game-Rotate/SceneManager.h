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
	// �e�V�[���𓮂���
	void MainLoop();
	// �V�[����ύX
	void ChangeScene(Scene scene);
	// �Q�[�����I������
	void Shutdown();
	// �e�N�X�`���[���擾
	SDL_Texture* SetTexture(const char* filename);
	// �����ā[���t�@�C��
	void SetStagefile(std::string filetext) { mStageFile = filetext; };
private:
	// �E�B���h�E���쐬
	bool MakeWindow();
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	// ���݂̃V�[��
	Scene mScene;
	// �X�e�[�W�f�[�^
	string mStageFile;
	// �V�[���̑J�ڂŎg��
	class Title* mTitle;
	class Select* mSelect;
	class Game* mGame;
	class Make* mMake;
	// ���܂������Ă��邩
	bool mSuccess;
};