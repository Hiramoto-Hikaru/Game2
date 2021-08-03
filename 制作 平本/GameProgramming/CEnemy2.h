#ifndef CENEMY2_H
#define CENEMY2_H
//�L�����N�^�N���X�̃C���N���[�h
#include"CCharacter.h"
//�R���C�_�N���X�̃C���N���[�h
#include"CCollider.h"
#include"CText.h"
/*�G�l�~�[�N���X
�L�����N�^�N���X���p��	*/
class CEnemy2 :public CCharacter {
public:
	//���f���f�[�^
	static CModel mModel;
	//�R���C�_
	CCollider mCollider;
	//�R���X�g���N�^	
	CEnemy2();
	CVector mPoint;//�ڕW�n�_
	int mHp;//�̗�
	int mJump;
	int mJump2;
	CText mText;
	
	//CEnemy2(�ʒu�A��]�A�g�k�j
	CEnemy2(const CVector& position, const CVector& rotation, const CVector& scale);
	CCollider mColSearch;//�T�[�`�p�R���C�_
	//�X�V����
	void Update();
	//�Փˏ���
	//Collision(�R���C�_�P�A�R���C�_�Q�j
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
	CCharacter* mpPlayer;//�v���C���[�̃|�C���^
	int mEnemyDamage;
};
#endif