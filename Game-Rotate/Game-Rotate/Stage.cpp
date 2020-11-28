#include "Stage.h"
#include <string>
#include <iostream>

Stage::Stage() :
	mArray(0),
	mXofOne(0),
	mYofOne(0),
	mSizeofOne(0),
	mNumofStage(0)
{
	mArray = new int[mXofOne * mYofOne * mNumofStage];
}

Stage::~Stage() {
	delete[] mArray;
	mArray = 0;
}


//�T�C�Y���Z�b�g
void Stage::SetSize(int size0, int size1, int numOfStage) {
	mArray = new int[size0 * size1 * numOfStage];
	mXofOne = size0;
	mYofOne = size1;
	mSizeofOne = size0 * size1;
	mNumofStage = numOfStage;
}

// ���g�ɃA�N�Z�X
int& Stage::operator () (int index0, int index1, int stageNumber){
	return mArray[mSizeofOne * stageNumber + index0 + index1 * mYofOne];
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
