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
	int GetNumOfStage() { return mNumofStage; };
	int SizeOfOne() { return mSizeofOne; };
	// 入力時と同じ形で出力
	void Show();
	int GetX() { return mXofOne; };
	int GetY() { return mYofOne; };
private:
	int* mArray;
	// １ステージごとの大きさ
	int mXofOne;
	int mYofOne;
	int mSizeofOne;
	// ステージの数
	int mNumofStage;
};