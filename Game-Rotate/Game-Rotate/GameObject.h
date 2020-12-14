
#pragma once
#include <vector>
#include "vector2.h"
#include "SDL.h"

class GameObject {
public:
	enum State {
		Active,
		Unactive
	};
	GameObject(class Game* game, vector2 position, int scale);
	virtual ~GameObject();

	// ゲームから呼び出される更新関数（OR不可）
	void Update(float deltaTime);
	// コンポーネントを更新（OR不可）
	void UpdateComponent(float deltaTime);
	// 独自の更新関数（OR可能)
	virtual void UpdateObject(float deltaTime);
	// 自分がいるステージを判断
	void SetStagenum();
	// 当たり判定のときに呼ばれる関数
	virtual void CollideDo(GameObject* go, int from) {};
	// 動きを止める
	virtual void IsKeynematic(float time) {};


	// ゲッター・セッター
	void SetState(State state) { mState = state; };
	void SetPos(vector2 position) { mPosition = position; };
	void SetScale(int scale) { mScale = scale; };
	void SetRotation(float radian) { mRotation = radian; };
	void SetIsRotate(bool isRotate ) { mIsRotate = isRotate; };
	void SetWidth(float width) { mWidth = width; };
	void SetHeight(float height) { mHeight = height; };
	float GetWidth() { return mWidth; };
	float GetHeight() { return mHeight; };
	bool GetIsRotate() { return mIsRotate;  };
	State GetState() { return mState; };
	vector2 GetPos() { return mPosition; };
	int GetScale() { return mScale; };
	float GetRotation() { return mRotation; };
	class Game* GetGame() { return mGame; };
	int GetStagenum() { return mStagenum; };
	// 実際にまわすの関数
	void Go(bool go) { mGo = go; };
	bool CanGo() { return mGo; }
	// コンポーネント追加消去
	void AddComponent(class Component* Component);
	void RemoveComponent(class Component* Component);

	// センサーに引っかかるか
	virtual bool IsCencer() { return true; };

	// 地面判定用（ORしてね）
	virtual void SetGround(bool yes) {  };
	virtual bool GetGround() { return false; };
	// すぴーど
	virtual float GetSpeed() { return 0.0f; };
protected:
	// オブジェクトの状態
	State mState;
	// 座標
	vector2 mPosition; // 中心
	int mScale;
	//横・たて
	float mWidth;
	float mHeight;
	float mRotation; // ラジアン
	// オブジェクトが持つコンポーネント
	std::vector<class Component*> mComponents;
	class Game* mGame;
	// 自分がいるステージ
	int mStagenum;
	// 回るか
	bool mIsRotate;
	// 実際に回す
	bool mGo;
};