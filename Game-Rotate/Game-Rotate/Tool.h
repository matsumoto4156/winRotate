#pragma once
#include "SDL.h"
#include "vector2.h"


// �I�u�W�F�N�g��z�u����c�[��
class Tool {
public:
	Tool(class Make* make, int objectnum);
	~Tool();
	// �ʒu�����߂�
	void SetPosition(float x, float y);
	// �T�C�Y�����߂�
	void SetSize(int width, int height) { mTextWidth = width; mTextHeight = height; };
	// �{�^����������Ă��邩
	bool IsButton(int x, int y);
	// �e�N�X�`���[��n��
	SDL_Texture* GetTexture() { return mTexture; };
	// �`��
	void Draw(SDL_Renderer* renderer);
	// ���ǂꂭ�炢�g������
	int GetUsuY() { return mTextHeight / 2; };
	// ���ǂꂭ�炢�g������
	int GetUsuX() { return mTextWidth / 2; };
private:
	// ������
	void Initialize();

	// ���C�N�N���X
	class Make* mMake;
	// �e�N�X�`���̑傫��
	int mTextWidth;
	int mTextHeight;
	// �ǂ̃I�u�W�F�N�g��
	int mObjectNumber;
	// �I������Ă��邩
	bool mOnThis;
	// �e�N�X�`���[
	SDL_Texture* mTexture;
	SDL_Texture* mFrameTexture;
	SDL_Texture* mOnTexture;
	// �ʒu
	vector2 mPosition;
	vector2 mLeftTop;
	vector2 mRightDown;
	// �t�@�C�����̃��X�g
	const char** mFilenames;
};

