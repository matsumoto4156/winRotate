#pragma once
#include <vector>


class PhisicManager {
public:
	PhisicManager();
	~PhisicManager();
	// �ł��߂����̂Ɠ����蔻��E�v���C���[�̈ʒu�𒲐�
	void ManagePlayer();
	// �v���C���[���擾
	// �v���C���[���擾
	void SetPlayer(class Player* player) { mPlayer = player; };
	void SetPlayerCollider(class PlayerCollider* playerC) { mPlayerCollider = playerC; };
	// �����蔻��
	unsigned char  Adjust(class BoxCollider* box);
	// �R���C�_�[��ǉ��E����
	void AddBox(class BoxCollider* box);
	void RemoveBox(class BoxCollider* box);
private:
	class PlayerCollider* mPlayerCollider;
	class Player* mPlayer;
	std::vector<class BoxCollider*> mBoxes;
};