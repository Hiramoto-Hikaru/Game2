#ifndef CENEMY_H
#define CENEMY_H
#include"CCharacter.h"
#include"CCollider.h"
class CEnemy :public CCharacter {
public:
	//�R���X�g���N�^
	//CEnemy(���f���A�ʒu�A��]�A�g�k�j

	CEnemy(CModel* model, CVector position, CVector rotation, CVector scale);
void Update();
//�R���C�_
int mHp;
CCollider mCollider1;
CCollider mCollider2;
CCollider mCollider3;
CVector mPoint;//�ڕW�n�_
CCollider mColSearch;//�T�[�`�p�R���C�_
CCharacter* mpPlayer;//�v���C���[�̃|�C���^
int mFireCount;
//�Փˏ���
//Collision(CCollider*m,CCollider*o)
void Collision(CCollider* m, CCollider* o);

void TaskCollision();

}; 
#endif