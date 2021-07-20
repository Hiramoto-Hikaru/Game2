#include "CParent.h"
#include "Ckey.h"
#include"CPlayer.h"
#define INIT_POSE CVector(0.0f, 0.0f, 1.0f) //�����̎p��
#define VELOCITY CVector(0.0f, 0.0f, 2.0f) //�ړ����x
#define ROTATE_V CVector(0.0f, 2.0f, 0.0f) //��]���x
#define COLLIDER_POS CVector(0.0f, 2.0f, 0.0f) //�R���C�_�̈ʒu
#define PARENT_MODEL "Weapon.obj","Weapon.mtl"
#define G 1,0f
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
	mScale = CVector(5.5f, 5.5f, 5.5f);
	mPosition = CVector(0.0f, 1.5f, 0.0f);
	mRotation = INIT_POSE;
	CTransform::Update();
}


void CChild::Update()
{
	
	// I �ōU��
	/*if (CKey::Push(VK_SPACE))
	{
		mRotation.mX = 90.0f;
	}*/
	
	
		
	

	if (CPlayer::mAction1 < 60) {
		
		mRotation.mX += 20.0f;
		CPlayer::mAction1++;
	}
	else if (CPlayer::mAction2 < 60) {
		if (mRotation.mX < 90) {
			mRotation.mX = 90.0f;
		}
		mRotation.mY += 20.0f;
		CPlayer::mAction2++;
	}
	else if (CPlayer::mAction3 < 60) {
		mRotation.mZ += 20.0f;
		CPlayer::mAction3++;
	}
	if (mPosition.mY > 1.5f) {
		mPosition.mY -= 1.0f;
	}
	else if(CPlayer::mAction1>=60&& CPlayer::mAction2 >= 60&& CPlayer::mAction3 >= 60) {
        mRotation = INIT_POSE;
	}
	//�q�̍s��̍X�V
	CTransform::Update();
	//�����̍s��ɐe�̍s����|���āA�ŏI�I�ȍ����s��ɂ���
	mMatrix = mMatrix * mpParent->mMatrix;
}
