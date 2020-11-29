#pragma once
#include "GameObject.h"

// �u���b�N�̊��N���X
class Block : public GameObject {
public:
	Block(Game* game, vector2 position, int scale);
	virtual ~Block();
	// �Ǝ��̍X�V�֐�
	virtual void UpdateObject(float deltaTime) {};
	// �������~�߂�
	virtual void IsKeynematic(float time) {};
	// �n�ʔ���p�iOR���Ăˁj
	virtual bool GetGround() { return false; };
private:
	const char* mFilename;
};




//�@��]����u���b�N
class RotateBlock : public Block {
public:
	RotateBlock(Game* Game, vector2 position, int scale);
	~RotateBlock();
private:
	const char* mFilename;
};


// �ǂ̃u���b�N
class WallBlock : public Block {
public:
	WallBlock(Game* Game, vector2 position, int scale);
	~WallBlock();
private:
	const char* mFilename;
};


// �������u���b�N
class StickBlock : public Block {
public:
	StickBlock(Game* Game, vector2 position, int scale);
	~StickBlock();
	// �Ǝ��̍X�V�֐�
	void UpdateObject(float deltaTime);
	// �������~�߂�
	void IsKeynematic(float time);
	// �n�ʔ���
	bool GetGround() { return mGround; };
	void SetGround(bool ground) { mGround = ground; };

private:
	// �������~�߂鎞��
	float mWaitTime;
	// �n�ʂɂ��Ă��邩
	bool mGround;
	// �t�@�C�����C
	const char* mFilename;
};


// �t���b�O
class Flag : public GameObject {
public:
	Flag(Game* game, vector2 position, int scale, int stage, const char* filename);
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
