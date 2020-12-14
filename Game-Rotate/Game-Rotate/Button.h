#pragma once
#include "SDL.h"
#include "vector2.h"

class Button {
public:
	Button(class SceneManager* scmana, const char* filename, const char* filename_b);
	~Button();
	// �ʒu�����߂�
	void SetPosition(float x, float y);
	// �T�C�Y�����߂�
	void SetSize(int width, int height) { mTextWidth = width; mTextHeight = height; };
	// �{�^����������Ă��邩
	bool IsButton(int x, int y);
	// �{�^����������Ă��邩
	void ReButton() { mText = mNormalText; };
	// �`��
	void Draw(SDL_Renderer* renderer);
	// ���ǂꂭ�炢�g������
	int GetUsuY() { return mTextHeight / 2; };
	// ���ǂꂭ�炢�g������
	int GetUsuX() { return mTextWidth / 2; };
private:
	// �e�N�X�`��
	SDL_Texture* mText;
	// ���ʂ̃e�N�X�`��
	SDL_Texture* mNormalText;
	// �����ꂽ���̃e�N�X�`��
	SDL_Texture* mPushText;
	// �t�@�C����
	const char* mFilename;
	// �e�N�X�`���̑傫��
	int mTextWidth;
	int mTextHeight;
	// ���W���
	vector2 mLeftTop;
	vector2 mRightDown;
	// �^��
	vector2 mPosition;
};