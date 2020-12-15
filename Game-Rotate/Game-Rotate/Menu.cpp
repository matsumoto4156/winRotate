#include "Menu.h"
#include "SceneManager.h"
#include "Button.h"
#include "SDL_image.h"
#include "Text.h"
#include <fstream>
#include <sstream>
#include <string>


#include <iostream>



//////////////////////////// class Menu /////////////////////////////////

Menu::Menu(SceneManager* scmana, SDL_Window* window, SDL_Renderer* renderer) :
	mScmana(scmana),
	mWindow(window),
	mRenderer(renderer),
	mIsRunning(true),
	mPreClick(false),
	mButtonNum(-1),
	mInputX(0),
	mInputY(0),
	mWindowWidth(0),
	mWindowHeight(0)
{
	SDL_GetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);
}

Menu::~Menu() {
}


// 毎フレーム呼ばれる
bool Menu::MainLoop() {
	bool isClick = Input();
	IsButton(isClick);
	Display();

	return mIsRunning;
}

// プレイヤーの入力を受け付け
bool Menu::Input() {
	static bool isDown = false;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
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
	}
	return isDown;
}


// メニュー画面の描写
void Menu::Display() {
	SDL_SetRenderDrawColor(mRenderer, 100, 160, 180, 255);
	SDL_RenderClear(mRenderer);

	for (auto texture : mTextures) {
		texture->Draw(mRenderer);
	}
	for (auto button : mButtons) {
		button->Draw(mRenderer);
	}
	for (auto text : mTexts) {
		text->Draw(mRenderer);
	}
	SDL_RenderPresent(mRenderer);
}





//////////////////////////// class Title /////////////////////////////////

Title::Title(SceneManager* scmana, SDL_Window* window, SDL_Renderer* renderer) :
	Menu(scmana, window, renderer)
{
	Initialize();
}
Title::~Title() {

}
// 初期化
void Title::Initialize() {
	const char* str[3] = { "Image/Menu1.png", "Image/Menu2.png" , "Image/Menu3.png" };
	const char* str_b[3] = { "Image/Menu1_b.png", "Image/Menu2_b.png" , "Image/Menu3_b.png" };
	float w = mWindowWidth / 2.0f;
	float h = mWindowHeight * 3 / 5.0f;
	int k = 0;
	for (auto _ : str) {
		Button* button = new Button(mScmana, str[k], str_b[k]);
		h += button->GetUsuY();
		button->SetPosition(w, h);
		h += button->GetUsuY() + 30;
		mButtons.push_back(button);
		k += 1;
	}
}
// ボタンが押されているか判断
void Title::IsButton(bool isDown) {
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
	// ボタンが押されたとき
	else if (mPreClick && !isDown) {
		for (auto button : mButtons) {
			button->ReButton();
		}
		switch (mButtonNum) {
		case 0:
			mScmana->ChangeScene(SceneManager::LOAD_DATA);
			break;
		case 1:
			mScmana->ChangeScene(SceneManager::RESET_MAKE);
			break;
		case 2:
			mIsRunning = false;
			break;
		default:
			mButtonNum = -1;
		}
		mPreClick = false;
	}
}

//////////////////////////// class Select /////////////////////////////////

Select::Select(SceneManager* scmana, SDL_Window* window, SDL_Renderer* renderer) :
	Menu(scmana, window, renderer) ,
	mStageData(0)
{
	Initialize();
}
Select::~Select() {

}
// 初期化
void Select::Initialize() {
	// ステージリストのファイルを開く
	vector<string> lines;
	string line;
	ifstream file("StageList.txt");
	if (!file.is_open()) {
		SDL_Log("file open Error");
		return;
	}
	while (getline(file, line)) {
		lines.push_back(line);
	}
	file.close();

	float w = mWindowWidth / 6.0f;
	float h = mWindowHeight / 7.0f;
	// 1行ずつステージ情報を読み込む
	for (string line : lines) {

		istringstream two(line);
		string stagename, stagetext, stagepicture;
		two >> stagename >> stagetext >> stagepicture;
		mStageData.push_back(stagetext);

		const char* sn = stagename.c_str();
		const char* sp = stagepicture.c_str();
		const char* bt = "Image/Null.png";
		const char* bt_b = "Image/Null_b.png";

		Button* texture = new Button(mScmana, sp, sp);
		Button* button = new Button(mScmana, bt, bt_b);
		texture->SetSize(200, 200);
		texture->SetPosition(w, h);
		button->SetSize(200, 200);
		button->SetPosition(w, h);
		mTextures.push_back(texture);
		mButtons.push_back(button);
		Text* text = new Text(sn, mRenderer, 25);
		text->SetPosition(w, h+button->GetUsuY() + 30);
		mTexts.push_back(text);

		w += button->GetUsuX()*2 + 30;
	}
}
// ボタンが押されているか判断
void Select::IsButton(bool isDown) {
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
	// ボタンが押されたとき
	else if (mPreClick && !isDown) {

		for (auto button : mButtons) {
			button->ReButton();
		}
		if (mStageData[mButtonNum] == "") {
			SDL_Log("StageData Error!");
			return;
		}
		mScmana->SetStagefile(mStageData[mButtonNum]);
		mScmana->ChangeScene(SceneManager::RESET_GAME);
		mPreClick = false;
	}
}






