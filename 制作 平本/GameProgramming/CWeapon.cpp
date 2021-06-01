#include"CWeapon.h"
#include"CVector.h"

#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"
#define OBJ "Weapon.obj"//���f���̃t�@�C��
#define MTL "Weapon.mtl"//���f���̃}�e���A���t�@�C��
#include"CCharacter.h"

CWeapon::CWeapon(CModel* model, CVector position, CVector rotation, CVector scale) 
	
	: mCollider(this, &mMatrix, CVector(0.0f, 5.0f, 0.0f), 1.0f)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ�i�N���X���̂ݓK�p�j
	mpModel = model;//���f��
	mPosition = position;//�ʒu
	mRotation = rotation;//��]
	mScale = scale; //�g�k
	
	
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����

	CTransform::Update();//�s��̍X�V
}
CWeapon::CWeapon() 
:mAction1(0)
	,mAction2(0)
	,mAction3(0)
{

}
void CWeapon::Update(){
	//mPosition = mpPlayer->mPosition;

		if (mAction1 > 0) {
			mRotation.mX += 3.0f;
			mAction1--;
		}
		else if (mAction2 > 0) {
			mRotation.mY += 3.0f;
			mAction2--;
		}
		else if (mAction3 > 0) {
			mRotation.mZ += 3.0f;
			mAction3--;
		}
    	else {
		mEnabled = false;
	    }
		
	

}
void CWeapon::Collision(CCollider* m, CCollider* o) {


	switch (o->mType) {
	case CCollider::ESPHERE://���R���C�_�̂Ƃ�
			//�R���C�_�̂��Ƃ����Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "Attack.tga", 2, 6, 2);
			//�Փ˂��Ă���Ƃ��͖���
			//mEnabled=false;
		}
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

