#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"

class Background : public GameObject {
public:
	Background(class Game* Game, vector2 position, int scale);
	~Background();
	// �Ǝ��̃A�b�v�f�[�g
	void UpdateObject(float deltaTime);
	//�F��ݒ�
	void SetColor( SpriteComponent::Color color);
private:
	class RectSprite* mRect;
};