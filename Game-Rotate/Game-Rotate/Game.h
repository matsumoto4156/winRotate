#pragma once
#include "SDL.h"
#include "Stage.h"
#include <vector>
#include <unordered_map>

#include <iostream>


class Game {
public:
	Game(class SceneManager* scmana, const char* stagefile, SDL_Window* window, SDL_Renderer* renderer, bool displayMode = false);
	~Game();
	// 初期化
	bool Initialize();
	// ループの内容
	bool MainLoop();
	// ゲームを終了する
	void Shutdown();
	// ゲームオブジェクトを追加/消去
	void AddObject(class GameObject* object);
	void RemoveObject(class GameObject* object);
	// レンダーを渡す
	SDL_Renderer* GetRenderer() { return mRenderer; };
	// テクスチャーを渡す
	SDL_Texture* GetTexture(const char* filename);
	// スプライトを追加
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	// ゲッター
	class UI* GetUI() { return mUI; };
	class Stage* GetStage() { return &mStage; };
	vector2 GetStageLoc(int stageNumber);
	class PhisicManager* GetPManager() { return mPManager; };
	// 回転を行う
	void Rotate(int stage);
	// メイクモード用
	void Draw(SDL_Renderer* renderer);
	

private:
	// 最初のロードを行う
	void LoadData();
	// ステージの読み取り
	void LoadStage();
	// ステージ座標の読み取り
	void InitStageLoc();
	// 背景を描写する
	void MakeBack();
	// プレイヤーを出す
	void SetPlayer();
	// ループのヘルパー関数群
	void Input();
	void UpdateGame();
	void Display();
	// 画像読み取りの関数
	SDL_Texture* LoadTexture(const char* filename);

	// シーンマネージャー
	class SceneManager* mScmana;
	// 物理かんりのクラス
	class PhisicManager* mPManager;
	// プレイヤーはもっておこう
	class Player* mPlayer;
	// UIは自分で管理する
	class UI* mUI;

	// SDLのウィンドウ
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	// テクスチャーのマップ
	std::unordered_map<const char*, SDL_Texture*> mTextures;
	// オブジェトの配列
	std::vector<class GameObject*> mObjects;	  // 活動組
	std::vector<class GameObject*> mWaitObjects;  // 待機組
	// スプライトの配列
	std::vector<class SpriteComponent*> mSprites;
	// ステージ配列
	class Stage mStage;

	// 動いているか
	bool mIsRunning;
	// 前回の時間
	Uint32 mPreviousTime;
	// ディスプレイモードかどうか
	bool mDisplayMode;
	// 更新中かを返す
	bool mUpdatingObjects;
	// ステージの座標
	vector2* mLeftTops;
	// ステージファイルの名前
	const char* mStageFile;
	// 人マス当たりの大きさ
	int mSize;
};