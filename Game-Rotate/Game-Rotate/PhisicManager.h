#pragma once
#include <vector>


class PhisicManager {
public:
	PhisicManager();
	~PhisicManager();
	// 最も近いものと当たり判定・プレイヤーの位置を調整
	void ManagePlayer();
	// プレイヤーを取得
	void SetPlayer(class Player* player) { mPlayer = player; };
	void SetPlayerCollider(class PlayerCollider* playerC) { mPlayerCollider = playerC; };
	// コライダーを追加・消去
	void AddBox(class ColliderComponent* box);
	void RemoveBox(class ColliderComponent* box);
	// コライダーを追加・消去
	void AddMove(class ColliderComponent* box);
	void RemoveMove(class ColliderComponent* box);
private:
	// 当たり判定(0あたってない、1横から、2縦から)
	int Adjust(class ColliderComponent* move, class ColliderComponent* target);
	// センサー判定
	unsigned char Cencer(class ColliderComponent* target);

	class PlayerCollider* mPlayerCollider;
	class Player* mPlayer;
	std::vector<class ColliderComponent*> mBoxes;
	std::vector<class ColliderComponent*> mMoves;
};