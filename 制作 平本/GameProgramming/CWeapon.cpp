#include"CWeapon.h"
#include"CVector.h"

#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"
#define OBJ "Weapon.obj"//���f���̃t�@�C��
#define MTL "Weapon.mtl"//���f���̃}�e���A���t�@�C��
#include"CCharacter.h"
#include"CMatrix.h"
#include"CsceneGame.h"
#include"CKey.h"

CWeapon::CWeapon(CModel* model, CVector position, CVector rotation, CVector scale) 
	
	: mCollider(this, &mMatrix, CVector(0.0f, 8.0f, 0.0f), 1.5f)
	, mRotationCountFirst(1)
	, mRotationCount(0)
	, mRotationCount2(0)
	, mRotationCount3(0)
	, mRotationCount4(0)

	,mStamina2(400)

{
	//���f���A�ʒu�A��]�A�g�k��ݒ�i�N���X���̂ݓK�p�j
	mpModel = model;//���f��
	mPosition = position;//�ʒu
	mRotation = rotation;//��]
	mScale = scale; //�g�k
	mCollider.mTag = CCollider::EWEAPON;
	mTag = EWEAPON;
	mModelW.Load("Weapon.obj", "Weapon.mtl");
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����

	CTransform::Update();//�s��̍X�V
}


void CWeapon::Update(){
	//���
	 if (CPlayer::mWeaponCount == 1) {
		 if (mRotation.mY <=  180) {
           mRotation.mY += 180;
		 }
		
	}
	 //��
	else if (CPlayer::mWeaponCount == 2) {
		 if (mRotation.mY >= -90) {
			 mRotation.mY -= 90;
		 }
	}
	 //�E
	else if (CPlayer::mWeaponCount == 3) {
		 if (mRotation.mY <= 90) {
			 mRotation.mY += 90;
		 }
	}
	 

	//������
	if (CKey::Push('A')) {
		mRotation.mY += 3;
	}
	//�E����
	if (CKey::Push('D')) {
		mRotation.mY -= 3;
	}

		if (CPlayer::mAction1 <60) {
			//if (mPosition.mY <= 3.0f) {
				mPosition.mY += 3;
			//}
            mRotation.mX += 20.0f;
           CPlayer::mAction1++;
		}
		else if (CPlayer::mAction2 <60) {
		if (mRotation.mX < 90) {
        	mRotation.mX += 90.0f;
		}
			mRotation.mY += 20.0f;
			CPlayer::mAction2++;
		}
 		else if (CPlayer::mAction3 <60) {
			mRotation.mZ += 20.0f;
			CPlayer::mAction3++;
		}
    	
		else {

			mEnabled = false;
		}
	    
		CTransform::Update();
}
void CWeapon::Collision(CCollider* m, CCollider* o) {

	switch (o->mType) {
	case CCollider::ESPHERE://���R���C�_�̂Ƃ�
		
		break;

	case CCollider::ETRIANGLE://�O�p�R���C�_�̂Ƃ�
		CVector adjust;//�����l
		//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
		//adjust�A�A�A�����l
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + adjust;
		}
		break;
	}
}

void CWeapon::TaskCollision()
{

	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
	

}

