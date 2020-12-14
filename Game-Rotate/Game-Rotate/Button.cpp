#include "Button.h"
#include "SceneManager.h"
#include <string>



Button::Button(SceneManager* scmana, const char* filename, const char* filename_b) :
	mFilename(filename),
	mText(0),
	mNormalText(0),
	mPushText(0),
	mTextWidth(0),
	mTextHeight(0)
{
	mNormalText = scmana->SetTexture(mFilename);
	mPushText = scmana->SetTexture(filename_b);
	mText = mNormalText;
	if (!mText) {
		SDL_Log("�e�N�X�`���𓾂��܂���ł���");
	}
	// �摜�̑傫�����擾
	SDL_QueryTexture(mText, nullptr, nullptr, &mTextWidth, &mTextHeight);
}

Button::~Button() {

}

// �ʒu�����߂�
void Button::SetPosition(float x, float y) {
	if (mTextWidth == 0) {
		SDL_Log("Error Please Set Size!");
		return;
	}
	mPosition = { x, y };
	mLeftTop = mPosition - vector2{ static_cast<float>(mTextWidth / 2), static_cast<float>(mTextHeight / 2) };
	mRightDown = mPosition + vector2{ static_cast<float>(mTextWidth / 2), static_cast<float>(mTextHeight / 2) };
}

// �{�^����������Ă��邩
bool Button::IsButton(int x, int y) {
	bool no = x < mLeftTop.x ||
		y < mLeftTop.y ||
		mRightDown.x < x ||
		mRightDown.y < y;

	if (!no) {
		mText = mPushText;
	}
	return !no;
}

// �`��
void Button::Draw(SDL_Renderer* renderer) {
	SDL_Rect back = { static_cast<int>(mLeftTop.x), static_cast<int>(mLeftTop.y), mTextWidth, mTextHeight };
	SDL_RenderCopyEx(
		renderer,
		mText,
		nullptr,
		&back,
		0,
		nullptr,
		SDL_FLIP_NONE
	);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawRect(renderer, &back);
}