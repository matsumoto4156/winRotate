#pragma once
#include "GameObject.h"

class Block : public GameObject {
public:
	Block(Game* game, vector2 position, int scale);
	~Block();
	// �Ǝ��̍X�V�֐�
	virtual void UpdateObject();
private:
	const char* mFilename;
};

class RotateBlock : public Block {
public:
	RotateBlock(Game* Game, vector2 position, int scale);
	~RotateBlock();

private:
	const char* mFilename;
};

class WallBlock : public Block {
public:
	WallBlock(Game* Game, vector2 position, int scale);
	~WallBlock();
private:
	const char* mFilename;
};


class Flag : GameObject {
public:
	Flag(Game* game, vector2 position, int scale, int stage);
	~Flag();
	// �Ǝ��̍X�V�֐�
	void UpdateObject(float deltaTime);
	// �X�e�[�W������]������
	void RotateStage(int stagenum);
	// �����蔻��̂Ƃ��ɌĂ΂��֐�
	void CollideDo();
private:
	// �ǂ̃X�e�[�W����]�����邩
	int mStage;
	const char* mFilename;
	// ���t���[���҂�
	int mCount;
};