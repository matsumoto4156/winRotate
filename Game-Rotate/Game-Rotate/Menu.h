#pragma once
#include "SDL.h"
#include <vector>
#include <string>


class Menu {
public:
	Menu(class SceneManager* smana, SDL_Window* window, SDL_Renderer* renderer);
	~Menu();
	// 毎フレーム呼ばれる
	bool MainLoop();
protected:
	// 初期化
	virtual void Initialize() {};
	// ユーザーの入力の取得
	bool Input();
	// ボタンが押されているか判断
	virtual void IsButton(bool isDown) {};
	// メニュー画面の描写
	void Display();

	// シーンマネージャー
	class SceneManager* mScmana;
	// 今動いているか
	bool mIsRunning;
	// マウスがクリックされている
	bool mPreClick;
	// ボタンの番号
	int mButtonNum;
	// SDL関係
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	// マウスの座標
	int mInputX;
	int mInputY;
	// ウィンドウの大きさ
	int mWindowWidth;
	int mWindowHeight;
	// テクスチャー
	std::vector<class Text*> mTexts;
	// テクスチャー
	std::vector<class Button*> mTextures;
	// ボタン
	std::vector<class Button*> mButtons;
};

// タイトル画面
class Title :public Menu {
public:
	Title(class SceneManager* smana, SDL_Window* window, SDL_Renderer* renderer);
	~Title();
protected:
	// 初期化
	void Initialize();
	// ボタンが押されているか判断
	void IsButton(bool isDown);
};

// ステージセレクト画面
class Select :public Menu {
public:
	Select(class SceneManager* smana, SDL_Window* window, SDL_Renderer* renderer);
	~Select();
protected:
	// 初期化
	void Initialize();
	// ボタンが押されているか判断
	void IsButton(bool isDown);

	// ステージファイル名
	std::vector<std::string> mStageData;
};

