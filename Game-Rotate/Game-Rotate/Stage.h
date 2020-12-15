#pragma once
#include "SDL.h"
#include "vector2.h"

// �O�������z��
class Stage {
public:
	Stage();
	~Stage();
	// �T�C�Y���Z�b�g
	void SetSize(int size0, int size1, int numOfStage);
	// ���g�ɃA�N�Z�X
	int& operator () (int index0, int index1, int stageNumber);
	const int& operator () (int index0, int index1, int stageNumber) const;
	// ���͎��Ɠ����`�ŏo��
	void Show();
	// ���W������
	void SetCoord(int stage, vector2 start, int lendth);
	void SetCCC(vector2 start, int lendth);
	// �Q�b�^�[
	vector2 GetCoord(int x, int y, int stageNumber) { return mCoord[mSizeofOne * stageNumber + x + y * mXofOne]; };
	vector2 GetCCC(int num) { return mCCC[num]; };
	int GetNumOfStage() { return mNumofStage; };
	int SizeOfOne() { return mSizeofOne; };
	int GetX() { return mXofOne; };
	int GetY() { return mYofOne; };
private:
	// �X�e�[�W�̔z��
	int* mArray;
	// ���W�̔z��
	vector2* mCoord;
	vector2* mCCC;
	// �P�X�e�[�W���Ƃ̑傫��
	int mXofOne;
	int mYofOne;
	int mSizeofOne;
	// �X�e�[�W�̐�
	int mNumofStage;
};