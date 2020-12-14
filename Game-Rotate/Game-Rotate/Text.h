#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "vector2.h"

class Text {
public:
	Text(const char* str, SDL_Renderer* renderer, int size);
	~Text();
	// �ʒu�����߂�
	void SetPosition(float x, float y);
	// �`��
	void Draw(SDL_Renderer* renderer);
private:
	// �e�N�X�`��
	const char* mStr;
	// �e�N�X�`��
	SDL_Texture* mText;
	// �e�N�X�`���̑傫��
	int mTextWidth;
	int mTextHeight;
	// ���W���
	vector2 mLeftTop;
	vector2 mRightDown;
	// �^��
	vector2 mPosition;
};