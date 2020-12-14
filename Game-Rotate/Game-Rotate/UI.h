#pragma once
#include "SDL.h"
#include <vector>


// UI 
class UI {
public:
	UI(class SceneManager* scmana, SDL_Window* window);
	~UI();
	// ���j���[��ʂ̕`��
	void Draw(SDL_Renderer* renderer);
	void Input(SDL_Event event);
private:
	// ������
	void Initialize();
	// �{�^����������Ă��邩���f
	void IsButton(bool isDown);

	// �V�[���}�l�[�W���[
	class SceneManager* mScmana;
	// �������Ă��邩
	bool mIsRunning;
	// �}�E�X���N���b�N����Ă���
	bool mPreClick;
	// �{�^���̔ԍ�
	int mButtonNum;
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