#pragma once
#include "SDL.h"
#include <vector>


// UI 
class UI {
public:
	UI(class SceneManager* scmana, SDL_Window* window);
	~UI();
	// メニュー画面の描写
	void Draw(SDL_Renderer* renderer);
	void Input(SDL_Event event);
private:
	// 初期化
	void Initialize();
	// ボタンが押されているか判断
	void IsButton(bool isDown);

	// シーンマネージャー
	class SceneManager* mScmana;
	// 今動いているか
	bool mIsRunning;
	// マウスがクリックされている
	bool mPreClick;
	// ボタンの番号
	int mButtonNum;
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