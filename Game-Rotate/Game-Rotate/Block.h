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
	// �Ԃ������p�iOR���Ăˁj
	virtual void CollideDo(GameObject* target, int from) {};
	// �Z���T�[�Ɉ��������邩
	virtual bool IsCencer() { return true; };
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
	// �e�N�X�`���[
	class TextureSprite* mText;
	// �d�̓R���|
	class GravityComponent* mGra;
	// �d�̓R���|
	class BoxCollider* mBox;
	// �������~�߂鎞��
	float mWaitTime;
	// �n�ʂɂ��Ă��邩
	bool mGround;
	// �t�@�C�����C
	const char* mFilename;
	// �O��y
	float mPreY;
	// ��������
	bool mStick;
};

// �ؔ��u���b�N
class CrateBlock : public Block {
public:
	CrateBlock(Game* Game, vector2 position, int scale);
	~CrateBlock();
	// �Ǝ��̍X�V�֐�
	void UpdateObject(float deltaTime);
	// �������~�߂�
	void IsKeynematic(float time);
	// �n�ʔ���
	bool GetGround() { return mGround; };
	void SetGround(bool ground) { mGround = ground; };
	// �Ԃ������Ƃ�
	void CollideDo(GameObject* target, int from);
	// �Z���T�[�Ɉ��������邩
	bool IsCencer() { return false; };
	
private:
	// �d�̓R���|
	class GravityComponent* mGra;
	// �d�̓R���|
	class BoxCollider* mBox;
	// �������~�߂鎞��
	float mWaitTime;
	// �n�ʂɂ��Ă��邩
	bool mGround;
	// �t�@�C�����C
	const char* mFilename;
	// �ړ��X�s�[�h�Ə��
	float mMoveSpeed;
	float mMaxSpeed;
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
	void CollideDo(GameObject* go, int from);
	// �Z���T�[�Ɉ��������邩
	bool IsCencer() { return false; };
private:
	// �ǂ̃X�e�[�W����]�����邩
	int mStage;
	const char* mFilename;
	// ���t���[���҂�
	int mCount;
};
