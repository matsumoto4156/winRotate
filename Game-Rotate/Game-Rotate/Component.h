#pragma once

class Component {
public:
	Component(class GameObject* owner, int updateOrder);
	virtual ~Component();
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; };
	// ÉQÉbÉ^Å[
	class GameObject* GetOwner() { return mOwner; };
protected:
	class GameObject* mOwner;
	int mUpdateOrder;
};