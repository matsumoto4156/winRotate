#pragma once
#include "SDL.h"
#include <vector>
#include "vector2.h"


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
	// �Q�b�^�[
	class SceneManager* GetScmana() { return mScmana; };
private:
	// ������
	void Initialize();
	// ���͂��󂯕t����
	bool Input();
	// �{�^���̔��f
	void IsButton(bool isDown);
	// �}�E�X�̏��
	void SetState();
	// ��ʂ�`��
	void Display();


	// ���݂̃��[�h
	Mode mMode;
	// UI
	class UI* mUI;
	// �Q�[���C���X�^���X
	class Game* mGame;
	// �V�[���}�l�[�W���[
	class SceneManager* mScmana;

	// SDL�֌W
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	// ��̃}�E�X�̍��W
	vec2<int> mMousePos;
	// �����ꂽ�}�E�X�̍��W
	int mInputX;
	int mInputY;
	// �\��t����ꏊ
	vector2 mSetLoc;
	// �E�B���h�E�̑傫��
	int mWindowWidth;
	int mWindowHeight;
	// �����ꂽ�{�^��
	int mButtonNum;
	// �t�@�C����
	const char* mStagefile;
	// �������Ă��邩
	bool mIsRunning;
	// �}�E�X���N���b�N����Ă���
	bool mPreClick;
	// �}�X���ɂ��邩
	bool mOnMass;
	// �e�N�X�`���[
	SDL_Texture* mMouseTexture;

	// ��v�ȍ��W
	vec2<int>* mLoc;
	// �c�[���̃��X�g
	std::vector<class Tool*> mTools;
};