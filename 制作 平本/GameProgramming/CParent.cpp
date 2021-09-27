#include "CParent.h"
#include "Ckey.h"
#include"CPlayer.h"
#include"CItem.h"
#define INIT_POSE CVector(0.0f, 0.0f, 1.0f) //�����̎p��
#define VELOCITY CVector(0.0f, 0.0f, 2.0f) //�ړ����x
#define ROTATE_V CVector(0.0f, 2.0f, 0.0f) //��]���x
#define COLLIDER_POS CVector(0.0f, 7.0f, 0.0f) //�R���C�_�̈ʒu
#define PARENT_MODEL "Weapon.obj","Weapon.mtl"



CModel CChild::sModel;
int CChild::sCount = 0;

CChild::CChild(CCharacter* parent)
	: mCollider(this, &mMatrix, CVector(0.0f, 7.0f, 0.0f), 2.0f)
	
{
	mCollider.mTag = CCollider::EWEAPONCOLLIDER;
	mTag = EWEAPON;
	mInitPose =CVector (0.0f, 0.0f, 1.0f);
	//�e�̃C���X�^���X�̑ޔ�
	mpParent = parent;

	if (sCount == 0)
	{
		
		sModel.Load(PARENT_MODEL);
	}
	mpModel = &sModel;
	//sCount++;
	mScale = CVector(5.5f, 7.5f, 5.5f);
	mPosition = CVector(0.0f, 1.5f, 0.0f);
	mRotation = INIT_POSE;
	CTransform::Update();

}


void CChild::Update()
{
	
	if (CItem::mItemCount > 0) {
        CItem::mItemCount--;
		
		mCollider.mRadius = 5.0;
		
	}
	else if(CItem::mItemCount <=0)  {
		mCollider.mRadius = 2.0;
	}
	if (CPlayer::mAction1 < 60) {
		mRotation.mX += 20.0f;
		CPlayer::mAction1++;
	}
	else if (CPlayer::mAction2 < 3) {
		mRotation = mInitPose;
		CPlayer::mAction2++;
	}
	else if (CPlayer::mAction2 < 60) {
        if (mRotation.mX < 90) {
			mRotation.mX = 90.0f;
		}
        CPlayer::mAction2++;
		mRotation.mY += 40.0f;
	}
	else if (CPlayer::mAction3 < 3) {
			
		mPosition=mInitPose;
		CPlayer::mAction3++;
	}
	else if (CPlayer::mAction3 < 60) {
		mRotation.mX += 20.0f;
        mRotation.mZ += 20.0f;
		CPlayer::mAction3++;
		
	}
	
	else if(CPlayer::mAction1>=60&& CPlayer::mAction2 >= 60&& CPlayer::mAction3 >= 60) {
        mRotation = INIT_POSE;
	}
	//�q�̍s��̍X�V
	CTransform::Update();
	//�����̍s��ɐe�̍s����|���āA�ŏI�I�ȍ����s��ɂ���
	mMatrix = mMatrix * mpParent->mMatrix;
}

void CChild::Collision(CCollider* m, CCollider* o) {
	
}

void CChild::TaskCollision()
{

	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();

	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);


}

