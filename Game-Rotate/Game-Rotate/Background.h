#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"

class Background : public GameObject {
public:
	Background(class Game* Game, vector2 position, int scale, const char* filename);
	~Background();
	// 独自のアップデート
	void UpdateObject(float deltaTime);
	//色を設定
	void SetColor( SpriteComponent::Color color);
private:
	class RectSprite* mRect;
	const char* mFilename;
};