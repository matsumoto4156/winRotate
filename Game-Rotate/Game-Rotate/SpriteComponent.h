#pragma once

#include "SDL.h"
#include "Component.h"
#include "vector2.h"

class SpriteComponent : public Component {
public:
	struct Color {
		Uint8 red = 0;
		Uint8 blue = 0;
		Uint8 green = 0;
		Uint8 alpha = 0;
	};
	SpriteComponent(class GameObject* owner, int updateOrder);
	virtual ~SpriteComponent();
	void Update(float delataTime) {};
	// �`�ʂ̏��Ԃ����߂�i�f�t�H��1�j
	void SetDrawOrder(int order) { mDrawOrder = order; };
	int GetDrawOrder() { return mDrawOrder; };
	// ���ꂼ��̕`�ʁiOR���Ăˁj
	virtual void Draw(SDL_Renderer* renderer);
private:
	int mDrawOrder;
};

class RectSprite : public SpriteComponent {
public:
	RectSprite(class GameObject* owner, int updateOrder);
	~RectSprite();
	// �����`��`��
	void Draw(SDL_Renderer* renderer);
	// �F��ݒ�E�Ԃ�
	void SetColor(Color color) { mColor = color; };
	Color GetColor() { return mColor; };
private:
	// �`�ʂɕK�v�ȕϐ����m��
	void SetLoc();
	Color mColor;
	vector2 mLeftTop;
	int mLendth;
};

class TextureSprite : public SpriteComponent {
public:
	TextureSprite(class GameObject* owner, int updateOrder, const char* filename, bool state = true);
	~TextureSprite();
	// �摜��`��
	void Draw(SDL_Renderer* renderer);
	// �摜�̌�����ς���
	void SetFlip(int right);
	// �`�ʂ��邩�ւ񂱂�
	void SetState(bool state) { mState = state; };
private:
	// �摜�T�C�Y���Z�b�g
	void SetTexture();
	SDL_Texture* mTexture;
	int mTextWidth;
	int mTextHeight;
	SDL_RendererFlip mFlip;
	// �`�ʂ��邩�ǂ���
	bool mState;
};