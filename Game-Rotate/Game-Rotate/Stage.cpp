#include "Stage.h"
#include <string>
#include <iostream>

Stage::Stage() :
	mArray(0),
	mCoord(0),
	mCCC(0),
	mXofOne(0),
	mYofOne(0),
	mSizeofOne(0),
	mNumofStage(0)
{
}

Stage::~Stage() {
	delete[] mArray;
	delete[] mCoord;
	delete[] mCCC;
	mArray = 0;
	mCoord = 0;
	mCCC = 0;
}


//�T�C�Y���Z�b�g
void Stage::SetSize(int size0, int size1, int numOfStage) {
	mArray = new int[size0 * size1 * numOfStage];
	mCoord = new vector2[size0 * size1 * numOfStage];
	mCCC = new vector2[size0 * size1 * numOfStage];
	mXofOne = size0;
	mYofOne = size1;
	mSizeofOne = size0 * size1;
	mNumofStage = numOfStage;
}

// ���g�ɃA�N�Z�X
int& Stage::operator () (int index0, int index1, int stageNumber){
	return mArray[mSizeofOne * stageNumber + index0 + index1 * mXofOne];
}

// ���g�ɃA�N�Z�X
const int& Stage::operator () (int index0, int index1, int stageNumber) const {
	return mArray[mSizeofOne * stageNumber + index0 + index1 * mXofOne];
}

// �e�X�e�[�W�̐����\�L���o��
void Stage::Show() {
	std::string str = "\n";
	for (int i = 0; i < 4; ++i) {
		str += "<Stage";
		str += static_cast<char>(i + 49);
		str += ">\n";
		for (int k = 0; k < mYofOne; ++k) {
			for (int l = 0; l < mXofOne ; ++l) {
				str += static_cast<char>(48 + operator()(l, k, i));
			}
			str += '\n';
		}
		str += '\n';
	}
	char a = static_cast<char>(48 + operator()(0, 0, 0));
	std::cout << str << std::endl;

}

// ���W������
void Stage::SetCoord(int stage, vector2 start, int one) {
	start = start + vector2{ one/2.0f, one/2.0f };
	for (int y = 0; y < mYofOne; ++y) {
		for (int x = 0; x < mXofOne; ++x) {
			mCoord[stage*mSizeofOne + y*GetX()+x] = start + vector2{ one*x*1.0f, 0 };
		}
		start.y += one;
	}

}

// ���W������
void Stage::SetCCC(vector2 start, int one) {
	start = start + vector2{ one / 2.0f, one / 2.0f };
	for (int y = 0; y < mYofOne * 2; ++y) {
		for (int x = 0; x < mXofOne * 2; ++x) {
			mCCC[y * mXofOne * 2 + x] = start + vector2{ one * x * 1.0f, 0 };
		}
		start.y += one;
	}

	//for (int i = 0; i < mSizeofOne * mNumofStage; ++i) {
	//	cout << "���W : x " << mCCC[i].x << " y " << mCCC[i].y << endl;

	//}
}
