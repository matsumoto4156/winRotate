#include "Background.h"
#include "SpriteComponent.h"
#include "RotateComponent.h"

Background::Background(Game* Game, vector2 position, int scale, const char* filename) :
	GameObject(Game, position, scale),
	mRect(0),
	mFilename(filename)
{
	TextureSprite* mRect = new TextureSprite(this, 0, mFilename);
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