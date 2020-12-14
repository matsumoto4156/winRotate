#pragma once
#include <vector>


class PhisicManager {
public:
	PhisicManager();
	~PhisicManager();
	// �ł��߂����̂Ɠ����蔻��E�v���C���[�̈ʒu�𒲐�
	void ManagePlayer();
	// �v���C���[���擾
	void SetPlayer(class Player* player) { mPlayer = player; };
	void SetPlayerCollider(class PlayerCollider* playerC) { mPlayerCollider = playerC; };
	// �R���C�_�[��ǉ��E����
	void AddBox(class ColliderComponent* box);
	void RemoveBox(class ColliderComponent* box);
	// �R���C�_�[��ǉ��E����
	void AddMove(class ColliderComponent* box);
	void RemoveMove(class ColliderComponent* box);
private:
	// �����蔻��(0�������ĂȂ��A1������A2�c����)
	int Adjust(class ColliderComponent* move, class ColliderComponent* target);
	// �Z���T�[����
	unsigned char Cencer(class ColliderComponent* target);

	class PlayerCollider* mPlayerCollider;
	class Player* mPlayer;
	std::vector<class ColliderComponent*> mBoxes;
	std::vector<class ColliderComponent*> mMoves;
};