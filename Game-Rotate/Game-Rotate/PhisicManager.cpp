#include "PhisicManager.h"
#include "ColliderComponent.h"
#include "Player.h"
#include <vector>
#include <algorithm>

#include <iostream>

PhisicManager::PhisicManager() :
	mPlayerCollider(0),
	mPlayer(0)
{
}
PhisicManager::~PhisicManager() {

}
// 最も近いものと当たり判定・プレイヤーの位置を調整
void PhisicManager::ManagePlayer() {

	// 最も近いものと当たり判定を行う
	float dist1 = 1000.0f;
	float dist2 = 1100.0f;
	ColliderComponent* target1 = nullptr;
	ColliderComponent* target2 = nullptr;
	vector2 pos = mPlayerCollider->GetPos();

	//unsigned char flag = mPlayerCollider->GetPlayerStage();
	for (auto b : mBoxes) {
		//if ((flag & static_cast<unsigned char>(pow(2,(b->GetOwner()->GetStagenum())))) != 0) {
		float a = mPlayer->GetPos().distance(b->GetPos());
		if (a < dist2) {
			if (a < dist1) {
				dist2 = dist1;
				dist1 = a;
				target2 = target1;
				target1 = b;
			}
			else {
				dist2 = a;
				target2 = b;
			}
		}
	}
	if (target1 == nullptr && target2 == nullptr) {
		SDL_Log("No Block in Player Stage");
		return;
	}
	// 当たり判定センサーを動かす
	unsigned char cencer = Cencer(target1) | Cencer(target2);
	Adjust(mPlayerCollider, target1);
	Adjust(mPlayerCollider, target2);
	mPlayer->SetCencer(cencer);

	
	for (ColliderComponent* move : mMoves) {
		// 最も近いものと当たり判定を行う
		float dist1 = 1000.0f;
		float dist2 = 1100.0f;
		ColliderComponent* target1 = nullptr;
		ColliderComponent* target2 = nullptr;
		vector2 pos = move->GetPos();
		for (auto b : mBoxes) {
			float a = move->GetPos().distance(b->GetPos());
			if (a == 0.0f) continue;
			if (a < dist2) {
				if (a < dist1) {
					dist2 = dist1;
					dist1 = a;
					target2 = target1;
					target1 = b;
				}
				else {
					dist2 = a;
					target2 = b;
				}
			}
		}
		if (target1 == nullptr && target2 == nullptr) {
			SDL_Log("No Block in Player Stage");
			return;
		}
		Adjust(move, target1);
		Adjust(move, target2);
	}
}



// 当たり判定
bool PhisicManager::Adjust(ColliderComponent* move, ColliderComponent* target){

	bool no = move->GetRightTop().x < target->GetLeftBottom().x ||
		target->GetRightTop().x < move->GetLeftBottom().x ||
		move->GetRightTop().y > target->GetLeftBottom().y ||
		target->GetRightTop().y > move->GetLeftBottom().y;

	// 当たっていなければ終了
	if (no) {
		return false;
	}
	// 当たっているとき関数
	target->OnCollider();
	// 衝突しないときcencerいらない
	if (!target->GetIsColl()) {
		return false;
	}

	// 当たっていたら位置を調節
	float dx1 = move->GetRightTop().x - target->GetLeftBottom().x;
	float dx2 = move->GetLeftBottom().x - target->GetRightTop().x;
	float dy1 = move->GetRightTop().y - target->GetLeftBottom().y;
	float dy2 = move->GetLeftBottom().y - target->GetRightTop().y;
	// 最小の距離を測定
	float dx = (std::abs(dx2) > std::abs(dx1)) ? dx1 : dx2; int a = 5;
	float dy;
	if (std::abs(dy2) < std::abs(dy1)) {
		dy = dy2;
	}
	else { dy = dy1; };
	if (std::abs(dy) > std::abs(dx)) {
		vector2 pos = move->GetOwner()->GetPos();
		pos.x -= dx;
		move->GetOwner()->SetPos(pos);
	}
	else {
		vector2 pos = move->GetOwner()->GetPos();
		pos.y -= dy;
		move->GetOwner()->SetPos(pos);
	}
	// プレイヤーのコリダーも更新
	move->SetLoc();
}

// センサー判定
unsigned char PhisicManager::Cencer(ColliderComponent* target) {
	if (!target->GetIsColl()) return 0;


	// センサーフラッグ
	unsigned char cencer = 0;
	float height = (mPlayerCollider->GetLeftBottom().y - mPlayerCollider->GetRightTop().y) / 2;
	float width = (mPlayerCollider->GetRightTop().x - mPlayerCollider->GetLeftBottom().x) / 2;
	width -= 2.0f;
	height -= 1.0f;
	// 頭がついているか判定
	vector2 head;
	head.x = mPlayerCollider->GetPos().x;
	head.y = mPlayerCollider->GetRightTop().y - 0.3f;
	cencer |= target->GetLeftBottom().x <= head.x &&
		head.x <= target->GetRightTop().x &&
		target->GetRightTop().y <= head.y &&
		head.y <= target->GetLeftBottom().y;
	// 当たっているか判定
	vector2 forward;
	for (int i = 0; i < 3; ++i) {
		forward.x = mPlayerCollider->GetPos().x + (width + 2.2f) * mPlayer->GetDir();
		forward.y = mPlayerCollider->GetRightTop().y + 1.0f + height * i;
		cencer |= ((target->GetLeftBottom().x <= forward.x &&
			forward.x <= target->GetRightTop().x &&
			target->GetRightTop().y <= forward.y &&
			forward.y <= target->GetLeftBottom().y) << 1);
	}
	// 地面についているか判定
	vector2 foot;
	for (int i = 0; i < 3; ++i) {
		foot.x = mPlayerCollider->GetLeftBottom().x + 1.0f + width*i;
		foot.y = mPlayerCollider->GetLeftBottom().y + 0.2f;
		cencer |= ((target->GetLeftBottom().x <= foot.x &&
			foot.x <= target->GetRightTop().x &&
			target->GetRightTop().y <= foot.y &&
			foot.y <= target->GetLeftBottom().y) << 2);
	}
	return cencer;
}

// コライダーを追加
void PhisicManager::AddBox(ColliderComponent* box) {
	mBoxes.emplace_back(box);
}
// コライダーを消去
void PhisicManager::RemoveBox(ColliderComponent* box) { 
	auto iter = std::find(mBoxes.begin(), mBoxes.end(), box);
	if (iter != mBoxes.end()) {
		mBoxes.erase(iter);
	}
};

// コライダーを追加
void PhisicManager::AddMove(ColliderComponent* box) {
	mMoves.emplace_back(box);
}
// コライダーを消去
void PhisicManager::RemoveMove(ColliderComponent* box) {
	auto iter = std::find(mMoves.begin(), mMoves.end(), box);
	if (iter != mMoves.end()) {
		mMoves.erase(iter);
	}
};