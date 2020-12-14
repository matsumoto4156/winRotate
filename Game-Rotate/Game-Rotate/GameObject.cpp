#include "GameObject.h"
#include "Component.h"
#include "Game.h"
#include "RotateComponent.h"

GameObject::GameObject(class Game* game, vector2 position, int scale) :
	mGame(game),
	mState(Active),
	mRotation(0),
	mStagenum(-1),
	mPosition(position),
	mScale(scale),
	mIsRotate(false),
	mGo(false),
	mWidth(0),
	mHeight(0)
{
	mWidth = static_cast<float>(scale / 2);
	mHeight= static_cast<float>(scale / 2);
	mGame->AddObject(this);
	SetStagenum();
	RotateComponent* rotate = new RotateComponent(this, 0);
}


GameObject::~GameObject() {
	mGame->RemoveObject(this);
}

// ゲームから呼び出される更新関数（OR不可）
void GameObject::Update(float deltaTime) {
	UpdateComponent(deltaTime);
	UpdateObject(deltaTime);
}

// コンポーネントを更新（OR不可）
void GameObject::UpdateComponent(float deltaTime) {
	for (Component* cp : mComponents) {
		cp->Update(deltaTime);
	}
}

// 独自の更新関数（OR可能)
void GameObject::UpdateObject(float deltaTime) {
}

// 自分がいるステージを判断
void GameObject::SetStagenum() {
	if (mPosition.x <= mGame->GetStageLoc(1).x) {
		if (mPosition.y <= mGame->GetStageLoc(0).y) {
			mStagenum = 3;
		}
		else {
			mStagenum = 0;
		}
	}
	else {
		if (mPosition.y <= mGame->GetStageLoc(1).y) {
			mStagenum = 2;
		}
		else {
			mStagenum = 1;
		}
	}
}





// コンポーネント追加消去
void GameObject::AddComponent(Component* comp) {
	int order = comp->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter) {
		if ((*iter)->GetUpdateOrder() > order) {
			break;
		}
	}
	mComponents.insert(iter, comp);
}
void GameObject::RemoveComponent(Component* Component){
	auto iter = std::find(mComponents.begin(), mComponents.end(), Component);
	if (iter != mComponents.end()) {
		mComponents.erase(iter);
	}
}