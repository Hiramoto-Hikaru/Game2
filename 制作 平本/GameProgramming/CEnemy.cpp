#include"CEnemy.h"
#include"CVector.h"

#include"CTaskManager.h"
#include"CEffect.h"
#include"CBullet.h"
#include"CCollisionManager.h"
#define COLLISIONRANGE 30
#define VELOCITY 0.11f //�}�N��
//�R���X�g���N�^
//CEnemy�i���f���A�ʒu�A��]�A�g�k)
//&mMatrix=�G
CEnemy::CEnemy(CModel* model, CVector position, CVector rotation, CVector scale)
	:mCollider1(this, &mMatrix, CVector(0.0f, 5.0f, 0.0f), 0.8f)
	, mCollider2(this, &mMatrix, CVector(0.0f, 5.0f, 7.0f), 0.8f)
	, mCollider3(this, &mMatrix, CVector(0.0f, 5.0f, -7.0f), 0.8f)
	, mpPlayer(nullptr)
	, mFireCount(0)
	,mHp(10)
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
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
	CTransform::Update();//�s��̍X�V

}
void CEnemy::Update() {
	//�������iX���j�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//������iY���j�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//�O�����iZ���j�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 5.0f) * mMatrixRotate;
	//�v���C���[�̃|�C���^���O�ȊO�̂Ƃ�
	if (mpPlayer) {
		//�v���C���[�܂ł̃x�N�g�������߂�
		//�v���C���[�ƓG�̍��W�̍�
		CVector vp = mpPlayer->mPosition - mPosition;
		float dx = vp.Dot(vx);
		float dy = vp.Dot(vy);
		float dz = vp.Dot(vz);
		//X����-2�`2�͈̔͂ɐڐG
		if (-2.0f < dx && dx < 2.0f) {
			//Y����-2�`2�͈̔͂ɐڐG
			if (-2.0f < dy && dy < 2.0f) {
				
				//Z����0.0�ȏ�͈̔͂ɐڐG
				if (0.0f <= dz) {
                   //��~
			    	mPosition = CVector(0.0f, 0.0f, 0.0f) * mMatrix;
					if (mFireCount <=0) {
						  //�e�𔭎�
						CBullet* bullet = new CBullet();
						bullet->Set(0.1f, 1.5f);
						bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
						bullet->mRotation = mRotation;
						bullet->Update();
						mFireCount += 60;
					}
					
				}

			}

		}

	}
	if (mFireCount >= 0) {
		mFireCount--;
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
		mRotation.mY += 5.0f;//���։�]
	}
	else if (dx < -margin) {
		mRotation.mY -= 5.0f;//�E�։�]
	}
	//�㉺�����ɉ�]
	/*if (dy > margin) {
		mRotation.mX -= 5.0f;//��։�]
	}
	else if (dy < -margin) {
		mRotation.mX += 5.0f;//���։�]
	}*/
	//�ړ�����
	mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY) * mMatrixRotate;
	
    //�s����X�V
	CTransform:: Update();
	int r = rand() % 60; //rand()�͐����̗�����Ԃ�
						 //%180�͂P�W�O�Ŋ������]������߂�
	if (r == 0) {
		if (mpPlayer) {
			mPoint = mpPlayer->mPosition;
		}
		else {
			mPoint = mPoint * CMatrix().RotateY(90);
		}
	}
	mpPlayer = 0;
	if (mHp <= 0) {
		mHp--;
		//15�t���[�����ƂɃG�t�F�N�g
		/*if (mHp % 15 == 0) {
			//�G�t�F�N�g����
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}*/
		CTransform::Update();
		return;
	}
	//�ʒu���ړ�(Z��������0.9���ړ��j
	mPosition = CVector(0.0f, 0.0f, 0.9f) * mMatrix;
}
void CEnemy::Collision(CCollider* m, CCollider* o) {
	//���肪�T�[�`�̂Ƃ��͖߂�
	if (o->mTag == CCollider::ESEARCH) {
		return;
	}
	//����̃R���C�_�^�C�v�̔���
	switch (o->mType) {
	case CCollider::ESPHERE://���R���C�_�̂Ƃ�
			//�R���C�_�̂��Ƃ����Փ˂��Ă��邩����
			if (CCollider::Collision(m, o)) {
				//�G�t�F�N�g����
				new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
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
void CEnemy::TaskCollision() {

	//�R���C�_�̗D��x�ύX
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider3, COLLISIONRANGE);
}