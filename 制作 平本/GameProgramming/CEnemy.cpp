#include"CEnemy.h"
#include"CVector.h"

#include"CTaskManager.h"
#include"CEffect.h"
#include"CBullet.h"
#include"CCollisionManager.h"
#define COLLISIONRANGE 30
#define HP 10
#define VELOCITY 0.11f //�}�N��
//�R���X�g���N�^
//CEnemy�i���f���A�ʒu�A��]�A�g�k)
//&mMatrix=�G
CEnemy::CEnemy(CModel* model, CVector position, CVector rotation, CVector scale)
	:mCollider1(this, &mMatrix, CVector(-0.5f, 1.0f, 0.0f), 4.0f)
	, mCollider2(this, &mMatrix, CVector(-0.5f, 1.0f, -1.0f), 4.0f)
	, mCollider3(this, &mMatrix, CVector(-0.5f, 1.0f, -2.0f), 4.0f)
	, mColSearch(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 200.0f)
	, mpPlayer(nullptr)
	, mFireCount(0)
	,mHp(HP)
{
	


	//���f���A�ʒu�A��]�A�g�k��ݒ�i�N���X���̂ݓK�p�j
	mpModel = model;//���f��
	mPosition = position;//�ʒu
	mRotation = rotation;//��]
	mScale = scale; //�g�k
	//�D��x��1�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
	mPoint = mPosition + CVector(0.0f, 0.0f, 30.0f) * mMatrixRotate;
	CTransform::Update();//�s��̍X�V
	mTag = EENEMY;
	mColSearch.mTag = CCollider::ESEARCH;
	mCollider1.mTag = CCollider::EENEMYCOLLIDER;
	mCollider2.mTag = CCollider::EENEMYCOLLIDER;
	mCollider3.mTag = CCollider::EENEMYCOLLIDER;
}
void CEnemy::Update() {
	//�������iX���j�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//������iY���j�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//�O�����iZ���j�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	//�v���C���[�̃|�C���^���O�ȊO�̂Ƃ�
	if (mpPlayer) {
		//�v���C���[�܂ł̃x�N�g�������߂�
		//�v���C���[�ƓG�̍��W�̍�
		CVector vp = mpPlayer->mPosition - mPosition;
		float dx = vp.Dot(vx);
		float dy = vp.Dot(vy);
		float dz = vp.Dot(vz);
		
	}
 
	//�ڕW�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mPoint - mPosition;
	//���x�N�g���Ƃ̓��ς����߂�
	float dx = vp.Dot(vx);

	//��x�N�g���Ƃ̓��ς����߂�
	float dy = vp.Dot(vy);
	float margin = 0.1f;
	//���E�����։�]

	if (dx > margin) {
		mRotation.mY += 1.0f;//���։�]
	}
	else if (dx < -margin) {
		mRotation.mY -= 1.0f;//�E�։�]
	}
	
	//�ړ�����
   mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY) * mMatrixRotate;
    //�s����X�V
	CTransform:: Update();
	int r = rand() % 180; //rand()�͐����̗�����Ԃ�
						 //%180�͂P�W�O�Ŋ������]������߂�
	if (r == 0) {
		if (mpPlayer) {
			mPoint = mpPlayer->mPosition;
		}
		else {
			mPoint = mPoint * CMatrix().RotateY(45);
		}
	}
	mpPlayer = 0;
	if (mHp <= 0) {
		mHp--;
		mEnabled = false;
		//15�t���[�����ƂɃG�t�F�N�g
		if (mHp % 15 == 0) {
			//�G�t�F�N�g����
			//new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		CTransform::Update();
		return;
	}
	if (mHp <= -100) {
		mEnabled = false;
	}
}
void CEnemy::Collision(CCollider* m, CCollider* o) {
	//�������T�[�`�p�̂Ƃ�
	if (m->mTag == CCollider::ESEARCH) {
		//���肪�e�R���C�_�̂Ƃ�
		if (o->mType == CCollider::ESPHERE) {
			//���肪�v���C���[�̂Ƃ��A
			if (o->mpParent->mTag == EPLAYER) {
				//�Փ˂��Ă���Ƃ�
				if (CCollider::Collision(m, o)) {
					//�v���C���[�̃|�C���^�ݒ�
					mpPlayer = o->mpParent;
				}
			}
		}
		return;
	}
	if (m->mType == CCollider::ESPHERE) {
		
		if (o->mType == CCollider::ESPHERE) {
			//���肪����̂Ƃ��A
			if (o->mpParent->mTag == EWEAPON) {
				//�Փ˂��Ă���Ƃ�
				if (CCollider::Collision(m, o)) {
					new CEffect(o->mpParent->mPosition, 3.0f, 3.0f, "Attack.tga", 2, 6, 2);
					mHp--;
				}
			}
		}
		return;
        if (o->mType == CCollider::ETRIANGLE) {
                CVector adjust;//�����l
				//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
				//adjust�A�A�A�����l
				if (CCollider::CollisionTriangleSphere(o, m, &adjust))
				{
					//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
					mPosition = mPosition + adjust;
				}
				
	    }
		return;
	}
	


	
}
void CEnemy::TaskCollision() {

	//�R���C�_�̗D��x�ύX
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();
	mColSearch.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColSearch, COLLISIONRANGE);
}