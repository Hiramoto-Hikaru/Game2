#ifndef CCOLLIDER_H
#define CCOLLIDER_H
#include"CCharacter.h"
#include"CTransform.h"
#include "CCollisionManager.h"

//�R���C�_�A�A�A�Փˑ��u
class CCollider :public CTransform,public CTask {
public:
	
	CCharacter* mpParent;//�e
	CMatrix* mpMatrix;//�e�s��
	float mRadius;//���a
	//�R���X�g���N�^
	//CCollider(�e�A�e�s��A�ʒu�A��]�A�g�k�A���a�j
	CCollider(CCharacter* parent, CMatrix* matrix, CVector position, float radius);
	//�f�X�g���N�^
	~CCollider();
	//�`��
	void Render();
	//�Փ˔���
	//CCollision(�R���C�_�P�C�R���C�_�Q�j
	//return true(�Փ˂��Ă���j�@false(�Փ˂��Ă��Ȃ��j
	static bool Collision(CCollider* m, CCollider* o);
	enum EType {
		ESPHERE,//�e�R���C�_
		ETRIANGLE,//�O�p�R���C�_
		ELINE,  //�����R���C�_
       
	};
	EType mType;//�R���C�_�^�C�v
	enum ETag {
        EWEAPONCOLLIDER,
		EPLAYERCOLLIDER,
		EBODY,//�{�̗p
		ESEARCH,//�T�[�`�p
		
	    EENEMYCOLLIDER,
		
		EENEMY2COLLIDER,
	};
	ETag mTag;

	//���_
	CVector mV[3];
	//�f�t�H���g�R���X�g���N�^
	CCollider();

    //CCollisionTriangleLine(�O�p�R���C�_�A�����R���C�_�A�����l�j
	//return:true(�Փ˂��Ă���j�Afalse(�Փ˂��Ă��Ȃ�)
	//�����l�F�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* adjust);
    //CCollisionTriangleSphere(�O�p�R���C�_�A���R���C�_�A�����l�j
	//return:true(�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l�F�������Ȃ��ʒu�܂Ŗ߂��l
	static bool CCollider::CollisionTriangleSphere(CCollider* triangle, CCollider* sphere, CVector* adjust);
	void ChangePriority();
	
};
#endif
