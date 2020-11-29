#pragma once
#include "SDL.h"
#include "Stage.h"
#include <vector>
#include <unordered_map>

#include <iostream>


class Game {
public:
	Game();
	~Game();
	// 初期化
	bool Initialize();
	// ループの内容
	void MainLoop();
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
	vector2 GetStageLoc(int stageNumber);
	class PhisicManager* GetPManager() { return mPManager; };
	// 回転を行う
	void Rotate(int stage);
	

private:
	// 最初のロードを行う
	void LoadData();
	// ステージの読み取り
	void LoadStage();
	// ステージ座標の読み取り
	void InitStageLoc();
	// 背景を描写する
	void MakeBack();
	// ループのヘルパー関数群
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	// 画像読み取りの関数
	SDL_Texture* LoadTexture(const char* filename);

	// プレイヤーはもっておこう
	class Player* mPlayer;

	// SDLのウィンドウ
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	Uint32 mPreviousTime;

	// テクスチャーのマップ
	std::unordered_map<const char*, SDL_Texture*> mTextures;

	// オブジェトの配列
	std::vector<class GameObject*> mObjects;	  // 活動組
	std::vector<class GameObject*> mWaitObjects;  // 待機組
	// スプライトの配列
	std::vector<class SpriteComponent*> mSprites;
	// ステージ配列
	class Stage mStage;
	// 更新中かを返す
	bool mUpdatingObjects;
	// ステージの座標
	vector2* mLeftTops;
	// 物理かんりのクラス
	class PhisicManager* mPManager;
	// 人マス当たりの大きさ
	int mSize;
};