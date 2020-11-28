#pragma once
#include <vector>


class PhisicManager {
public:
	PhisicManager();
	~PhisicManager();
	// 最も近いものと当たり判定・プレイヤーの位置を調整
	void ManagePlayer();
	// プレイヤーを取得
	// プレイヤーを取得
	void SetPlayer(class Player* player) { mPlayer = player; };
	void SetPlayerCollider(class PlayerCollider* playerC) { mPlayerCollider = playerC; };
	// 当たり判定
	unsigned char  Adjust(class BoxCollider* box);
	// コライダーを追加・消去
	void AddBox(class BoxCollider* box);
	void RemoveBox(class BoxCollider* box);
private:
	class PlayerCollider* mPlayerCollider;
	class Player* mPlayer;
	std::vector<class BoxCollider*> mBoxes;
};