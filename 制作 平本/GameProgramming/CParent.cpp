#include "CParent.h"
#include "Ckey.h"

#define INIT_POSE CVector(20.0f, 0.0f, 0.0f) //�����̎p��
#define VELOCITY CVector(0.0f, 0.0f, 2.0f) //�ړ����x
#define ROTATE_V CVector(0.0f, 2.0f, 0.0f) //��]���x
#define COLLIDER_POS CVector(0.0f, 1.7f, 0.0f) //�R���C�_�̈ʒu
#define PARENT_MODEL "Weapon.obj","Weapon.mtl"

CModel CParent::mModel;
int CParent::sCount = 0;

CParent::CParent()
	
{
	/*if (sCount == 0)
	{
		mModel.Load(PARENT_MODEL);
		
	}*/
	mpModel = &mModel;
	sCount++;
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CTransform::Update();
}


void CParent::Update()
{
	// J L �ŉ�]
	if (CKey::Push('J'))
	{
		mRotation = mRotation + ROTATE_V;
	}
	if (CKey::Push('L'))
	{
		mRotation = mRotation - ROTATE_V;
	}
	//W S �ňړ�
	if (CKey::Push('W'))
	{
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	if (CKey::Push('S'))
	{
		mPosition = mPosition - VELOCITY * mMatrixRotate;
	}
	//�e�̍s��̍X�V
	CTransform::Update();
}

/*****************************************************/
/*  CChild                                           */
/*****************************************************/

CModel CChild::sModel;
int CChild::sCount = 0;

CChild::CChild(CCharacter* parent)
	: mCollider(this, &mMatrix, COLLIDER_POS, 1.0f)
{
	//�e�̃C���X�^���X�̑ޔ�
	mpParent = parent;

	if (sCount == 0)
	{
		
		sModel.Load(PARENT_MODEL);
	}
	mpModel = &sModel;
	//sCount++;
	mScale = CVector(0.5f, 5.5f, 0.5f);
	mPosition = CVector(0.0f, 1.0f, 0.0f);
	mRotation = INIT_POSE;
	CTransform::Update();
}


void CChild::Update()
{
	// I �ōU��
	if (CKey::Push('I'))
	{
		mRotation.mX = 90.0f;
	}
	else
	{
		mRotation = INIT_POSE;
	}
	//�q�̍s��̍X�V
	CTransform::Update();
	//�����̍s��ɐe�̍s����|���āA�ŏI�I�ȍ����s��ɂ���
	mMatrix = mMatrix * mpParent->mMatrix;
}
