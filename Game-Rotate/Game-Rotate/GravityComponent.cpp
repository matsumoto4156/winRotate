#include "GravityComponent.h"
#include "GameObject.h"


GravityComponent::GravityComponent(class GameObject* owner, int updateOrder):
	Component(owner, updateOrder),
	mGravity(0.0f),
	mMaxGravity(10.0f),
	mGround(false){
}

GravityComponent::~GravityComponent() {
}

void GravityComponent::Update(float deltaTime) {
	vector2 pos = mOwner->GetPos();
	if (mOwner->GetGround()) {
		mGravity = 0;
	}
	else{
		if (mGravity < mMaxGravity) {
			mGravity += 0.7f;
		}
	}
		pos.y += mGravity;
		mOwner->SetPos(pos);
}