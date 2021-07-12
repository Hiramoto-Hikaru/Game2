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
	mModelW.Load("Weapon.obj", "Weapon.mtl");
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����

	CTransform::Update();//�s��̍X�V
}
CWeapon::CWeapon( 
)
	
{

}
void CWeapon::Update(){
	//�O�i
	if (CKey::Push('I')) {
		if (mRotationCount <= 0) {
			mRotationCount += 1;
			if (mRotationCountFirst > 0) {
				mRotationCountFirst--;
			}
		}
		else if (mRotationCount2 > 0) {//�E�������Ă����Ƃ�
			mRotation.mY += 90;
			mRotationCount2 -= 1;
		}
		else if (mRotationCount3 > 0) {//���������Ă����Ƃ�
			mRotation.mY += 180;
			mRotationCount3 -= 1;
		}
		else if (mRotationCount4 > 0) {//���������Ă����Ƃ�
			mRotation.mY -= 90;
			mRotationCount4 -= 1;
		}
		
	}
	//���
	else if (CKey::Push('K')) {
		if (mRotationCount3 <= 0) {
			mRotationCount3 += 1;
			if (mRotationCountFirst > 0) {
				mRotation.mY += 180;
				mRotationCountFirst--;
			}
		}
		else if (mRotationCount2 > 0) {//�E�������Ă����Ƃ�
			mRotation.mY -= 90;
			mRotationCount2 -= 1;
		}
		else if (mRotationCount > 0) {//���ʂ������Ă����Ƃ�
			mRotation.mY += 180;
			mRotationCount -= 1;
		}
		else if (mRotationCount4 > 0) {//���������Ă����Ƃ�
			mRotation.mY += 90;
			mRotationCount4 -= 1;
		}
	
	}
	//����
	else if (CKey::Push('J')) {
		if (mRotationCount4 <= 0) {
			mRotationCount4 += 1;
			if (mRotationCountFirst > 0) {
				mRotation.mY += 90;
				mRotationCountFirst--;
			}
		}
		else if (mRotationCount2 > 0) {//�E�������Ă����Ƃ�
			mRotation.mY += 180;
			mRotationCount2 -= 1;
		}
		else if (mRotationCount3 > 0) {//���������Ă����Ƃ�
			mRotation.mY -= 90;
			mRotationCount3 -= 1;
		}
		else if (mRotationCount > 0) {//���ʂ������Ă����Ƃ�
			mRotation.mY += 90;
			mRotationCount -= 1;
		}
		
	}
	//�E��
	else if (CKey::Push('L')) {
		if (mRotationCount2 <= 0) {
			mRotationCount2 += 1;
			if (mRotationCountFirst > 0) {
				mRotation.mY -= 90;
				mRotationCountFirst--;
			}
		}
		else if (mRotationCount > 0) {//���ʂ������Ă����Ƃ�
			mRotation.mY -= 90;
			mRotationCount -= 1;
		}
		else if (mRotationCount3 > 0) {//���������Ă����Ƃ�
			mRotation.mY += 90;
			mRotationCount3 -= 1;
		}
		else if (mRotationCount4 > 0) {//���������Ă����Ƃ�
			mRotation.mY += 180;
			mRotationCount4 -= 1;
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

		if (CPlayer::mAction1 <100) {
			if (mPosition.mY <= 3.0f) {
				mPosition.mY += 3;
			}
            mRotation.mX += 20.0f;
           CPlayer::mAction1++;
		}
		else if (CPlayer::mAction2 <100) {
		if (mRotation.mX < 90) {
        	mRotation.mX += 90.0f;
		}
			mRotation.mY += 20.0f;
			CPlayer::mAction2++;
		}
 		else if (CPlayer::mAction3 <100) {
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
			//�R���C�_�̂��Ƃ����Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			if (o->mpParent->mTag ==CCollider::EENEMYCOLLIDER1 || o->mpParent->mTag == CCollider::EENEMY2COLLIDER) {
				//�G�t�F�N�g����
				new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "Attack.tga", 2, 6, 2);
				//�Փ˂��Ă���Ƃ��͖���
				//mEnabled=false;
			}
		}
		break;
	case CCollider::EENEMYCOLLIDER1:
		if (CCollider::Collision(m, o)) {
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "Attack.tga", 2, 6, 2);
		}
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

