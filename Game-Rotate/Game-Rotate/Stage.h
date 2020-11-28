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
	int GetNumOfStage() { return mNumofStage; };
	int SizeOfOne() { return mSizeofOne; };
	// ���͎��Ɠ����`�ŏo��
	void Show();
	int GetX() { return mXofOne; };
	int GetY() { return mYofOne; };
private:
	int* mArray;
	// �P�X�e�[�W���Ƃ̑傫��
	int mXofOne;
	int mYofOne;
	int mSizeofOne;
	// �X�e�[�W�̐�
	int mNumofStage;
};