#pragma once
#include "SDL.h"
#include "vector2.h"

// 三次元風配列
class Stage {
public:
	Stage();
	~Stage();
	// サイズをセット
	void SetSize(int size0, int size1, int numOfStage);
	// 中身にアクセス
	int& operator () (int index0, int index1, int stageNumber);
	const int& operator () (int index0, int index1, int stageNumber) const;
	// 入力時と同じ形で出力
	void Show();
	// 座標列を作る
	void SetCoord(int stage, vector2 start, int lendth);
	void SetCCC(vector2 start, int lendth);
	// ゲッター
	vector2 GetCoord(int x, int y, int stageNumber) { return mCoord[mSizeofOne * stageNumber + x + y * mXofOne]; };
	vector2 GetCCC(int num) { return mCCC[num]; };
	int GetNumOfStage() { return mNumofStage; };
	int SizeOfOne() { return mSizeofOne; };
	int GetX() { return mXofOne; };
	int GetY() { return mYofOne; };
private:
	// ステージの配列
	int* mArray;
	// 座標の配列
	vector2* mCoord;
	vector2* mCCC;
	// １ステージごとの大きさ
	int mXofOne;
	int mYofOne;
	int mSizeofOne;
	// ステージの数
	int mNumofStage;
};