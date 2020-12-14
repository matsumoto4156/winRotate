#pragma once
#include "SDL.h"
#include <vector>
#include <string>


class Menu {
public:
	Menu(class SceneManager* smana, SDL_Window* window, SDL_Renderer* renderer);
	~Menu();
	// ���t���[���Ă΂��
	bool MainLoop();
protected:
	// ������
	virtual void Initialize() {};
	// ���[�U�[�̓��͂̎擾
	bool Input();
	// �{�^����������Ă��邩���f
	virtual void IsButton(bool isDown) {};
	// ���j���[��ʂ̕`��
	void Display();

	// �V�[���}�l�[�W���[
	class SceneManager* mScmana;
	// �������Ă��邩
	bool mIsRunning;
	// �}�E�X���N���b�N����Ă���
	bool mPreClick;
	// �{�^���̔ԍ�
	int mButtonNum;
	// SDL�֌W
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	// �}�E�X�̍��W
	int mInputX;
	int mInputY;
	// �E�B���h�E�̑傫��
	int mWindowWidth;
	int mWindowHeight;
	// �e�N�X�`���[
	std::vector<class Text*> mTexts;
	// �e�N�X�`���[
	std::vector<class Button*> mTextures;
	// �{�^��
	std::vector<class Button*> mButtons;
};

// �^�C�g�����
class Title :public Menu {
public:
	Title(class SceneManager* smana, SDL_Window* window, SDL_Renderer* renderer);
	~Title();
protected:
	// ������
	void Initialize();
	// �{�^����������Ă��邩���f
	void IsButton(bool isDown);
};

// �X�e�[�W�Z���N�g���
class Select :public Menu {
public:
	Select(class SceneManager* smana, SDL_Window* window, SDL_Renderer* renderer);
	~Select();
protected:
	// ������
	void Initialize();
	// �{�^����������Ă��邩���f
	void IsButton(bool isDown);

	// �X�e�[�W�t�@�C����
	std::vector<std::string> mStageData;
};

