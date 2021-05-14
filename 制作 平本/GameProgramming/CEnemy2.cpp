#include"CEnemy2.h"
#include"CEffect.h"
#include"CCollisionManager.h"
#include"CBullet.h"
#define OBJ "f14.obj"//���f���̃t�@�C��
#define MTL "f14.mtl"//���f���̃}�e���A���t�@�C��
#define HP 3
#define VELOCITY 0.11f //�}�N��

CModel CEnemy2::mModel;//���f���f�[�^�쐬

//�f�t�H���g�R���X�g���N�^
CEnemy2::CEnemy2()
//�R���C�_�̐ݒ�
	:mCollider(this,&mMatrix,CVector(0.0f,0.0f,0.0f),0.1f)
	,mColSearch(this,&mMatrix,CVector(0.0f,0.0f,100.0f),30.0f)
	,mpPlayer(0)
	,mHp(HP)

{
	//���f���������Ƃ��͓ǂݍ���
	if (mModel.mTriangles.size() == 0) {
		mModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &mModel;
	mColSearch.mTag = CCollider::ESEARCH;//�^�O�ݒ�

}

//CEnemy(�ʒu�A��]�A�g�k�j
CEnemy2::CEnemy2(const CVector& position, const CVector& rotation, const CVector& scale)
:CEnemy2()

{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;//�ʒu�̐ݒ�
	mRotation = rotation;//��]�̐ݒ�
	mScale = scale;//�g�k�̐ݒ�
	CTransform::Update();//�s��̍X�V
	//�ڕW�n�_�̐ݒ�
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;

	//�D��x���P�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}
//�X�V����
void CEnemy2::Update() {
	//�������iX���j�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f)*mMatrixRotate;
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
		if (-2.0f < dx && dx< 2.0f) {
				//Y����-2�`2�͈̔͂ɐڐG
			if (-2.0f < dy && dy < 2.0f) {
				//�ʒu���ړ�(Z��������0.9���ړ��j
				mPosition = CVector(0.0f, 0.0f, 0.9f) * mMatrix;

				//Z����0.0�ȏ�͈̔͂ɐڐG
				if (0.0f <= dz) {
                //�e�𔭎�

				/*CBullet* bullet = new CBullet();
				bullet->Set(0.1f, 1.5f);
				bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
				bullet->mRotation = mRotation;
				bullet->Update();*/
				}
				
			}

		}

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
	//�㉺�����ɉ�]
	/*if (dy > margin) {
		mRotation.mX  -= 1.0f;//��։�]
	}
	else if (dy < -margin) {
		mRotation.mX += 1.0f;//���։�]
	}*/
	//�ړ�����
	mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY) * mMatrixRotate;
	CTransform::Update();//�s��X�V


	int r = rand() % 60; //rand()�͐����̗�����Ԃ�
	                     //%180�͂P�W�O�Ŋ������]������߂�
	if (r == 0) {
		if (mpPlayer) {
			mPoint = mpPlayer->mPosition;

		}
		else {
			mPoint = mPoint * CMatrix().RotateY(45);
		}
	}

	mpPlayer =0;
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
//���~������
		mPosition.mY -= 0.03f;

}
//Collision(�R���C�_�P�C�R���C�_�Q�C�j
void CEnemy2::Collision(CCollider* m, CCollider* o) {
	//���肪�T�[�`�̂Ƃ��͖߂�
	if (o->mTag == CCollider::ESEARCH) {
		
		return;
	}
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


	//����̃R���C�_�^�C�v�̔���
	switch (o->mType) {
	case CCollider::ESPHERE://���R���C�_�̂Ƃ�
			//�R���C�_�̂��Ƃ����Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			mHp--;
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
				//���j�Œn�ʂɏՓ˂���Ɩ���
			if (mHp <= 0) {
			
				 //mEnabled = false;
			}
		}
	
		break;
	}
}
void CEnemy2::TaskCollision() {
	mColSearch.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mColSearch, COLLISIONRANGE);
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
