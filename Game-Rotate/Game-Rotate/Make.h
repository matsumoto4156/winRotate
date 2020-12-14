#pragma once
#include "SDL.h"


class Make {
public:
	enum Mode {
		MAKE,
		PLAY
	};

	Make(class SceneManager* scmana, SDL_Window* window, SDL_Renderer* renderer);
	~Make();
	// ���t���[���X�V
	bool MainLoop();
	// ��郂�[�h
	void ModeMake();
	// �v���C���[�h
	void ModePlay();
private:
	// ���͂��󂯕t����
	void Input();
	// ��ʂ�`��
	void Display();

	// �t�@�C����
	const char* mStagefile;
	// ���݂̃��[�h
	Mode mMode;
	// �Q�[���C���X�^���X
	class Game* mGame;
	// �V�[���}�l�[�W���[
	class SceneManager* mScmana;
	// �������Ă��邩
	bool mIsRunning;
	// SDL�֌W
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
};