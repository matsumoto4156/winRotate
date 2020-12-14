#include "UI.h"
#include "Button.h"
#include "SceneManager.h"
#include "Text.h"



UI::UI(SceneManager* scmana, SDL_Window* window):
	mScmana(scmana),
	mIsRunning(true),
	mPreClick(false),
	mButtonNum(-1),
	mInputX(0),
	mInputY(0),
	mWindowWidth(0),
	mWindowHeight(0)
{
	SDL_GetWindowSize(window, &mWindowWidth, &mWindowHeight);
	Initialize();
}

UI::~UI() {

}

// ������
void UI::Initialize() {
	Button* button = new Button(mScmana, "Image/ToTitle.png", "Image/ToTitle_b.png");
	button->SetSize(40, 30);
	button->SetPosition(40, 40);
	mButtons.push_back(button);
}


// ���j���[��ʂ̕`��
void UI::Draw(SDL_Renderer* renderer) {
	for (auto texture : mTextures) {
		texture->Draw(renderer);
	}
	for (auto button : mButtons) {
		button->Draw(renderer);
	}
	for (auto text : mTexts) {
		text->Draw(renderer);
	}
}


// �v���C���[�̓��͂��󂯕t��
void UI::Input(SDL_Event event){
	static bool isDown = false;

	switch (event.type) {
	case SDL_QUIT:
		mIsRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&mInputX, &mInputY);
		isDown = true;
		break;
	case SDL_MOUSEBUTTONUP:
		isDown = false;
		break;
	}
	if (isDown) cout << "sas" << endl;
	IsButton(isDown);
}

// �{�^����������Ă��邩���f
void UI::IsButton(bool isDown) {
	if (isDown) {
		int k = 0;
		for (auto button : mButtons) {
			if (button->IsButton(mInputX, mInputY)) {
				mButtonNum = k;
			}
			k += 1;
		}
		if (mButtonNum >= 0) {
			mPreClick = true;
		}
	}
	// �{�^���������ꂽ�Ƃ�
	else if (mPreClick && !isDown) {

		mScmana->ChangeScene(SceneManager::TITLE);
		mPreClick = false;
	}
}