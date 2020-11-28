#include "Background.h"
#include "SpriteComponent.h"

Background::Background(Game* Game, vector2 position, int scale) :
	GameObject(Game, position, scale),
	mRect(0)
{
	mRect = new RectSprite(this, 0);
	mRect->SetDrawOrder(0);
}

Background::~Background() 
{
	delete[] mRect;
	mRect = 0;
}
// XV
void Background::UpdateObject(float deltaTime) {

}
//F‚ðÝ’è
void Background::SetColor(SpriteComponent::Color color) {
	mRect->SetColor(color);
}