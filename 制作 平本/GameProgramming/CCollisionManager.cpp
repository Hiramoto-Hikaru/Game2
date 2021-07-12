#include "CCollisionManager.h"
#include"CCollider.h"
#include"CTaskManager.h"
//�}�l�[�W���̃C���X�^���X
CCollisionManager* CCollisionManager::mpInstance = 0;
//�C���X�^���X�̎擾
CCollisionManager* CCollisionManager::Get() {
	//�C���X�^���X���Ȃ����
	if (mpInstance == 0) {
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}
void CCollisionManager::Collision() {
	//�^�X�N���X�g���g��
	//���݈ʒu��擪�ɂ���
	CCollider* task = (CCollider*)mHead.mpNext;
	//�Ō�܂ŗ�����I��
	//task�̎��̏ꍇ
	while (task->mpNext) {
		//���݈ʒu�̎������߂�
		CCollider* next = (CCollider*)task->mpNext;
		//�����O�ɂȂ�����I��
		//next�̎��̏ꍇ
		while (next->mpNext) {
			//�e�̏Փˏ������Ăяo��
			//�����̏Փˏ���
			if (task->mpParent)//task�̐e�̂Ƃ�
				task->mpParent->Collision(task, next);//task����next
			//����̏Փˏ���
			if (next->mpParent)//next�̐e�̂Ƃ�
				next->mpParent->Collision(next, task);//next����task
			//�������߂�
			next = (CCollider*)next->mpNext;

		}
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;

	}
}
void CCollisionManager::Collision(CCollider* c, int range) {

	//���݈ʒu��擪�ɂ���
	CCollider* task = (CCollider*)mHead.mpNext;
	//�͈͂܂œǂݔ�΂�
	//range:�K�p����͈͂�ݒ肷�鐔��
	//�D��x+range���D��x�̏������^�X�N�ɓK�p

	while (task->mpNext) {
		if (task->mPriority <= c->mPriority + range) {
	      //���[�v����߂�
			break;
		}
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}
	//�Ō�܂ŗ�����I������
	//�D��x�[range���D��x�̏������^�X�N�ɂ͓K�p���Ȃ�
	while (task->mpNext) {
		if (task->mPriority <= c->mPriority - range) {
			break;
		}
		//�e�̏Փˏ������Ăяo��
		//�����̏Փˏ���
		if (c->mpParent && c != task)
			c->mpParent->Collision(c, task);
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}
}